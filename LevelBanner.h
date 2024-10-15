#include "raylib.h"
class LevelBanner{
   public:
    Vector2 position;
    int width, height;
    std::string levelName;

    LevelBanner(Vector2 position, int width, int height, std::string levelName){
        this->position = position;
        this->height = height;
        this->width = width;
        this->levelName = levelName;
        
    }    

};