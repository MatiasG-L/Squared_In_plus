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
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1000;
    const int screenHeight = 800;
    
 
    

    InitWindow(screenWidth, screenHeight, " SQUARED IN ");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Player player;


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
         if(!player.isGrounded) player.set_yVelocity(player.get_yVelocity() - 1);
         else player.set_yVelocity(0);
         player.position.y += -player.get_yVelocity();
         
         if(player.position.y > 600) {player.isGrounded = true; player.position.y = 601;}
         else player.isGrounded = false;
            
            
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
          
             DrawRectangle(player.position.x, player.position.y, 100, 100 , BLACK);
             DrawRectangle(0, 700 ,1000 ,300 , BLACK);
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