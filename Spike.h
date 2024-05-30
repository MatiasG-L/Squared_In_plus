#include "raylib.h"

class Spike{
    public:
        float width;
        float height;
        Vector2 position;
        
        Spike(float width, float height, Vector2 position){
            this->width = width;
            this->height = height;
            this->position = position;
        }
};    