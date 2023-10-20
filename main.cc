/**
*  @file: waffle.cc
*  @author: cashcraf
*  @date: 2023-10-16 
*  @brief: Waffles big day out (a game for sam) main file
* 
*/
 
// can now compile with make linux or make windows make clean to clear the executibles and make run to run on linux
#include "raylib.h"
#include <stdlib.h>
#include "Headers/animation.h"
#include "Headers/camera.h"
#include "Headers/rat.h"
#include "Headers/waffle.h"

using namespace std;
int main() {
    
    // Initialize Raylib and your game objects
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Waffles big day out");

    // Initialize waffle
    Waffle waffle(Vector2{1, screenHeight - 32}); // because of the origin being 0,0 being the top left); // Create an instance of the Waffle class
    waffle.initializeAnimations();

    // Initialize enemys
    Rat rat1(Vector2{1000, screenHeight - 32}); // Create an instance of the Rat class (screenHeight - 32 puts it at waffles height)
    rat1.initializeAnimations(); // maybe make a vector of rats or something 

    // boolean values for enemy collisions
    bool isRat1Hit = false; // not in contact by default
    bool rat1Dead = false;
    bool game_restart = false;


    // camera stuff
    Camera2D camera = waffle.getWafflesCamera();

    // animation stuff
    Texture2D background = LoadTexture("Images/2D_courtSt.png");

    // sound stuff
    InitAudioDevice();

    // fps
    SetTargetFPS(60);

    // Set up the game loop
    while (!WindowShouldClose()) {
        waffle.initializeSounds();
        Vector2 wafflePos = waffle.getWafflePos();
        camera.target = (Vector2){wafflePos.x+32,screenHeight};// camera follows the Waffle
        Rectangle waffleHitbox = waffle.getHitbox(); // next make a hit animation that hits the rat and kills them first try by using a tiny rectangle if a button is pushed be made and a hitting animation plays 
        Rectangle rat1Hitbox = rat1.getHitbox();
        
        // enemy collisons
        // if you add a vector of rats just change some stuff around
        if (!rat1Dead){
        isRat1Hit = CheckCollisionRecs(waffleHitbox, rat1Hitbox); // checks if rat 1 has collided with waffle
        }
        if (isRat1Hit){
            rat1Dead = rat1.Dead(); // another debug placeholder 
            bool game_restart = waffle.lose(); // we dont want waffle to lose if hit once but this is a placeholder game restart will be true if you lose

        }

        // Update game objects
        waffle.Update();
        rat1.Update();
    
        // Handle user input (e.g., checking for key presses)

        // Clear and draw game objects
        BeginDrawing();
        BeginMode2D(camera); // Set camera mode to follow the target

        // background
        ClearBackground(WHITE);
        DrawTexture(background, -(float)screenWidth /6, 0, WHITE);
        DrawText("move waffle with arrow keys", 10, 10, 20, WHITE);
        waffle.doAnimations();
        rat1.doAnimations();

        EndMode2D();
        EndDrawing();
    }
    UnloadTexture(background);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
