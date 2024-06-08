#include "raylib.h"

class Spike{
    public:
    //variables that hold the spikes width and height values
        float width;           
        float height;           
        Vector2 position;       
        //decleration of a struct that hold the vectors *coordinates* of the spikes corners used for collision
        typedef struct Verticies{
            Vector2 Top;
            Vector2 BottomLeft;
            Vector2 BottomRight;
        } Verticies;
        //creation of a instance of the previously declared struct
        Verticies corners;  
        
        //parametarized construtor of the spike class
        Spike(float width, float height, Vector2 position){
            //sets the instance variables to the given paramaters
            this->width = width;
            this->height = height;
            this->position = position;
            //initializes the corners instance to the newly set varibles
            corners = {{position.x, position.y-height/2}, {position.x - width/2, position.y+height/2},{position.x + width/2, position.y+height/2}};
        }
};    