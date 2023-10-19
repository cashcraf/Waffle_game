/**
*  @file: Waffle.cc
*  @author: cashcraf
*  @date: 2023-10-18 
*  @brief: 
*/
 
#include "raylib.h"
#include <stdlib.h>
#include "Headers/animation.h"
#include "Headers/camera.h"
#include "Headers/waffle.h"
using namespace std;
// function defs here
Waffle::Waffle(Vector2 wafflePosition){
    wafflePos = wafflePosition;
    camera = InitiateCamera((Vector2){wafflePos.x + waffleSize * scale / 2, wafflePos.y + waffleSize * scale / 2}, (float)screenWidth, (float)screenHeight);
}

void Waffle::Update(){
    UpdateKeysAndAnimations();
    UpdatePhysics();
}

void Waffle::doAnimations(){
        // animations
        Rectangle dest = (Rectangle){wafflePos.x, wafflePos.y, waffleSize * scale, waffleSize * scale}; 
        Vector2 origin = {0, waffleSize*(scale-1)};
        if (waffle_animation.rectangles != NULL) {
        DrawSpriteAnimationPro(waffle_animation, dest, origin, 0, WHITE); // has this in it //DrawTexturePro(Waffle, source, dest, (Vector2){0, 0}, 0, WHITE); // Change the origin of the waffle and this //Rectangle source = (Rectangle){waffle_index * waffleSize, 0, waffleSize, waffleSize};
        //DisposeSpriteAnimation(waffle_animation); // deallocate memory
        }
}

void Waffle::UpdateKeysAndAnimations(){
    // x direction
    if (IsKeyDown(KEY_RIGHT)) { // Dont need x bounds because its going to be a side scroller
        wafflePos.x += x_velocity;
        isMoving = 1;
        isRight = 1;
        if (!isJumping){ // to account for when your in the air and pusing the right key
        waffle_animation = walkingForwardAnimation;
        }
    }
    else if (IsKeyDown(KEY_LEFT) && wafflePos.x > 0) { 
        wafflePos.x -= x_velocity;
        isMoving = 1;
        isRight = 0;
        if(!isJumping){
        waffle_animation = walkingBackwardAnimation;
        }
    }
    else{
        isMoving = 0;
    }

    // y direction
    if (IsKeyDown(KEY_UP) && wafflePos.y + waffleSize*scale >= screenHeight && canJump) { 

        y_velocity = jumpForce; 
        canJump = 0; // no double jumps
        isMoving = 1;
        isJumping = 1;
        if (isRight) {
        waffle_animation = jumpingAnimationRight;
        }
        else if (!isRight){
        waffle_animation = jumpingAnimationLeft;
        }
    }

    // special keys
    if (IsKeyDown(KEY_SPACE)){ // push space to hiss (fix it when you hold in space rn it loops the audio)
        isHissing = 1;
        waffle_animation = hissingAnimation;
        PlaySound(hiss);
    }
    else if (IsKeyUp(KEY_SPACE)){
        isHissing = 0;
    }
    

    if (!isMoving && !isJumping && !isHissing){
        waffle_animation = idleAnimation; // this sets it to the idle if nothing else is pressed
    }
    if (wafflePos.y >= screenHeight - waffleSize) {
        canJump = 1; // Reset the ability to jump when on the ground
        isJumping = 0;
    }

}
void Waffle::UpdatePhysics(){
    y_velocity += gravity; // apply gravity
    wafflePos.y += y_velocity; // update postion
    if (wafflePos.y > screenHeight - waffleSize) {
        // Ensure the character stays on the ground
        wafflePos.y = screenHeight - waffleSize;
        y_velocity = 0;
    }
}
Vector2 Waffle::setCameraTarget(){
    Vector2 target;
    target = (Vector2){wafflePos.x+waffleSize,(float)screenHeight};// camera follows the Waffle
    return target;
}

void Waffle::initializeAnimations(){
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
    idleAnimation = CreateSpriteAnimation(waffle, 2, idolFrames, 8);


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
    walkingForwardAnimation = CreateSpriteAnimation(waffle, 4, walkingForwardFrames, 8);


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
    walkingBackwardAnimation = CreateSpriteAnimation(waffle, 2, walkingBackwardFrames, 8);


    Rectangle jumpingRightFrames[] = {
    (Rectangle){waffle_index * waffleSize, 256, waffleSize, waffleSize},
    (Rectangle){waffle_index + 1 * waffleSize, 256, waffleSize, waffleSize},
    (Rectangle){waffle_index + 2 * waffleSize, 256, waffleSize, waffleSize},
    (Rectangle){waffle_index + 3 * waffleSize, 256, waffleSize, waffleSize},
    (Rectangle){waffle_index + 4 * waffleSize, 256, waffleSize, waffleSize},
    (Rectangle){waffle_index + 5 * waffleSize, 256, waffleSize, waffleSize},
    (Rectangle){waffle_index + 6 * waffleSize, 256, waffleSize, waffleSize}

    };
    jumpingAnimationRight = CreateSpriteAnimation(waffle, 5, jumpingRightFrames, 7);


    Rectangle jumpingLeftFrames[] = {
    (Rectangle){waffle_index * waffleSize, 320, waffleSize, waffleSize},
    (Rectangle){waffle_index + 1 * waffleSize, 320, waffleSize, waffleSize},
    (Rectangle){waffle_index + 2 * waffleSize, 320, waffleSize, waffleSize},
    (Rectangle){waffle_index + 3 * waffleSize, 320, waffleSize, waffleSize},
    (Rectangle){waffle_index + 4 * waffleSize, 320, waffleSize, waffleSize},
    (Rectangle){waffle_index + 5 * waffleSize, 320, waffleSize, waffleSize}, 
    (Rectangle){waffle_index + 6 * waffleSize, 320, waffleSize, waffleSize}


    };

    jumpingAnimationLeft= CreateSpriteAnimation(waffle, 5, jumpingLeftFrames, 7);


    Rectangle hissingFrames[] = {
    (Rectangle){waffle_index * waffleSize, 288, waffleSize, waffleSize},
    (Rectangle){waffle_index + 1 * waffleSize, 288, waffleSize, waffleSize},
    (Rectangle){waffle_index + 2 * waffleSize, 288, waffleSize, waffleSize},
    (Rectangle){waffle_index + 3 * waffleSize, 288, waffleSize, waffleSize},
    (Rectangle){waffle_index + 4 * waffleSize, 288, waffleSize, waffleSize},
    (Rectangle){waffle_index + 5 * waffleSize, 288, waffleSize, waffleSize}, 
    (Rectangle){waffle_index + 6 * waffleSize, 288, waffleSize, waffleSize},
    (Rectangle){waffle_index + 7 * waffleSize, 288, waffleSize, waffleSize}


    };
    hissingAnimation = CreateSpriteAnimation(waffle, 5, hissingFrames, 8);
}