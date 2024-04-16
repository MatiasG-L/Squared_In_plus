#include "raylib.h"

class Platform{
private:


public:  
float width;
float height;
Vector2 position;

Rectangle rec;

Platform(float posX, float posY, float width, float height){
    this->width = width;
    this->height = height;
    position.x = posX;
    position.y = posY;
    
    rec = {posX, posY, width, height};
}


  
};