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
#include "Headers/game.h"

using namespace std;
int main() {
    
    // Initialize Raylib and your game objects
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Waffles Big Day OUt");
    InitAudioDevice();
    int framesCounter = 0;
    Game* level1 = new Game(5,1);
    level1->initializeGame();
    // Game level2(5,2);
    // level2.initializeGame();
    

    // boolean values for screens
    bool logo = true; // logo screen
    bool intro = false;
    bool game = false;
    bool level1On = true;
    bool level1Restart = false;
    bool level1Win = false;
    bool level2On = false;
    

    // animation stuff
    Texture2D titlePic = LoadTexture("Images/title.png");
    Texture2D logoPic = LoadTexture("Images/logo.png");


    // fps
    SetTargetFPS(60);


    // Set up the game loop
    while (!WindowShouldClose()) {
        if (logo){
        BeginDrawing();
        
        ClearBackground(WHITE);
        DrawTexture(logoPic, 0, 0, WHITE);

        EndDrawing();

        framesCounter++;    // Count frames

            // Wait for 2 seconds (120 frames) before jumping to TITLE screen
            if (framesCounter > 120)
            {
             // Exit the title screen after 2 seconds
            logo = false;
            intro = true;
            framesCounter = 0;
        }
        }

    else if (intro) {
        ClearBackground(RAYWHITE);

        DrawTexture(titlePic, 0, 0, WHITE);
        EndDrawing();

        if (IsKeyPressed(KEY_SPACE)) {
            intro = false;
            game = true;
        }
    }


        else if (game) {
            if (level1On && !level1Win) {
                level1->updateGame();
                level1->drawGame();
                level1Restart = level1->checkLose();

                if (level1Restart) {
                    framesCounter++;
                    if (framesCounter >= 120) // wait 2 seconds then reset the level
                    {
                    // Delete the existing level1 and create a new one
                    delete level1;
                    level1 = new Game(5, 1);
                    level1->initializeGame();
                    level1Restart = false;
                    framesCounter = 0;
                    }
                    
                }

                level1Win = level1->checkWin(); // do check win

                if (level1Win && !level1Restart) {
                    delete level1;
                    level2On = true;
                    level1On = false;
                    CloseWindow();
                }
            }
            // if (level2On){
            //     // same as level 1 
            // }


    }
    }
    CloseWindow();
    CloseAudioDevice();
    return 0;
}
