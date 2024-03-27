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
#include <iostream>
#include <string>

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
 
    

    InitWindow(screenWidth, screenHeight, " SQUARED IN ");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Player player;
    Platform platform1(-50, 600, 600, 300);
    Platform platform2(800, 600, 600, 300);


    std::vector<Platform> collidables;
    collidables.push_back(platform1);
    collidables.push_back(platform2);
    
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
         
         if(!player.isGrounded) player.set_yVelocity(player.get_yVelocity() - player.getGravity());
         else player.set_yVelocity(0);
         player.position.y += -player.get_yVelocity();
         
         // collision
         
         for(Platform collider : collidables){
             
             if((player.position.y > collider.position.y - (collider.height/2) + (player.height/2)) && (player.position.x < collider.position.x + collider.width && player.position.x > collider.position.x - player.width)) {
                if(player.position.y < collider.position.y){
                    player.isGrounded = true;
                    player.position.y = collider.position.y - (collider.height/2) + (player.height/2)+1;
                }
                else player.isGrounded = false;
            }
         
         }
         
         sprintf(xposition, "x:  %f", player.get_yVelocity());   
         sprintf(yposition, "y:  %f", player.position.y);
            
            
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
          
             
             DrawRectangle(player.position.x, player.position.y, player.width, player.height, BLACK);
             DrawRectanglePro(platform1.rec, {0,0}, 0, GRAY);
             DrawRectanglePro(platform2.rec, {0,0}, 0, GRAY);
             DrawText(xposition, 100, 100, 30, BLACK); 
             DrawText(yposition, 100, 200, 30, BLACK); 
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