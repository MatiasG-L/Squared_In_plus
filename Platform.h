#include "raylib.h"

class Platform{
private:


public:  
float width;
float height;
Vector2 position;

Platform(float posX, float posY, float width, float height){
    this->width = width;
    this->height = height;
    position.x = posX;
    position.y = posY;
}


  
};