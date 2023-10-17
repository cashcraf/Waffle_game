/**
*  @file: waffle.cc
*  @author: cashcraf
*  @date: 2023-10-16 
*  @brief: Waffles big day out (a game for sam) main file
*  (yes most of this should be in a header and a def file but I dont care I tried and it was hard)
*/
 
 // can now compile with make linux or make windows make clean to clear the executibles and make run to run on linux
#include "raylib.h"
#include <stdlib.h>
#include "animation.h"
#include "camera.h"

// Memory is auto deallocated after program ends so the rectangles dont need to be deallocated
// to compile: cc -o waffle.exe waffle.cc animation.cc camera.cc -lraylib -lGL -lpthread -ldl -lrt -lX11 -lm

#define waffleSize 32 // size of how long and high the sprite is
#define jumpForce -8 // raylib coordinate system flipped, 0,0 is top left instead of bottom left so every value is flipped from what you think. which fine but its weird
#define gravity 0.4
#define MAX_JUMP_TIME 30
int main(){
    // defintion of physics variables
    float x_velocity = 5;
    float y_velocity = 0; // because of the origin being 0,0 being the top left
    const int screenWidth = 800;
    const int screenHeight = 450;
    float waffle_index = 0; // which animation waffle is on
    float scale = 4.0f; // scales the sprite to 4 times its size
    bool canJump = 1;
    bool isMoving = 0;
    bool isJumping = 0;
    bool isRight = 1;
    bool isLeft = 0;
    float jumpStartTime;
    float jumpTime;



    // characteristics of window and origin of waffles position
    InitWindow(screenWidth, screenHeight, "Waffles big day out");
    Vector2 wafflePos = {1, screenHeight - waffleSize}; // because of the origin being 0,0 being the top left


    // camera functions not working
    Camera2D camera = InitiateCamera((Vector2){wafflePos.x + waffleSize * scale / 2, wafflePos.y + waffleSize * scale / 2}, (float)screenWidth, (float)screenHeight);

    // Textures and annimations
    Texture2D Waffle = LoadTexture("Waffle_Sprite_Sheet.png");
    
    SpriteAnimation _animation;
    SpriteAnimation idleAnimation;
    SpriteAnimation walkingForwardAnimation;
    SpriteAnimation walkingBackwardAnimation;
    SpriteAnimation jumpingAnimationRight;
    SpriteAnimation jumpingAnimationLeft;
    





    Rectangle idolFrames[] = {
    (Rectangle){waffle_index * waffleSize, 0, waffleSize, waffleSize},
    (Rectangle){waffle_index + 1 * waffleSize, 0, waffleSize, waffleSize},
    (Rectangle){waffle_index + 2 * waffleSize, 0, waffleSize, waffleSize},
    (Rectangle){waffle_index + 3 * waffleSize, 0, waffleSize, waffleSize},
    (Rectangle){waffle_index * waffleSize, 32, waffleSize, waffleSize},  // collum 2 
    (Rectangle){waffle_index + 1 * waffleSize, 32, waffleSize, waffleSize}, 
    (Rectangle){waffle_index + 2 * waffleSize, 32, waffleSize, waffleSize},
    (Rectangle){waffle_index + 3 * waffleSize, 32, waffleSize, waffleSize}


    };
    idleAnimation = CreateSpriteAnimation(Waffle, 2, idolFrames, 8);

    Rectangle walkingForwardFrames[] = { 
    (Rectangle){waffle_index * waffleSize, 128, waffleSize, waffleSize}, // x, y , width, height
    (Rectangle){waffle_index + 1* waffleSize, 128, waffleSize, waffleSize}, 
    (Rectangle){waffle_index + 2* waffleSize, 128, waffleSize, waffleSize}, 
    (Rectangle){waffle_index + 3* waffleSize, 128, waffleSize, waffleSize}, 
    (Rectangle){waffle_index + 4* waffleSize, 128, waffleSize, waffleSize}, 
    (Rectangle){waffle_index + 5* waffleSize, 128, waffleSize, waffleSize},
    (Rectangle){waffle_index + 6* waffleSize, 128, waffleSize, waffleSize}, 
    (Rectangle){waffle_index + 7* waffleSize, 128, waffleSize, waffleSize}, 

    };
    walkingForwardAnimation = CreateSpriteAnimation(Waffle, 4, walkingForwardFrames, 8);

    Rectangle walkingBackwardFrames[] = { 
    (Rectangle){waffle_index * waffleSize, 160, waffleSize, waffleSize}, // x, y, width, height fix
    (Rectangle){waffle_index + 1* waffleSize, 160, waffleSize, waffleSize}, 
    (Rectangle){waffle_index + 2* waffleSize, 160, waffleSize, waffleSize}, 
    (Rectangle){waffle_index + 3* waffleSize, 160, waffleSize, waffleSize}, 
    (Rectangle){waffle_index + 4* waffleSize, 160, waffleSize, waffleSize}, 
    (Rectangle){waffle_index + 5* waffleSize, 160, waffleSize, waffleSize},
    (Rectangle){waffle_index + 6* waffleSize, 160, waffleSize, waffleSize}, 
    (Rectangle){waffle_index + 7* waffleSize, 160, waffleSize, waffleSize}, 

    };
    walkingBackwardAnimation = CreateSpriteAnimation(Waffle, 2, walkingBackwardFrames, 8);


    Rectangle jumpingRightFrames[] = {
    (Rectangle){waffle_index * waffleSize, 256, waffleSize, waffleSize},
    (Rectangle){waffle_index + 1 * waffleSize, 256, waffleSize, waffleSize},
    (Rectangle){waffle_index + 2 * waffleSize, 256, waffleSize, waffleSize},
    (Rectangle){waffle_index + 3 * waffleSize, 256, waffleSize, waffleSize},
    (Rectangle){waffle_index + 4 * waffleSize, 256, waffleSize, waffleSize},
    (Rectangle){waffle_index + 5 * waffleSize, 256, waffleSize, waffleSize},
    (Rectangle){waffle_index + 6 * waffleSize, 256, waffleSize, waffleSize}

    };
    jumpingAnimationRight = CreateSpriteAnimation(Waffle, 5, jumpingRightFrames, 7);

    Rectangle jumpingLeftFrames[] = {
    (Rectangle){waffle_index * waffleSize, 320, waffleSize, waffleSize},
    (Rectangle){waffle_index + 1 * waffleSize, 320, waffleSize, waffleSize},
    (Rectangle){waffle_index + 2 * waffleSize, 320, waffleSize, waffleSize},
    (Rectangle){waffle_index + 3 * waffleSize, 320, waffleSize, waffleSize},
    (Rectangle){waffle_index + 4 * waffleSize, 320, waffleSize, waffleSize},
    (Rectangle){waffle_index + 5 * waffleSize, 320, waffleSize, waffleSize}, 
    (Rectangle){waffle_index + 6 * waffleSize, 320, waffleSize, waffleSize}


    };
    jumpingAnimationLeft= CreateSpriteAnimation(Waffle, 5, jumpingLeftFrames, 7);

    Sound meow = LoadSound("");
    SetTargetFPS(60);
    _animation = idleAnimation; // this sets it to the idle if nothing else is pressed
    while (!WindowShouldClose()){
    
    camera.target = (Vector2){wafflePos.x+waffleSize,screenHeight};// camera follows the Waffle

    if (IsKeyDown(KEY_RIGHT)) { // Dont need x bounds because its going to be a side scroller
        wafflePos.x += x_velocity;
        isMoving = 1;
        isRight = 1;
        if (!isJumping){ // to account for when your in the air and pusing the right key
        _animation = walkingForwardAnimation;
        }
    }
    else if (IsKeyDown(KEY_LEFT) && wafflePos.x > 0) { 
        wafflePos.x -= x_velocity;
        isMoving = 1;
        isRight = 0;
        if(!isJumping){
        _animation = walkingBackwardAnimation;
        }
    }
    else{
        isMoving = 0;
    }
    if (IsKeyDown(KEY_UP) && wafflePos.y + waffleSize*scale >= screenHeight && canJump) { 

        y_velocity = jumpForce; 
        canJump = 0; // no double jumps
        isMoving = 1;
        isJumping = 1;
        jumpTime = jumpStartTime;
        if (jumpTime > 0){
            y_velocity = jumpForce; 
        }
        if (isRight) {
        _animation = jumpingAnimationRight;
        }
        else if (!isRight){
        _animation = jumpingAnimationLeft;
        }
    }
 

    if (!isMoving && !isJumping){
        _animation = idleAnimation; // this sets it to the idle if nothing else is pressed
    }
    if (wafflePos.y >= screenHeight - waffleSize) {
        canJump = 1; // Reset the ability to jump when on the ground
        isJumping = 0;
    }

    y_velocity += gravity; // apply gravity
    wafflePos.y += y_velocity; // update postion
    if (wafflePos.y > screenHeight - waffleSize) {
        // Ensure the character stays on the ground
        wafflePos.y = screenHeight - waffleSize;
        y_velocity = 0;
    }

        BeginDrawing();
        BeginMode2D(camera); // Set camera mode to follow the target

        ClearBackground(DARKGRAY);
        DrawText("move waffle with arrow keys", 10, 10, 20, WHITE);

        Rectangle dest = (Rectangle){wafflePos.x, wafflePos.y, waffleSize * scale, waffleSize * scale}; 
        Vector2 origin = {0, waffleSize*(scale-1)};
        if (_animation.rectangles != NULL) {
        DrawSpriteAnimationPro(_animation, dest, origin, 0, WHITE); // has this in it //DrawTexturePro(Waffle, source, dest, (Vector2){0, 0}, 0, WHITE); // Change the origin of the waffle and this //Rectangle source = (Rectangle){waffle_index * waffleSize, 0, waffleSize, waffleSize};
        //DisposeSpriteAnimation(_animation); // deallocate memory
        }
        EndMode2D();
        EndDrawing();
    }
   CloseWindow();
   return 0;
}

