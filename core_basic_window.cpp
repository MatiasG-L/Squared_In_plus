/*******************************************************************************************
*
*   raylib [textures] example - Texture source and destination rectangles
*
*   Example originally created with raylib 1.3, last time updated with raylib 1.3
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2024 Ramon Santamaria (@raysan5)   
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
    const int screenWidth = 1200;
    const int screenHeight = 900;
    char xposition[20];
    char yposition[20];
    char groundState[20];
 
    

    InitWindow(screenWidth, screenHeight, " SQUARED IN ");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Player player;
    Platform platform1(100, 500, 150, 300);
    Platform platform2(300, 500, 100, 300);
    Platform platform3(650, 600, 200, 300);
    Platform platform4(1000, 600, 150, 300);

    //vector of platform objects to be considered for collision
    std::vector<Platform> collidables;
    collidables.push_back(platform1);
    collidables.push_back(platform2);
    collidables.push_back(platform3);
    collidables.push_back(platform4);
    
    SetTargetFPS(60);
    
    player.setSpeed(10);


    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
         if (IsKeyDown(KEY_RIGHT)) player.position.x += player.getSpeed();
         if(IsKeyDown(KEY_LEFT)) player.position.x -= player.getSpeed();
         if(IsKeyPressed(KEY_UP) && player.isGrounded) {player.isGrounded = false; player.set_yVelocity(20);}
         
         if(IsKeyPressed(KEY_R) ) {player.position = {200,100}; player.isGrounded = false; player.set_yVelocity(0);}
         
         player.Rec = {player.position.x, player.position.y, player.width, player.height};
         
         // collision
         
         
         // wall collisiion
         for(Platform collider : collidables){
              if(player.position.x < collider.position.x + collider.width && player.position.y > collider.position.y - player.width/2 && player.position.x > collider.position.x + collider.width/2){
                 player.position.x = collider.position.x + collider.width + 1;
             }
             if(player.position.x > collider.position.x - player.width && player.position.y > collider.position.y - player.width/2 && player.position.x < collider.position.x + collider.width/2){
                 player.position.x = collider.position.x - player.width - 1;
             }
             
         }
         
         //floor collision
        bool grounded = false;
        for(Platform collider : collidables){
            
             if(player.position.x < collider.position.x + collider.width && player.position.x > collider.position.x - player.width){
                 if((player.position.y > collider.position.y - collider.height/2)) {
                        if(CheckCollisionRecs(player.Rec, collider.rec) && player.position.y < collider.position.y){
                            player.isGrounded = true;
                            player.position.y = collider.position.y - (collider.height/2) + (player.height/2);
                        }
                        grounded = true;
                 }
            }
        }
        if(!grounded) player.isGrounded = false;
            
             
        
         
         
         
         
          // deals with velocity while the player is grounded
          if(!player.isGrounded) player.set_yVelocity(player.get_yVelocity() - player.getGravity());
          else player.set_yVelocity(0);
          player.position.y += -player.get_yVelocity();
         
         //outputs player varibles for debbuging
         sprintf(groundState, "Ground state: %d", player.isGrounded);   
         sprintf(xposition, "yVelocity: %f", player.get_yVelocity());   
         sprintf(yposition, "y:  %f", player.position.y);
            
            
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
             for(Platform collider : collidables){
                 DrawRectanglePro(collider.rec, {0,0}, 0, GRAY);
                 DrawCircle(collider.position.x , collider.position.y , 10, BLACK);
                 DrawCircle(collider.position.x + collider.width, collider.position.y, 10, BLACK);
                 DrawCircle(collider.position.x + collider.width, collider.position.y + collider.height, 10, BLACK);
                 DrawCircle(collider.position.x, collider.position.y + collider.height, 10, BLACK);
             }
             
             DrawRectanglePro(player.Rec, {0,0}, 0, BLACK);
             DrawCircle(player.position.x , player.position.y , 10, WHITE);
             
             
             
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