#include "sprite.h"

Sprite::Sprite(int id, int width, int height, float scale, float rotation){
    this->id = id;
    this->width = width;
    this->height = height;
    this->scale = scale;
    this->rotation = rotation;
}

Pixel::Pixel(int r, int g, int b, int a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}