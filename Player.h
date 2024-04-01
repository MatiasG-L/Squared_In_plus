#include "raylib.h"

class Player{
    private:
    float speed;
    float yVelocity = 0;
    float Gravity = 1;
    
    public:
    Vector2 position;
    bool isGrounded;
    float width = 100;
    float height = 100;
    Rectangle Rec;
   
    Player(){
        position.x = 100;
        position.y = 100;
        speed = 3;
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