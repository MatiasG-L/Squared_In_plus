/*******************************************************************************************
*
*   SQUARED IN REMASTERED IN C++, USING: RAYLIB 5.0
*
*   IM SOOO COOL (MISIRABLE)  
*   
*   Challange: No tutorials or videos all logic and gameplay must be original (documentation isnt included) 
*
********************************************************************************************/

#include <vector>
#include <string>
#include <cmath>

#include "raylib.h"
#include "Player.h"
#include "Platform.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 900;
    char xposition[20];
    char yposition[20];
    char groundState[20];
 
    

    InitWindow(screenWidth, screenHeight, " SQUARED IN++");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Player player;
    Platform platform1(0, 800, 400, 100);
    Platform platform2(1000, 500, 200, 100);
    Platform platform3(400, 600, 200, 300);
    

    //vector of platform objects to be checked for collision
    std::vector<Platform> collidables;
    collidables.push_back(platform1);
    collidables.push_back(platform2);
    collidables.push_back(platform3);
    
    //boolean in charge of ensuring the player can place squares
    bool canPlace = false;

    //limits fps for more univarsal experience
    SetTargetFPS(60);
    
    player.setSpeed(10);


    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
    // Update
        
        
        //toggles the ability to place blocks
        if(IsKeyPressed(KEY_P) && !canPlace) canPlace = true;
        else if(IsKeyPressed(KEY_P)) canPlace = false;
        
        //creates a platform at mouse X,Y
        if(IsMouseButtonDown(0) && canPlace){
            Platform CST(GetMouseX()-CST.width/2, GetMouseY()-CST.height/2, 100, 100);
            collidables.push_back(CST);
            canPlace = false;
        }
        
        
        //allows dragging and resizing of objects
        bool reSize = false;
        bool isDrag = false;
        for(int i = 0; i < collidables.size(); i++){
           if(IsMouseButtonDown(0)){
               // handles the dragging
               if(GetMouseX() < collidables[i].position.x + collidables[i].width && GetMouseX() > collidables[i].position.x && GetMouseY() < collidables[i].position.y + collidables[i].height && GetMouseY() > collidables[i].position.y){     
                   isDrag = true;
                   SetMouseCursor(9);
                   collidables[i].position.x = (GetMouseX() + (collidables[i].position.x - GetMouseX())) + GetMouseDelta().x;
                   collidables[i].position.y = (GetMouseY() + (collidables[i].position.y - GetMouseY())) + GetMouseDelta().y;       
               }
               // handles the resizing
               if(GetMouseX() < collidables[i].position.x + collidables[i].width + 20 && GetMouseX() > collidables[i].position.x + collidables[i].width - 20 && GetMouseY() < collidables[i].position.y + collidables[i].height + 20 && GetMouseY() > collidables[i].position.y + collidables[i].height - 20){
                   reSize = true;         
                   collidables[i].width += GetMouseDelta().x; 
                   collidables[i].height += GetMouseDelta().y; 
                   SetMouseCursor(7);
               }
               
           }
           if(!reSize && !canPlace && !isDrag) SetMouseCursor(1); // sets cursor to normal if player cant place and drag and resize
           else if(!reSize && !isDrag) SetMouseCursor(3); // sets the cursor to place if you can place
        }
        
        
        
        
        
        
        
        
        // player input 
         if (IsKeyDown(KEY_RIGHT)) player.xVelocity = player.getSpeed();
         else if(IsKeyDown(KEY_LEFT)) player.xVelocity = -player.getSpeed();
         else if(player.xVelocity > 0) player.xVelocity /= player.Friction;
         else if(player.xVelocity < 0) player.xVelocity /= player.Friction;
         
         if(IsKeyDown(KEY_UP) && player.isGrounded) {player.set_yVelocity(player.jumpStr);player.isGrounded = false;}
         
         if(IsKeyPressed(KEY_R) ) {player.position = {200,100}; player.isGrounded = false; player.set_yVelocity(0);}
         
         player.Rec = {player.position.x, player.position.y, player.width, player.height};
         
         
         
      
         
        // collision
        bool grounded = false;
        for(Platform collider : collidables){
            
            // wall collision
             if(player.position.x < collider.position.x + collider.width && (player.position.y > collider.position.y - player.width/2 && player.position.y < collider.position.y + collider.height - 40) && player.position.x > collider.position.x + collider.width/2){
                 player.position.x = collider.position.x + collider.width + 1;
             }
             if(player.position.x > collider.position.x - player.width && (player.position.y > collider.position.y - player.width/2 && player.position.y < collider.position.y + collider.height - 40) && player.position.x < collider.position.x + collider.width/2){
                 player.position.x = collider.position.x - player.width - 1;
             }
             
            //floor collision
             if(player.position.x < collider.position.x + collider.width && player.position.x > collider.position.x - player.width){
                 if((player.position.y > collider.position.y - player.height-1 && player.position.y < collider.position.y + collider.height/2)) {
                     if(CheckCollisionRecs(player.Rec, collider.rec)){
                        player.position.y = collider.position.y - player.height;
                        player.isGrounded = true;
                     }
                     grounded = true;
                 }
             }
            
            //roof collision
            if(player.position.x < collider.position.x + collider.width && player.position.x > collider.position.x - player.width){
                 if((player.position.y > collider.position.y + collider.height -20)) {
                     if(CheckCollisionRecs(player.Rec, collider.rec)){
                        player.position.y = collider.position.y + collider.height;
                        player.set_yVelocity(0);
                     }
                 }
             }
            
        }
        if(!grounded) player.isGrounded = false;
            
             
        
         
         
         
         
          // deals with velocity 
          if(!player.isGrounded) player.set_yVelocity(player.get_yVelocity() - player.getGravity());
          else player.set_yVelocity(0);
          player.position.y -= player.get_yVelocity();
          player.position.x += player.xVelocity;
            
         
         //outputs player varibles for debbuging
         sprintf(groundState, "Ground state: %d", player.isGrounded);   
         sprintf(xposition, "yVelocity: %f", player.get_yVelocity());   
         sprintf(yposition, "y:  %f", player.position.y);
            
            
      // Draw

        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            //draws a vector of plafrom objects
             for(int i = 0; i < collidables.size(); i++){
                 //updates the objects rec for accurate visuals
                 collidables[i].rec = {collidables[i].position.x, collidables[i].position.y, collidables[i].width, collidables[i].height};
                 
                 DrawRectanglePro(collidables[i].rec, {0,0}, 0, GRAY);
                 DrawCircle(collidables[i].position.x , collidables[i].position.y , 10, BLACK);
                 DrawCircle(collidables[i].position.x + collidables[i].width, collidables[i].position.y, 10, BLACK);
                 DrawCircle(collidables[i].position.x + collidables[i].width, collidables[i].position.y + collidables[i].height, 10, BLACK);
                 DrawCircle(collidables[i].position.x, collidables[i].position.y + collidables[i].height, 10, BLACK);
             }
             
             //draws player
             DrawRectanglePro(player.Rec, {0,0}, 0, BLACK);
             DrawCircle(player.position.x , player.position.y , 10, WHITE);
             
             
             //draws player state text
             DrawText(xposition, 100, 100, 30, BLACK); 
             DrawText(yposition, 100, 200, 30, BLACK); 
             DrawText(groundState, 100, 300, 30, BLACK);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
     
     

    // De-Initialization
    //--------------------------------------------------------------------------------------
      // Texture unloading

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}