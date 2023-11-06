/**
*  @file: main.cc
*  @author: cashcraf
*  @date: 2023-10-16 
*  @brief: Waffles big day out (a game for sam) main file
* 
*/
 
// can now compile with make linux or make windows or make web
// make clean to clear the executibles and make run to run on linux or web

#include "raylib.h"
#include <stdlib.h>
#include "Headers/animation.h"
#include "Headers/camera.h"
#include "Headers/rat.h"
#include "Headers/waffle.h"
#include "Headers/game.h"

#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif


// play web version with python3 -m http.server 
// then go to http://localhost:8000/waffleWeb.html

using namespace std;

   // Initialize Raylib and your game objects
    const int screenWidth = 800;
    const int screenHeight = 450;


    int framesCounter = 0;
    
    Game* level1 = nullptr;

    Game* level2 = nullptr;

    Game* level3 = nullptr;
    

    // boolean values for screens
    bool logo = true; // logo screen
    bool intro = false;
    bool game = false;

    bool level1On = true;
    bool level1Restart = false;
    bool level1Win = false;

    bool level2On = false;
    bool level2Restart = false;
    bool level2Win = false;

    bool level3On = false;
    bool level3Restart = false;
    bool level3Win = false;

    // animation stuff
    Texture2D titlePic;
    Texture2D logoPic;;

    // for web
    //bool spaceBar = false;

// For the web
void UpdateDrawFrame(void);   

int main() { 
    
    InitWindow(screenWidth, screenHeight, "Waffles Big Day OUt");
    InitAudioDevice();
    level1 = new Game(5,1);
    level1->initializeGame();

    Game* level2 = new Game(5,2);
    level2->initializeGame();

    Game* level3 = new Game(5,3);
    level3->initializeGame();

    // animation stuff
    titlePic = LoadTexture("Images/title.png");
    logoPic = LoadTexture("Images/logo.png");



    #ifdef PLATFORM_WEB
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);

    #else

    // fps
    SetTargetFPS(60);

    // audio
    //InitAudioDevice();

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
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(titlePic, 0, 0, WHITE);
        EndDrawing();

        if (IsKeyPressed(KEY_SPACE)) {
            intro = false;
            game = true;
        }
    }


        else if (game) {
            if (level1On) {
                level1->updateGame();
                level1->drawGame();

                if (!level1Win){
                level1Restart = level1->checkLose();
                }

                if (level1Restart && !level1Win) {
                    framesCounter++;
                    if (framesCounter >= 120) // wait 2 seconds then reset the level
                    {
                    // Delete the existing level1 and create a new one
                    level1->cleanUp();
                    delete level1;
                    level1 = new Game(5, 1);
                    level1->initializeGame();
                    level1Restart = false;
                    framesCounter = 0;
                    }
                    
                }
                
    
                level1Win = level1->checkWin(); // checks if waffle has won

                if (level1Win) {
                    framesCounter++;
                    if (framesCounter >= 120) // wait 2 seconds then win the level
                    {
                        level1->cleanUp();
                        delete level1;
                        level2On = true;
                        level1On = false;
                        framesCounter = 0;
                    }
                }
            }


            else if (level2On){
                level2->updateGame();
                level2->drawGame();

                if (!level2Win){
                level2Restart = level2->checkLose();
                }

                if (level2Restart && !level2Win) {
                    framesCounter++;
                    if (framesCounter >= 120) // wait 2 seconds then reset the level
                    {
                        // Delete the existing level1 and create a new one
                        delete level2;
                        level2 = new Game(5, 2);
                        level2->initializeGame();
                        level2Restart = false;
                        framesCounter = 0;
                    }
                    
                }
                
    
                level2Win = level2->checkWin(); // checks if waffle has won

                if (level2Win) {
                     framesCounter++;
                     if (framesCounter >= 120) // wait 2 seconds then win the level
                     {
                    level2->cleanUp();
                    delete level2;
                    level3On = true;
                    level2On = false;
                    framesCounter = 0;
                    }
                }
            }

            else if (level3On){
                level3->updateGame();
                level3->drawGame();

                if (!level3Win){
                level3Restart = level3->checkLose();
                }

                if (level3Restart && !level3Win) {
                    framesCounter++;
                    if (framesCounter >= 120) // wait 2 seconds then reset the level
                    {
                        // Delete the existing level1 and create a new one
                        delete level3;
                        level3 = new Game(5, 3);
                        level3->initializeGame();
                        level3Restart = false;
                        framesCounter = 0;
                    }
                    
                }
                
    
                level3Win = level3->checkWin(); // checks if waffle has won

                if (level3Win) {
                     framesCounter++;
                     if (framesCounter >= 120) // wait 2 seconds then win the level
                     {
                    level2->cleanUp();
                    delete level3;
                    //level4On = true; // dont know if I want a level 4 or a winning screen or to quit yet
                    level3On = false;
                    framesCounter = 0;
                    }
                }
            }
             

    }
    }
    CloseWindow();
    CloseAudioDevice();
    #endif
    return 0;
}

#ifdef PLATFORM_WEB
// One iteration of main loop of my game for web
void UpdateDrawFrame() {
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
        
    
        if (IsKeyDown(KEY_SPACE)) {
            intro = false;
            game = true;
            }
        
    }


        else if (game) {
            if (level1On) {
                level1->updateGame();
                level1->drawGame();

                if (!level1Win){
                level1Restart = level1->checkLose();
                }

                if (level1Restart && !level1Win) {
                    framesCounter++;
                    if (framesCounter >= 120) // wait 2 seconds then reset the level
                    {
                    // Delete the existing level1 and create a new one
                    level1->cleanUp();
                    delete level1;
                    level1 = new Game(5, 1);
                    level1->initializeGame();
                    level1Restart = false;
                    framesCounter = 0;
                    }
                    
                }
                
    
                level1Win = level1->checkWin(); // checks if waffle has won

                if (level1Win) { // somewhere here it gives a devide by 0 
                    framesCounter++;
                    if (framesCounter >= 120) // wait 2 seconds then win the level
                    {
                        level1->cleanUp(); 
                        delete level1; 
                        level2On = true;
                        level1On = false;
                        framesCounter = 0;
                    }
                }
            }


            else if (level2On){
                level2->updateGame();
                level2->drawGame(); // this is the issue

                if (!level2Win){
                level2Restart = level2->checkLose();
                }

                if (level2Restart && !level2Win) {
                    framesCounter++;
                    if (framesCounter >= 120) // wait 2 seconds then reset the level
                    {
                        // Delete the existing level1 and create a new one
                        delete level2;
                        level2 = new Game(5, 2);
                        level2->initializeGame();
                        level2Restart = false;
                        framesCounter = 0;
                    }
                    
                }
                
    
                level2Win = level2->checkWin(); // checks if waffle has won

                if (level2Win) {
                     framesCounter++;
                     if (framesCounter >= 120) // wait 2 seconds then win the level
                     {
                    level2->cleanUp();
                    delete level2;
                    level3On = true;
                    level2On = false;
                    framesCounter = 0;
                    }
                }
             }

            else if (level3On){
                level3->updateGame();
                level3->drawGame();

                if (!level3Win){
                level3Restart = level3->checkLose();
                }

                if (level3Restart && !level3Win) {
                    framesCounter++;
                    if (framesCounter >= 120) // wait 2 seconds then reset the level
                    {
                        // Delete the existing level1 and create a new one
                        delete level3;
                        level3 = new Game(5, 3);
                        level3->initializeGame();
                        level3Restart = false;
                        framesCounter = 0;
                    }
                    
                }
                
    
                level3Win = level3->checkWin(); // checks if waffle has won

                if (level3Win) {
                     framesCounter++;
                     if (framesCounter >= 120) // wait 2 seconds then win the level
                     {
                    level2->cleanUp();
                    delete level3;
                    //level4On = true; // dont know if I want a level 4 or a winning screen or to quit yet
                    level3On = false;
                    framesCounter = 0;
                    }
                }
            }
             

    }
}
#endif