#include <GL/freeglut.h>

void RenderString(float x, float y, void *font, char* string, int r, int g, int b){  
  glColor3f(r, g, b); 
  int len, i;
  glRasterPos2f(x, y);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}