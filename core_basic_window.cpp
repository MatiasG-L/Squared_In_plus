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
    
 
    

    InitWindow(screenWidth, screenHeight, " SQUARED IN ");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Player player;
    Platform platform1(200, 600, 600, 300);
    //player.position.x = platform1.position.x;
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
         if((player.position.y > platform1.position.y - (platform1.height/2) + (player.height/2)) && (player.position.x < platform1.position.x + platform1.width && player.position.x > platform1.position.x - player.width)) {
             if(player.position.y < platform1.position.y){
                 player.isGrounded = true;
                 player.position.y = platform1.position.y - (platform1.height/2) + (player.height/2)+1;
             }
         }
         else player.isGrounded = false;
            
            
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
          
             Rectangle rec = {platform1.position.x, platform1.position.y, platform1.width, platform1.height};
             DrawRectangle(player.position.x, player.position.y, player.width, player.height, BLACK);
             DrawRectanglePro(rec, {0 , platform1.position.y - platform1.height*2}, 0, GRAY);
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