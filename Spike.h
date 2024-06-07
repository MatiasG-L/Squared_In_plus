#include "raylib.h"

class Spike{
    public:
        float width;
        float height;
        Vector2 position;
        
        typedef struct Verticies{
            Vector2 Top;
            Vector2 BottomLeft;
            Vector2 BottomRight;
        } Verticies;
   
        Verticies corners;  
        
        Spike(float width, float height, Vector2 position){
            this->width = width;
            this->height = height;
            this->position = position;
            
            corners = {{position.x, position.y-height/2}, {position.x - width/2, position.y+height/2},{position.x + width/2, position.y+height/2}};
        }
};    