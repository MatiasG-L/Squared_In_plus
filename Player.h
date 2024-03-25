#include "raylib.h"

class Player{
    private:
    float speed;
    float yVelocity = 0;
    float Gravity = 2;
    
    public:
    Vector2 position;
    bool isGrounded;
    float width = 100;
    float height = 100;
   
    Player(){
        position.x = 100;
        position.y = 100;
        speed = 5;
        isGrounded = false;
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