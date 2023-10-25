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
#include <vector>

using namespace std;
int main() {
    
    // Initialize Raylib and your game objects
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Waffles Big Day OUt");
    int framesCounter = 0;
    float stamina = 300;
    Color staminaBorderColor = DARKGRAY;
    Color staminaFillColor = GREEN;

    // Initialize waffle
    Waffle waffle(Vector2{1, screenHeight - 32}); // because of the origin being 0,0 being the top left); // Create an instance of the Waffle class
    waffle.initializeAnimations();

    // Initialize enemys
    vector<Rat> rats;
    const int numRats = 5; // You can change this to the number of rats you want

    for (int i = 0; i < numRats; i++) {
        Vector2 startingPosition = {(float)GetRandomValue(0, 10000), screenHeight - 32};
        Rat rat(startingPosition);
        rat.initializeAnimations();
        rats.push_back(rat);
    }

    // boolean values for enemy collisions
    vector<bool> isWaffleHit (numRats, false); // not in contact by default
    vector<bool> ratDead(numRats, false);
    bool game_restart = false;
    bool logo = true; // logo screen
    bool intro = false;
    bool game = false;



    // camera stuff
    Camera2D camera = waffle.getWafflesCamera();

    // Stamina bar
    Rectangle staminaBar = {camera.target.x + 10, camera.target.y + 10, stamina, 20};
    int staminaSubtract = 0;

    // animation stuff
    Texture2D background = LoadTexture("Images/2D_courtSt.png");
    Texture2D titlePic = LoadTexture("Images/title.png");
    Texture2D logoPic = LoadTexture("Images/logo.png");

    // sound stuff
    InitAudioDevice();
    waffle.initializeSounds();

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


        else if (game){
        ClearBackground(RAYWHITE);

        Vector2 wafflePos = waffle.getWafflePos();
        if (wafflePos.x < 6500){ // camera bounds
        camera.target = (Vector2){wafflePos.x+32,screenHeight};// camera follows the Waffle
        }
        
        // Hitboxes
        Rectangle waffleHitbox = waffle.getHitbox(); // next make a hit animation that hits the rat and kills them first try by using a tiny rectangle if a button is pushed be made and a hitting animation plays 
        for (int i = 0; i < numRats; i++) {
        Rectangle rat1Hitbox = rats[i].getHitbox();
        
        // enemy collisons
        // if you add a vector of rats just change some stuff around
        if (!ratDead[i]){
        isWaffleHit[i] = CheckCollisionRecs(waffleHitbox, rat1Hitbox); // checks if rat 1 has collided with waffle
        }
        if (isWaffleHit[i] && !ratDead[i]){
            stamina -= 10;
        }
        }

        //ratDead[i] = rats[i].Dead(); //when we want the rat to die

        staminaSubtract = waffle.getIsMoving();
        if (staminaSubtract){
            stamina -= 0.05; // update by how much movement subtracts the stamina
        }

        if (stamina <= 0) {
        game_restart = waffle.lose(); // when waffle runs out of stamina
        }
        
        // Update game objects
        waffle.Update();

         for (Rat& rat : rats) {
            rat.Update();
        }

        // Stamina bar
        staminaBar.x = camera.target.x - 100; // puts it in top corner of screen and makes it follow waffle
        staminaBar.y = camera.target.y - 400;
        //staminaBar = {camera.target.x, camera.target.y, stamina, 20};

        // Set camera mode to follow the target
        BeginMode2D(camera); 
        
        // background
        DrawTexture(background, -(float)screenWidth /6, 0, WHITE);
        DrawText("move waffle with arrow keys", 10, 10, 20, WHITE);
        waffle.doAnimations();
         for (Rat& rat : rats) {
            rat.doAnimations();
        }

        // Stamina bar
        float greenWidth = (stamina / 300.0f) * (staminaBar.width - 4); // update change in stamina (-4 for the border)
        
        DrawRectangle(staminaBar.x, staminaBar.y, greenWidth, staminaBar.height - 4, LIME); // stamina bar

        DrawRectangleLinesEx(staminaBar, 5, BLACK); // stamina bar outline

        
        EndMode2D();
        EndDrawing();
    }
    }
    UnloadTexture(background);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}
