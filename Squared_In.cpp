/**************************************************************************************************************
*
*   SQUARED IN REMASTERED IN C++, USING: RAYLIB 5.0
*
*   IM SOOO COOL (MISIRABLE)  
*   
*   Challange: No tutorials or videos, all logic and gameplay must be original and made by me (raylib documentation isnt included) 
*
**************************************************************************************************************/



     //---------------------------------------------------------------------------//
    //  NOTE:                                                                    //            
   //     when subtracting from an objects position on the y axis; it will      //
  //      appear to be moving up and vise versa meaning that, up is a          // 
 //       lower value or negative, while down is a positive or higher number  // 
//---------------------------------------------------------------------------//



#include <vector>
#include <string>
#include <cmath>

#include "GameMethods.cpp"
#include "WallExpanders.h"
#include "raylib.h"
#include "Player.h"
#include "Platform.h"
#include "Spike.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    //creating variables to set the screen dimentions to
    const int screenWidth = 1600;
    const int screenHeight = 900;
    //varibles for the debugging text
    char xposition[20];
    char yposition[20];
    char groundState[20];
 
    

    InitWindow(screenWidth, screenHeight, " SQUARED IN++ "); //initilisation of the window 

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    
    Player player;// creation the player object
    
    //creates a few platforms to start off the program with
    Platform platform1(0, 800, 400, 100);
    Platform platform2(1000, 500, 200, 100);
    Platform platform3(400, 600, 200, 300);
    
    
    WallExpanders wall1({0,0}, 900, 50, false);
    WallExpanders wall2({1550,0}, 900, 52, true);
    WallExpanders wall3({0,0}, 50, 1600, false);
    WallExpanders wall4({0,850}, 50, 1600, true);
    
    WallExpanders walls[] = {wall1, wall2, wall3, wall4};

    //vector of platform objects to be checked for collision
    std::vector<Platform> collidables;
    collidables.push_back(platform1);
    collidables.push_back(platform2);
    collidables.push_back(platform3);
    
    //vector for the player spawn
    Vector2 spawn = {100,100};
    
    //Vector for the exit door
    Vector2 exit = {500,500};
    
    
    //creates a spike object to start the program with
    Spike spike1(100,100,{500,300});
    //creates the vector of spike objects
    std::vector<Spike> spikes;
    //adds the spike to the vector 
    spikes.push_back(spike1);
    
    //boolean in charge of ensuring the player can place squares or spikes
    bool canPlace = false;
    bool canPlaceSpk = false;

    //limits fps for more univarsal experience
    SetTargetFPS(60);
    
    //setting the player speed
    player.setSpeed(10);
      //variables used for the dragging and resizing 
      bool dragging = false;
      bool resizing = false;
      //variables used for setting the mouse cursor while draggin or resizing
      bool reSize = false;
      bool isDrag = false;
      //variables used to hold the index of the object thats being dragged
      int index = -1;
      int index2 = -1;
      //variables used for the dragging and resizing spikes
      bool dragging2 = false;
      bool resizing2 = false;
      //used to toogle the level editor
      bool editor = false;
      //used for toggleling the pause menu
      bool pause = false;
      //used to drag spawn square
      bool draggingSpw = false;
      //used to drag the exit door
      bool draggingEXT = false;
      
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
    // Update
      if(!editor){
        for(int i = 0; i < 4; i++){
            walls[i].growthSizeH += 0.2;
            walls[i].growthSizeW += 0.2;
            if(walls[i].positionChange){
                walls[i].position.x -= 0.2;
                walls[i].position.y -= 0.2;
            }    
        }    
      } 
        if(IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_E)){
            if(editor) editor = false;
            else editor = true;
        }
        
      if(editor){
          
         if(GetMouseX() < exit.x + 100 && GetMouseX() > exit.x && GetMouseY() < exit.y + 200 && GetMouseY() > exit.y && IsMouseButtonPressed(0)){
            draggingEXT = true;
         }
         if(IsMouseButtonReleased(0) && draggingEXT){
            draggingEXT = false;
         }     
         if(draggingEXT){
            exit.x += GetMouseDelta().x;
            exit.y += GetMouseDelta().y;
         }
         
         if(GetMouseX() < spawn.x + 100 && GetMouseX() > spawn.x && GetMouseY() < spawn.y + 100 && GetMouseY() > spawn.y && IsMouseButtonPressed(0)){
            draggingSpw = true;
         }
         if(IsMouseButtonReleased(0) && draggingSpw){
            draggingSpw = false;
         }     
         if(draggingSpw){
            spawn.x += GetMouseDelta().x;
            spawn.y += GetMouseDelta().y;
         }         
          
        //toggles the ability to place blocks
        if(IsKeyPressed(KEY_P) && !canPlace) canPlace = true;
        else if(IsKeyPressed(KEY_P)) canPlace = false;
          
        //creates a platform at mouse X,Y
        if(IsMouseButtonDown(0) && canPlace){
            Platform CST(GetMouseX()-CST.width/2, GetMouseY()-CST.height/2, 100, 100);
            collidables.push_back(CST);
            canPlace = false;
        }
        //toggles the ability to place spikes
        if(IsKeyPressed(KEY_O) && !canPlaceSpk) canPlaceSpk = true;
        else if(IsKeyPressed(KEY_O)) canPlaceSpk = false;   
        
        //creates a platform at mouse X,Y
        if(IsMouseButtonDown(0) && canPlaceSpk){
            Spike CST(100, 100, {GetMouseX(), GetMouseY()});
            spikes.push_back(CST);
            canPlaceSpk = false;
        }
        //allows dragging and resizing of objects
        for(int i = 0; i < collidables.size(); i++){
            
            // handles the dragging
             if(GetMouseX() < collidables[i].position.x + collidables[i].width && GetMouseX() > collidables[i].position.x && GetMouseY() < collidables[i].position.y + collidables[i].height && GetMouseY() > collidables[i].position.y && IsMouseButtonPressed(0)){     
                 isDrag = true;
                 dragging = true;
                 index = i;
             }
             if(IsMouseButtonReleased(0) && dragging){
                 dragging = false;
                 index = -1;
                 isDrag = false;
             }     
             if(dragging){
                   SetMouseCursor(9);
                   collidables[index].position.x += GetMouseDelta().x/collidables.size();
                   collidables[index].position.y += GetMouseDelta().y/collidables.size();
             } 
               // handles the resizing
               if(GetMouseX() < collidables[i].position.x + collidables[i].width + 20 && GetMouseX() > collidables[i].position.x + collidables[i].width - 20 && GetMouseY() < collidables[i].position.y + collidables[i].height + 20 && GetMouseY() > collidables[i].position.y + collidables[i].height - 20 && IsMouseButtonPressed(0)){
                   reSize = true;   
                   resizing = true;
                   index = i;
               }
               if(IsMouseButtonReleased(0) && resizing){
                 resizing = false;
                 index = -1;
                 reSize = false;
               } 
               if(resizing){
                SetMouseCursor(7);
                collidables[index].width += GetMouseDelta().x/collidables.size(); 
                collidables[index].height += GetMouseDelta().y/collidables.size();
               } 
          //handles overlaping cursor instructions
           if(!reSize && !canPlace && !isDrag) SetMouseCursor(1); // sets cursor to normal if player cant place and drag and resize
           else if(!reSize && !isDrag) SetMouseCursor(3); // sets the cursor to place if you can place
           //deletes the block
           if(IsMouseButtonPressed(1)){
                if(GetMouseX() < collidables[i].position.x + collidables[i].width && GetMouseX() > collidables[i].position.x && GetMouseY() < collidables[i].position.y + collidables[i].height && GetMouseY() > collidables[i].position.y){
                    collidables.erase(collidables.begin() + i);
                }
           }
        }
        
        //allows dragging and resizing of spikes
        for(int i = 0; i < spikes.size(); i++){           
               // handles the dragging
               if(CheckCollisionPointTriangle({GetMouseX(),GetMouseY()},{spikes[i].position.x, spikes[i].position.y-spikes[i].height/2}, {spikes[i].position.x - spikes[i].width/2, spikes[i].position.y+spikes[i].height/2},{spikes[i].position.x + spikes[i].width/2, spikes[i].position.y+spikes[i].height/2}) && IsMouseButtonPressed(0)){     
                    isDrag = true;
                    dragging2 = true;
                    index2 = i;     
               }
               
               if(IsMouseButtonReleased(0) && dragging2){
                 dragging2 = false;
                 index2 = -1;
                 isDrag = false;
               }     
               if(dragging2){
                   SetMouseCursor(9);
                   spikes[index2].position.x += GetMouseDelta().x/spikes.size();
                   spikes[index2].position.y += GetMouseDelta().y/spikes.size();
               }
               
               // handles the resizing
               if(GetMouseX() < spikes[i].position.x + spikes[i].width/2 + 20 && GetMouseX() > spikes[i].position.x + spikes[i].width/2 - 20 && GetMouseY() < spikes[i].position.y + spikes[i].height/2 + 20 && GetMouseY() > spikes[i].position.y + spikes[i].height/2 - 20 && IsMouseButtonPressed(0)){
                   reSize = true;
                   resizing2 = true;
                   index2 = i;                     
               }     
               if(IsMouseButtonReleased(0) && resizing2){
                 resizing2 = false;
                 index2 = -1;
                 reSize = false;
               }     
               if(resizing2){
                   SetMouseCursor(7);
                   spikes[index2].width += GetMouseDelta().x*2/spikes.size(); 
                   spikes[index2].height += GetMouseDelta().y*2/spikes.size(); 
               }
               
           //handles overlaping cursor instructions
           if(!reSize && !(canPlace || canPlaceSpk) && !isDrag) SetMouseCursor(1); // sets cursor to normal if player cant place and drag and resize
           else if(!reSize && !isDrag) SetMouseCursor(3); // sets the cursor to place if you can place
           //deletes spike with a right click
           if(CheckCollisionPointTriangle({GetMouseX(),GetMouseY()},{spikes[i].position.x, spikes[i].position.y-spikes[i].height/2}, {spikes[i].position.x - spikes[i].width/2, spikes[i].position.y+spikes[i].height/2},{spikes[i].position.x + spikes[i].width/2, spikes[i].position.y+spikes[i].height/2}) && IsMouseButtonPressed(1)){
                spikes.erase(spikes.begin() + i);      
           }
           
        }
      } 
      
         
            // player input for moving 
            if (IsKeyDown(KEY_RIGHT) && player.xVelocity < player.getSpeed()) player.xVelocity += player.acceleration;
            else if(IsKeyDown(KEY_LEFT) && player.xVelocity > -player.getSpeed()) player.xVelocity -= player.acceleration;
            else if(player.xVelocity > 0) player.xVelocity /= player.Friction;
            else if(player.xVelocity < 0) player.xVelocity /= player.Friction;
         
         
         //player input for jump
         if(IsKeyDown(KEY_UP) && player.isGrounded) {player.set_yVelocity(player.jumpStr+abs(player.xVelocity)/2);player.isGrounded = false;}
         //player input to reset
         if(IsKeyPressed(KEY_R)){
             player.position = spawn; 
             player.isGrounded = false; 
             player.set_yVelocity(0);
             for(int i = 0; i < 4; i++){
                    walls[i].growthSizeH = walls[i].height;
                    walls[i].growthSizeW = walls[i].width;
                    walls[i].position = walls[i].resetPos;
             }
         }
         //updating the player Rec to have accurate visuals and collosion
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
        
        for(int i = 0; i < 4; i++){
            if(CheckCollisionRecs(player.Rec,{walls[i].position.x, walls[i].position.y, walls[i].growthSizeW, walls[i].growthSizeH})){
             player.position = spawn;
             player.isGrounded = false;
             player.set_yVelocity(0);
             for(int i = 0; i < 4; i++){
                    walls[i].growthSizeH = walls[i].height;
                    walls[i].growthSizeW = walls[i].width;
                    walls[i].position = walls[i].resetPos;
             }  
        }
        }    
        
        //checks for collision between the player and the exit
        if(CheckCollisionRecs(player.Rec,{exit.x, exit.y, 100, 200})){
             player.position = spawn;
             player.isGrounded = false;
             player.set_yVelocity(0);
             for(int i = 0; i < 4; i++){
                    walls[i].growthSizeH = walls[i].height;
                    walls[i].growthSizeW = walls[i].width;
                    walls[i].position = walls[i].resetPos;
             }  
        }
        
        //spike collision
        for(Spike spike : spikes){
            if(CheckCollisionPointRec(spike.corners.Top, player.Rec) || CheckCollisionPointTriangle(player.corners.BottomRight, spike.corners.Top, spike.corners.BottomLeft, spike.corners.BottomRight) || CheckCollisionPointTriangle(player.corners.BottomLeft, spike.corners.Top, spike.corners.BottomLeft, spike.corners.BottomRight)){
                player.position = spawn;
                player.isGrounded = false;
                player.set_yVelocity(0);
                for(int i = 0; i < 4; i++){
                    walls[i].growthSizeH = walls[i].height;
                    walls[i].growthSizeW = walls[i].width;
                    walls[i].position = walls[i].resetPos;
                }    
            }
        }    
          // stops player movement when level editor is active   
          if(!(editor || pause)){
            // moves the player based on y velocity which is calculated when the player is not grounded 
            if(!player.isGrounded) player.set_yVelocity(player.get_yVelocity() - player.getGravity());
            else player.set_yVelocity(0);
            player.position.y -= player.get_yVelocity();
            player.position.x += player.xVelocity;
          }  
         
         //outputs player varibles for debbuging
         sprintf(groundState, "Ground state: %d", player.isGrounded);   
         sprintf(xposition, "yVelocity: %f", player.get_yVelocity());   
         sprintf(yposition, "y:  %f", player.position.y);
            
            
      // Draw, where the scene actually gets rendered and drawn out

        BeginDrawing();

            ClearBackground(LIGHTGRAY);
            
            //draws a vector of plafrom objects
             for(int i = 0; i < collidables.size(); i++){
                 //updates the objects rec for accurate visuals
                 collidables[i].rec = {collidables[i].position.x, collidables[i].position.y, collidables[i].width, collidables[i].height};
                 //draws each platform at the index of the for loop
                 DrawRectanglePro(collidables[i].rec, {0,0}, 0, DARKGRAY);
                 if(editor){
                    //circles to show the corners of a platform
                    DrawCircle(collidables[i].position.x , collidables[i].position.y , 10, BLACK);
                    DrawCircle(collidables[i].position.x + collidables[i].width, collidables[i].position.y, 10, BLACK);
                    DrawCircle(collidables[i].position.x + collidables[i].width, collidables[i].position.y + collidables[i].height, 10, BLACK);
                    DrawCircle(collidables[i].position.x, collidables[i].position.y + collidables[i].height, 10, BLACK);
                 }
             }
             //draws a vector of spike of spike objects
             for(int i = 0; i < spikes.size(); i++){
                 //updates the corners struct of the spikes to make collison and visuals more accurate 
                 spikes[i].corners = {{spikes[i].position.x, spikes[i].position.y-spikes[i].height/2}, {spikes[i].position.x - spikes[i].width/2, spikes[i].position.y+spikes[i].height/2},  {spikes[i].position.x + spikes[i].width/2, spikes[i].position.y+spikes[i].height/2}};
                 //Draws each individual spike at the index of the for loop
                 DrawTriangle(spikes[i].corners.Top, spikes[i].corners.BottomLeft, spikes[i].corners.BottomRight, BLACK);
                 if(editor){
                    DrawCircle(spikes[i].position.x, spikes[i].position.y, 10, WHITE);
                 }
             }    
             
             //draws player
             DrawRectanglePro(player.Rec, {0,0}, 0, BLACK);
             //updates the players corners with his position
             player.corners = {{player.position.x, player.position.y}, {player.position.x + player.width, player.position.y}, {player.position.x + player.width, player.position.y + player.height}, {player.position.x, player.position.y + player.height}};
             if(editor){
                //draws a circle at the players origin for reference
                DrawCircle(player.position.x , player.position.y , 10, WHITE);
                DrawRectangle(spawn.x, spawn.y, 100, 100, RED);
             }
             //draws the exit door
             DrawRectangle(exit.x,exit.y, 100, 200, WHITE);
             if(editor){
                //draws player text that displays the players y coordinate, y velocity, and Grounded state for debbuging
                DrawText(xposition, 100, 100, 30, BLACK); 
                DrawText(yposition, 100, 200, 30, BLACK); 
                DrawText(groundState, 100, 300, 30, BLACK);
             }
             for(int i = 0; i < 4; i++){
                DrawRectangle(walls[i].position.x, walls[i].position.y, walls[i].growthSizeW, walls[i].growthSizeH, BLACK);
             }    
             
             
        //ends the drawing phase of the program     
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