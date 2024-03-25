#include "raylib.h"

class Player{
    private:
    float speed;
    float yVelocity = 0;
    
    public:
    Vector2 position;
    bool isGrounded;
   
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
};