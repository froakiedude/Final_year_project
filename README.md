# SteamEngine
# Introduction
SteamEngine is a 2.5D video game engine which works by projecting a 2 dimensional map view into a 3 dimensional world view from the players perspective.

There is no z-axis in terms of under the hood code, everything is imply projected to a 3D view and texture mapped appropriately.

# Installation

Simply clone the repository or download as zip and extract. When building, ensure that the dependencies folder is part of your compilers include path and when running the compiled output ensure that the glut32.dll and .lib files are in the same folder and that the assets folder has the assets that you are using.

# vector3d

vector3d is the vector processing and mathematics class found in SteamEngine. It consists of 3 float values corresponding to an x, y and z position/rotation. 

All vectors are **mutable**. That is to say that operations done to them directly modify the values. No new objects are created.
## vector3d()
Default constructor sets all float values to 0

```
vector3d x = new vector3d();
x.print();

output:
0 0 0
```

## vector3d(float x, float y, float z)
Constructor for all float values

```
vector3d x = new vector3d(1.0f, 0.0f, 2.0f);
x.print();

output:
1.0 0 2.0
```

## vector3d(const vector3d &vec)
Copy constructor from pre-existing vector

```
vector3d x = new vector3d(0.0f, 0.0f, 0.0f);
vector3d y = new vector3d(y);
y.print();

output:
0 0 0
```

## vector3d operator+(const vector3d &vec)

Add two vectors together

```
vector3d x = new vector3d(1.0f, 1.0f, 1.0f);
vector3d y = new vector3d(1.0f, 1.0f, 1.0f);
vector3d z = new vector3d();
z = x + y;
z.print();

output:
2.0 2.0 2.0
```

## vector3d &operator+=(const vector3d &vec)

Augmented assignment for adding two vectors together

```
vector3d x = new vector3d(1.0f, 1.0f, 1.0f);
vector3d y = new vector3d(1.0f, 1.0f, 1.0f);
x+= y;
x.print();

output:
2.0 2.0 2.0
```

# Entity
Entity is the base class for players, enemies and objects that inhabit the world. Geometry of the level (the walls) is not considered to be an entity. All entities define a time variable dictating how long they have existed for and a time variable stating when they should die and be cleaned from memory.
By setting this variable to 0, the user can delete objects from memory on demand at the end of the current frame.
This class is abstract so it cannot be instantiated, only one of its derived classes can be (such as Player or Enemy).

Each class inheriting from Entity must define it's own implementation of the update() function. Entities also hold an array of sprites corresponding to frames of animation and a variable stating which frame is currently active. The programmers can use these features to create sprite animation.

## void setPos(vector3d pos)

Setter for the position vector of the entity

```
player.setPos(*new vector3d(0, 0, 0));
```

## void setAngle(int angle)

Setter for the angle of the entity

```
player.setAngle(0);
```

## void setDir(vector3d dir)

Setter for the direction of the entity

```
player.setDir(*new vector3d(0, 0, 0));
```

## void setVel(vector3d vel)

Setter for the velocity of the entity

```
player.setVel(*new vector3d(0, 0, 0));
```

## void setHealth(float health)

Setter for the health of the entity

```
player.setHealth(0.0);
```

## void draw(float x, float y, float angle, int depth[number of rays cast])

Draws the stored sprite for the entity given the required values of the player and a depth so that it can be occluded by walls. Doesn't draw 255,0,255 pixels so use those for transparency.

```
entities[i]->draw(player.getPos().getX(), player.getPos().getY(), player.getAngle(), depth);
```

## virtual void update(float x, float y)

Abstract method for updating the entity, implemented on a per class basis

# Player
This class inherits from entity and implements features desired for the player of the game

## Player(int x, int y, int z, int vx, int vy, int vz, int dx, int dy, int dz, float health, int angle, bool isCollider)

Constructor for player object

```
//initialise player
Player player = Player(150, 400, 90, cos(degToRad(90)), -sin(degToRad(90)), 0, 0, 0, 0, 0, 0, true);
```

## void update()

Updates all relevant data, including health, position and sprite. Should be called once per frame.

```
player.update();
```

# raycast.cpp
This is where raycasts are calculated against the wall defined in the game map and translated into a "3D" view of the game world. By default, we cast 240 rays though this can be altered by the programmer to give a cleaner although more expensive result.
When a wall is hit by a ray, its texture (which is defined in the map) is looked up and and overlayed over the wall. All textures are pre loaded at first runtime so this presents no overhead. This is also where the programmer should write their main method code.

## void output(int x, int y, char *string)

Outputs given text to the screen at given coordinates

```
//framerate counter
double lastTime = 0;
int num_frames = 0;
//CALL EVERY FRAME
double currentTime = glutGet(GLUT_ELAPSED_TIME);
num_frames++;
if (currentTime - lastTime >= 1000.0) {
   fps_str = std::to_string(num_frames);
   num_frames = 0;
   lastTime = currentTime;
}
output(10, 20, &fps_str[0]);
```

## void ReadWavFileIntoMemory(std::string fname, BYTE** pb, DWORD *fsize)

Reads a wav file into memory for later playback. The 2nd and third parameters are pointers to the memory location where the data will be stored.

```
DWORD dwFileSize;
BYTE* pFileBytes;
ReadWavFileIntoMemory("assets/audio/music.wav", &pFileBytes, &dwFileSize); 
```

## void playSoundAtVolume(string filename, float volume)

Plays a sound at a given volume. The volume is a float between 0 and 1. This function calls ReadWavFileIntoMemory().

```
playSoundAtVolume("assets/audio/music.wav", 0.02f);
```

## void ButtonDown(unsigned char key, int x, int y)

Handles key presses by setting the relevant key to true. This function is passed to OpenGL.

```
glutKeyboardFunc(ButtonDown);
```

## void ButtonUp(unsigned char key, int x, int y)

Handles key releases by setting the relevant key to false. This function is passed to OpenGL.

```
glutKeyboardFunc(ButtonUp);
```

## float degToRad(float a)

Converts degrees to radians

```
float Tan=tan(degToRad(ra));
```

## float FixAng(float a)

Wraps angle back around after it exceeds 360 or goes below 0

```
ra=FixAng(player.getAngle()+15); 
```

## void init()

Initializes window pane and colour

## void display()

Display function passed to OpengGL to draw the game

## void drawRays2D()

Draws the rays cast by the player in 2D. Called once per frame.