#include "raylib.h"

class Player{
    private:
    float speed = 2;
    float yVelocity = 0;
    float Gravity = 1;
    
    public:
    // player attributes
    float width = 100;
    float height = 100;
    float Friction = 1.15;
    Rectangle Rec;
    float jumpStr = 20;
    float acceleration = 0.5;
    // player state
    float xVelocity = 0;
    bool isGrounded; 
    Vector2 position;

   
    Player(){
        position.x = 100;
        position.y = 100;
        speed = 2;
        isGrounded = false;
        
        Rec = {position.x, position.y, width, height};
    }
 
    float getSpeed(){
        return speed;
    }
    void setSpeed(float speed){
        this->speed = speed;
    }
    float get_yVelocity(){
        return yVelocity;
    }
    void set_yVelocity(float yVelocity){
        this->yVelocity = yVelocity;
    }
    float getGravity(){
        return Gravity;
    }
    void setGravity(float Gravity){
        this->Gravity = Gravity;
    }
    
};