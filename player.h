#include "entity.h"
#include <vector>

class Player : public Entity
{
    public:
        Player(int x, int y, int z, int vx, int vy, int vz, int dx, int dy, int dz, float health, int angle, bool isCollider, bool state);
        void update(float x, float y);
    private:
};