#include "raylib.h"
class WallExpanders{
  public:
    Vector2 position;
    int width;
    int height;
    float growthSizeH;
    float growthSizeW;
    bool positionChange;
    Vector2 resetPos;
    
    WallExpanders(Vector2 position, int height, int width, bool positionChange){
        this->height = height;
        this->width = width;
        this->position = position;
        this->positionChange = positionChange;
        growthSizeH = height;
        growthSizeW = width;
        resetPos = position;
    }    
    
    reset(){
        growthSizeH = height;
        growthSizeW = width;
    }    
};