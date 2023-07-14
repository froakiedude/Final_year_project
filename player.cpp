#include "player.h"

Player::Player(int x, int y, int z, int vx, int vy, int vz, int dx, int dy, int dz, float health, int angle, bool isCollider, bool state) : Entity(x, y, z, vx, vy, vz, dx, dy, dz, health, angle, isCollider, state){
    this->setPos(vector3d(x, y, z));
    this->setVel(vector3d(vx, vy, vz));
    this->setDir(vector3d(dx, dy, dz));
    this->setAngle(angle);
    this->isCollider = isCollider;
    this->setHealth(health);
}

void Player::update(float x, float y){
    setHealth(getHealth());
}