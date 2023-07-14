#include <vector>

using namespace std;

class Pixel{
    public:
        int r, g, b, a;
        Pixel(int r, int g, int b, int a);
};

class Sprite{
    public:
        int width, height;
        vector<Pixel> pixels;
        int id;
        float scale;
        float rotation;
        Sprite(int id, int width, int height, float scale, float rotation);
};