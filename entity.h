#include "vector3d.h"
#include "sprite.h"
#include <math.h>

class Entity{
    public:
        Entity(int x, int y, int z, int vx, int vy, int vz, int dx, int dy, int dz, float health, int angle, bool isCollider, bool state);
        void setPos(vector3d pos);
        void setVel(vector3d vel);
        void setAngle(int angle);
        void setHealth(float health);
        float getHealth();
        int getAngle();
        void setDir(vector3d dir);
        vector3d getDir();
        vector3d getPos();
        bool isCollider;
        virtual void update(float x, float y) = 0;
        float timeAlive = 0; 
        float timeToLive = 9999999999; 
        int current_frame = 0;
        bool state;
        void draw(float x, float y, float angle, int depth[240]);
        int sprite[12288];
        int sprite2[12288];
    private:
        vector3d position;
        vector3d velocity;
        vector3d direction;
        int angle;
        float health;
};