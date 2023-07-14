#include "enemy.h"

Enemy::Enemy(int x, int y, int z, int vx, int vy, int vz, int dx, int dy, int dz, float health, int angle, bool isCollider, bool state) : Entity(x, y, z, vx, vy, vz, dx, dy, dz, health, angle, isCollider, state){
    this->setPos(vector3d(x, y, z));
    this->setVel(vector3d(vx, vy, vz));
    this->setDir(vector3d(dx, dy, dz));
    this->setAngle(angle);
    this->isCollider = isCollider;
    this->setHealth(health);
}

void Enemy::update(float x, float y){
    if (this->getPos().x > x){
        this->setPos(vector3d(this->getPos().x - 0.1, this->getPos().y, this->getPos().z));
    }
    if (this->getPos().x < x){
        this->setPos(vector3d(this->getPos().x + 0.1, this->getPos().y, this->getPos().z));
    }
    if (this->getPos().y > y){
        this->setPos(vector3d(this->getPos().x, this->getPos().y - 0.1, this->getPos().z));
    }
    if (this->getPos().y < y){
        this->setPos(vector3d(this->getPos().x, this->getPos().y + 0.1, this->getPos().z));
    }
}