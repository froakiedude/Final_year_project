#include <math.h>
#include "vector3d.h"
#include <iostream>

vector3d::vector3d(const vector3d &vec)
{
    x=vec.x;
    y=vec.y;
    z=vec.z;
}

//addition
vector3d vector3d::operator+(const vector3d &vec){
    return vector3d(x+vec.x,y+vec.y,z+vec.z);
}

vector3d &vector3d::operator+=(const vector3d &vec){
    x+=vec.x;
    y+=vec.y;
    z+=vec.z;
    return *this;
}

//subtraction
vector3d vector3d::operator-(const vector3d &vec){
    return vector3d(x-vec.x,y-vec.y,z-vec.z);
}

vector3d &vector3d::operator-=(const vector3d &vec){
    x-=vec.x;
    y-=vec.y;
    z-=vec.z;
    return *this;
}

//scalar multiplication

vector3d vector3d::operator*(float value){
    return vector3d(x*value,y*value,z*value);
}

vector3d vector3d::operator*(const vector3d &vec){
    return vector3d(x*vec.x,y*vec.y,z*vec.z);
}



vector3d &vector3d::operator*=(float value){
    x*=value;
    y*=value;
    z*=value;
    return *this;
}

//scalar division
vector3d vector3d::operator/(float value){
    return vector3d(x/value,y/value,z/value);
}

vector3d &vector3d::operator/=(float value){
    x/=value;
    y/=value;
    z/=value;
    return *this;
}


vector3d &vector3d::operator=(const vector3d &vec){
    x=vec.x;
    y=vec.y;
    z=vec.z;
    return *this;
}

//Dot product
float vector3d::dot_product(const vector3d &vec){
    return x*vec.x+vec.y*y+vec.z*z;
}

//cross product
vector3d vector3d::cross_product(const vector3d &vec){
    float ni=y*vec.z-z*vec.y;
    float nj=z*vec.x-x*vec.z;
    float nk=x*vec.y-y*vec.x;
    return vector3d(ni,nj,nk);
}

float vector3d::magnitude(){
    return sqrt(square());
}

float vector3d::square(){
    return x*x+y*y+z*z;
}

vector3d vector3d::normalize(){
    *this/=magnitude();
    return *this;
}

float vector3d::distance(const vector3d &vec){
    vector3d dist=*this-vec;
    return dist.magnitude();
}

float vector3d::getX(){
    return x;
}

float vector3d::getY(){
    return y;
}

float vector3d::getZ(){
    return z;
}

void vector3d::print(){
    std::cout << x << " " << y << " " << z << std::endl;
}