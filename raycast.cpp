#include <stdlib.h>
#include "enemy.h"
#include "audio.h"
#include <algorithm>
#include <iterator>
#include <GL/freeglut.h>
  

#include "assets/textures/brick_64.ppm"
#include "assets/textures/test_sprite.ppm"
#include "assets/textures/test_sprite_frame_2.ppm"


typedef struct {
   int w, a, d, s;
} ButtonKeys; ButtonKeys keys;

//-----------------------------MAP----------------------------------------------
#define mapX  8      //map width
#define mapY  8      //map height
#define mapS mapX * mapY      //map cube size
int mapW[]=          //the map array. Edit to change level but keep the outer walls
{
 1,1,1,1,1,1,1,1,
 1,0,0,1,0,0,0,1,
 1,0,0,1,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,1,1,1,1,1,1,1,
};

int depth[240];

//read a wav file into memory for later manipulation
void ReadWavFileIntoMemory(std::string fname, BYTE** pb, DWORD *fsize){
    ifstream f(fname, std::ios::binary);

    f.seekg(0, std::ios::end);
    int lim = f.tellg();
    *fsize = lim;

    *pb = new BYTE[lim];
    f.seekg(0, std::ios::beg);

    f.read((char *)*pb, lim);

    f.close();
}

//outputs text to the screen in a given position
void output(int x, int y, char *string){
    int len, i;
    glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }
}

//plays a sound file at a given volume
void playSoundAtVolume(string filename, float volume){
    DWORD dwFileSize;
    BYTE* pFileBytes;
    ReadWavFileIntoMemory("assets/audio/music.wav", &pFileBytes, &dwFileSize); 
    BYTE* pDataOffset = (pFileBytes + 40); 
    __int16 * p = (__int16 *)(pDataOffset + 8);
    for (int i = 80 / sizeof(*p); i < dwFileSize / sizeof(*p); i++){
        p[i] = (float)p[i] * volume;
    }
    PlaySound((LPCSTR)pFileBytes, NULL, SND_MEMORY | SND_ASYNC);
}

std::string fps_str;
float frame1, frame2, framediff;
double lastTime = 0;
int num_frames = 0;

//converts degrees to radians
float degToRad(float a) { 
    return a*M_PI/180.0;
}

//ensures that the angle is between 0 and 360
float FixAng(float a){ 
   if(a>359){ 
      a-=360;
   } 
   if(a<0){ 
      a+=360;
   } 
   return a;
}

//Shader ourShader("C:/Users/oweng/Desktop/UNI/CE301/SteamEngine/22-23_CE301_greene_owen_k_m/fxaa.vs", "C:/Users/oweng/Desktop/UNI/CE301/SteamEngine/22-23_CE301_greene_owen_k_m/fxaa.fs");

//------------------------PLAYER------------------------------------------------
//initialise player
Player player = Player(150, 400, 90, cos(degToRad(90)), -sin(degToRad(90)), 0, 0, 0, 0, 0, 0, true, true);

//create vector of entities
std::vector<Entity*> entities;

Enemy enemy = Enemy(2 * 64, 5 * 64, 20, 0, 0, 0, 0, 0, 0, 0, 0, true, true);

//---------------------------Draw Rays and Walls--------------------------------
void drawRays2D(){
  glColor3f(0,1,1); glBegin(GL_QUADS); glVertex2i(0,  0); glVertex2i(2012,  0); glVertex2i(2012,640); glVertex2i(0,640); glEnd();	//draw background
  glColor3f(0,0,1); glBegin(GL_QUADS); glVertex2i(0,640); glVertex2i(2012,640); glVertex2i(2012,1280); glVertex2i(0,1280); glEnd();	 	
 	
  int r,mx,my,mp,dof,side; float vx,vy,rx,ry,ra,xo,yo,disV,disH; 
  ra=FixAng(player.getAngle()+15);                                                              //ray set back 30 degrees
  
  for(r=0;r<240;r++){
    //---Vertical--- 
    dof=0; side=0; disV=100000;
    float Tan=tan(degToRad(ra));
    if(cos(degToRad(ra))> 0.001){ 
       rx=(((int)player.getPos().x>>6)<<6)+mapS;      
       ry=(player.getPos().x-rx)*Tan+player.getPos().y; 
       xo= mapS; yo=-xo*Tan;
    }//looking left
    else if(cos(degToRad(ra))<-0.001){ 
       rx=(((int)player.getPos().x>>6)<<6) -0.0001; 
       ry=(player.getPos().x-rx)*Tan+player.getPos().y; 
       xo=-mapS; yo=-xo*Tan;
    }//looking right
    else { 
      rx=player.getPos().x; ry=player.getPos().y; dof=mapX;
    }                                                  //looking up or down. no hit  
  
    while(dof<mapX) { 
      mx=(int)(rx)>>6; 
      my=(int)(ry)>>6; 
      mp=my*mapX+mx;                     
      if(mp>0 && mp<mapX*mapY && mapW[mp]==1){ //hit 
        dof=mapX; 
        disV=cos(degToRad(ra))*(rx-player.getPos().x)-sin(degToRad(ra))*(ry-player.getPos().y);
      }        
      else {               //check next horizontal
        rx+=xo; 
        ry+=yo; 
        dof+=1;
      }                                               
    } 
    vx=rx;
    vy=ry;
  
    //---Horizontal---
    dof=0; disH=100000;
    Tan=1.0/Tan; 
    if(sin(degToRad(ra))> 0.001){ ry=(((int)player.getPos().y>>6)<<6) -0.0001; rx=(player.getPos().y-ry)*Tan+player.getPos().x; yo=-mapS; xo=-yo*Tan;}//looking up 
    else if(sin(degToRad(ra))<-0.001){ ry=(((int)player.getPos().y>>6)<<6)+mapS;      rx=(player.getPos().y-ry)*Tan+player.getPos().x; yo= mapS; xo=-yo*Tan;}//looking down
    else{ rx=player.getPos().x; ry=player.getPos().y; dof=mapX;}                                                   //looking straight left or right
   
    while(dof<mapX) 
    { 
     mx=(int)(rx)>>6; my=(int)(ry)>>6; mp=my*mapX+mx;                          
     if(mp>0 && mp<mapX*mapY && mapW[mp]==1){ dof=mapX; disH=cos(degToRad(ra))*(rx-player.getPos().x)-sin(degToRad(ra))*(ry-player.getPos().y);}//hit         
     else{ rx+=xo; ry+=yo; dof+=1;}                                               //check next horizontal
    } 
    
    float shade = 1;
    glColor3f(0,0.8,0);
    if(disV<disH){ shade = 0.5; rx=vx; ry=vy; disH=disV; glColor3f(0,0.6,0);}                  //horizontal hit first
      
    int ca=FixAng(player.getAngle()-ra); disH=disH*cos(degToRad(ca));                            //fix fisheye 
    int lineH = (mapS*1280)/(disH); 
    float ty_step = 64.0 / (float)lineH;
    float ty_off = 0;
    if(lineH>1280){ 
       ty_off = (lineH-1280)/2;
       lineH=1280;
    }                     //line height and limit
    int lineOff = 640 - (lineH>>1);                                               //line offset

    depth[r] = disH;

    int y;
    float ty = ty_off * ty_step;
    int t_res = 64;
    float tx = (int) (rx / 2.0) % t_res;
    if (shade == 1){
     tx = (int) (rx / 2.0) % t_res;
     if (ra > 180){
        tx = t_res - 1 - tx;
     }
    } else {
     tx = (int) (ry / 2.0) % t_res;
     if (ra > 90 && ra < 270){
        tx = t_res - 1 - tx;
     }
    }
   
   Pixel p = Pixel(0,0,0,0);
   for (y = 0; y < lineH; y++){ //loop over pixels
     int pixel = ((int) ty * t_res + (int) tx) * 3;
     p = Pixel(T_brick_64[pixel] * shade, T_brick_64[pixel+1] * shade, T_brick_64[pixel+2] * shade, 255);
     glPointSize(38); glColor3ub(p.r, p.g, p.b); glBegin(GL_POINTS); glVertex2i(r*38, y+lineOff); glEnd(); //draw vertical wall
     ty+=ty_step;
   } 


  ra=FixAng(ra-0.5);                                                              //go to next ray
 }
}//-----------------------------------------------------------------------------


void init(){
 glClearColor(0.3,0.3,0.3,0);
 gluOrtho2D(0,1920,1080,0);
 //to set a sprite for an entity, you need to use std::copy to copy the sprite into the entity's sprite array. Only use this for sprites that are 64x64
 std::copy(std::begin(T_sprite), std::end(T_sprite), std::begin(enemy.sprite));
 std::copy(std::begin(T_sprite_frame_2), std::end(T_sprite_frame_2), std::begin(enemy.sprite2));
 //add the entity to the entities vector
 entities.push_back(&enemy);
}

void display(){   
 frame2=glutGet(GLUT_ELAPSED_TIME); framediff=frame2-frame1; frame1=glutGet(GLUT_ELAPSED_TIME);

 //buttons and collision
 if(keys.a){ player.setAngle(player.getAngle() + 0.2 * framediff); player.setAngle(FixAng(player.getAngle())); player.setDir(*new vector3d(cos(degToRad(player.getAngle())), -sin(degToRad(player.getAngle())), player.getDir().z));} 	
 if(keys.d){ player.setAngle(player.getAngle() - 0.2 * framediff); player.setAngle(FixAng(player.getAngle())); player.setDir(*new vector3d(cos(degToRad(player.getAngle())), -sin(degToRad(player.getAngle())), player.getDir().z));} 
 
  
 int xo = 0; if(player.getDir().x < 0) {xo = -20;} else {xo = 20;}
 int yo = 0; if(player.getDir().y < 0) {yo = -20;} else {yo = 20;}
 int map_size = mapX * mapY;
 int mpx = player.getPos().x/map_size, mpx_add_xo = (player.getPos().x+xo)/map_size, mpx_sub_xo = (player.getPos().x-xo)/map_size;
 int mpy = player.getPos().y/map_size, mpy_add_yo = (player.getPos().y+yo)/map_size, mpy_sub_yo = (player.getPos().y-yo)/map_size;


 if(keys.w){ 
   if(mapW[mpy * mapX + mpx_add_xo] == 0) {
      player.setPos(*new vector3d(player.getPos().x + player.getDir().x * 0.2 * framediff, player.getPos().y, player.getPos().z));
   }
   if(mapW[mpy_add_yo * mapX + mpx] == 0) {
      player.setPos(*new vector3d(player.getPos().x, player.getPos().y + player.getDir().y * 0.2 * framediff, player.getPos().z));
   }
 }
 if(keys.s){ 
   if(mapW[mpy * mapX + mpx_sub_xo] == 0) {
      player.setPos(*new vector3d(player.getPos().x - player.getDir().x * 0.2 * framediff, player.getPos().y, player.getPos().z));
   }
   if(mapW[mpy_sub_yo * mapX + mpx] == 0) {
      player.setPos(*new vector3d(player.getPos().x, player.getPos().y - player.getDir().y * 0.2 * framediff, player.getPos().z));
   }
 }
 glutPostRedisplay();
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
 //first draw walls
 drawRays2D();
 //then update and draw all entities
 for(int i = 0; i < entities.size(); i++){
   entities[i]->timeAlive++;
   if (entities[i]->timeAlive > entities[i]->timeToLive) {
      //remove entity from vector
      entities.erase(entities.begin() + i);
      continue;
   }
   entities[i]->update(player.getPos().getX(), player.getPos().getY());
   entities[i]->draw(player.getPos().getX(), player.getPos().getY(), player.getAngle(), depth);
 }
 //ourShader.use();
 //ourShader.setFloat("someUniform", 1.0f);  
 //calculate and display fps
 double currentTime = glutGet(GLUT_ELAPSED_TIME);
 num_frames++;
 if (currentTime - lastTime >= 1000.0) {
    fps_str = std::to_string(num_frames);
    num_frames = 0;
    lastTime = currentTime;
 }
 output(10, 20, &fps_str[0]);
 glutSwapBuffers();  
}

void ButtonDown(unsigned char key, int x, int y){
 switch(key){
  case 'w': keys.w = 1; break;
  case 's': keys.s = 1; break;
  case 'a': keys.a = 1; break;
  case 'd': keys.d = 1; break;
 }
 glutPostRedisplay();
}

void ButtonUp(unsigned char key, int x, int y){
 switch(key){
  case 'w': keys.w = 0; break;
  case 's': keys.s = 0; break;
  case 'a': keys.a = 0; break;
  case 'd': keys.d = 0; break;
 }
 glutPostRedisplay();
}

int main(int argc, char* argv[]){ 
 playSoundAtVolume("assets/audio/music.wav", 0.02f);
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 glutInitWindowSize(1920,1080);
 glutCreateWindow("Scene");
 init();
 glutDisplayFunc(display);
 glutKeyboardFunc(ButtonDown);
 glutKeyboardUpFunc(ButtonUp);
 glutMainLoop();
}