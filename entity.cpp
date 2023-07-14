#include "entity.h"

#include <GL/freeglut.h>

Entity::Entity(int x, int y, int z, int vx, int vy, int vz, int dx, int dy, int dz, float health, int angle, bool isCollider, bool state){
    position.x = x;
    position.y = y;
    position.z = z;
    velocity.x = vx;
    velocity.y = vy;
    velocity.z = vz;
    direction.x = dx;
    direction.y = dy;
    direction.z = dz;
    this->health = health;
    this->angle = angle;
    this->isCollider = isCollider;
    this->state = state;
}

void Entity::setPos(vector3d pos){
    position = pos;
}

void Entity::setAngle(int angle){
    this->angle = angle;
}

int Entity::getAngle(){
    return angle;
}

void Entity::setDir(vector3d dir){
    direction = dir;
}

vector3d Entity::getDir(){
    return direction;
}

vector3d Entity::getPos(){
    return position;
}

void Entity::setVel(vector3d vel){
    velocity = vel;
}

void Entity::setHealth(float health){
    this->health = health;
}

float Entity::getHealth(){
    return health;
}

void Entity::draw(float x, float y, float angle, int depth[240]){
    current_frame++;
    float sx = position.x - x;
    float sy = position.y - y;
    float sz = position.z;

    float CS = cos(angle * M_PI / 180);
    float SN = sin(angle * M_PI / 180);
    float a = sy * CS + sx * SN;
    float b = sx * CS - sy * SN;
    sx = a;
    sy = b;

    sx = (sx * 216.0 / sy) + (240 / 2);
    sy = (sz * 216.0 / sy) + (160 / 2);

    int x1, y1;
    int scale = 64 * 160 / b;

    //texture
    float t_x = 0;
    float t_y = 63.0;
    float t_x_step = 63.5 / (float) scale;
    float t_y_step = 64.0 / (float) scale;

    for (x1 = sx - scale / 2; x1 < sx + scale / 2; x1++){
        //if (sx > 0 && sx < 240 && b < depth[x1]){
            t_y = 63;
            for (y = 0; y < scale; y++){
                int pixel = ((int) t_y * 64 + (int) t_x) * 3;
                if (current_frame < 5){
                    if (sprite[pixel] != 255 || sprite[pixel + 1] != 0 || sprite[pixel + 2] != 255){
                        glPointSize(8); glColor3ub(sprite[pixel], sprite[pixel + 1], sprite[pixel + 2]); glBegin(GL_POINTS); glVertex2i(x1 * 8, sy * 8 - y * 8); glEnd();
                    }
                } else {
                    if (sprite2[pixel] != 255 || sprite2[pixel + 1] != 0 || sprite2[pixel + 2] != 255){
                        glPointSize(8); glColor3ub(sprite2[pixel], sprite2[pixel + 1], sprite2[pixel + 2]); glBegin(GL_POINTS); glVertex2i(x1 * 8, sy * 8 - y * 8); glEnd();
                    }
                }
                
                t_y-= t_y_step;
                if (t_y < 0) {
                    t_y = 0;
                }
            }
            t_x += t_x_step;
        //}
    }
    if (current_frame > 10){
        current_frame = 0;
    }
}