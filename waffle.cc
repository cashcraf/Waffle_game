/**
*  @file: waffle.cc
*  @author: cashcraf
*  @date: 2023-10-18 
*  @brief: this is the def file for waffle.h
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
    hitbox = {wafflePos.x, wafflePos.y, waffleSize-10, waffleSize+10};
}

void Waffle::Update(bool hasCollided, bool collisionSideRight, bool collisionSideLeft){
    if (!lost){
    collisionSideRightWaffle = collisionSideRight;
    collisionSideLeftWaffle = collisionSideLeft;
    UpdateKeysAndAnimations(hasCollided, collisionSideRightWaffle, collisionSideLeftWaffle);
    UpdatePhysics(hasCollided);
    }
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

void Waffle::UpdateKeysAndAnimations(bool hasCollided, bool collisionSideRight, bool collisionSideLeft){ // jumping movement looks bad
    framesToMeow ++;
    if (framesToMeow == 400){ // meow every 4 seconds
        PlaySound(meow);
        framesToMeow = 0;
    }
    // x direction
    if (!lost && !win){
    if (IsKeyDown(KEY_RIGHT) && !isHissing && !collisionSideRight) { // Dont need x bounds because its going to be a side scroller
        wafflePos.x += x_velocity;
        isMoving = 1;
        isRight = 1;
        isLeft = 0;
        if (!isJumping && !isHitting){ // to account for when your in the air and pusing the right key
        waffle_animation = walkingForwardAnimation;
        
    }
    }

    // y direction
    else if (IsKeyDown(KEY_LEFT) && wafflePos.x > 0 && !isHissing && !collisionSideLeft) { 
        wafflePos.x -= x_velocity;
        isMoving = 1;
        isRight = 0;
        isLeft = 1;
        if(!isJumping && !isHitting){
        waffle_animation = walkingBackwardAnimation;
        }
    }
    else{
        isMoving = 0;
    }

    // y direction
    if (IsKeyDown(KEY_UP) && canJump && !isHissing) {
        PlaySound(jump);
        isJumping = true;
        canJump = 0; // no double jumps
        isMoving = 1;
        jumpTimer += GetFrameTime();
        if (isRight && !isHitting) {
            if (jumpTimer < 0.1f) {
                waffle_animation = jumpingPhase1AnimationRight;
            } else if (jumpTimer < 0.2f) {
                waffle_animation = jumpingPhase2AnimationRight; // stuck here
            } else if (jumpTimer < 0.3f) {
                waffle_animation = jumpingPhase3AnimationRight;
            } else {
                waffle_animation = jumpingPhase4AnimationRight;
            }
        }
        else if (!isRight && !isHitting){
            if (jumpTimer < 0.1f) {
                waffle_animation = jumpingPhase1AnimationLeft;
            } else if (jumpTimer < 0.2f) {
                waffle_animation = jumpingPhase2AnimationLeft;
            } else if (jumpTimer < 0.3f) {
                waffle_animation = jumpingPhase3AnimationLeft;
            } else {
                waffle_animation = jumpingPhase4AnimationLeft;
            }
        }

        // Adjust jumpForce based on jump duration
        if (jumpTimer < maxJumpDuration) {
            jumpForce = -10 * (-1.0f + (jumpTimer / maxJumpDuration));
        }
    }

        // Apply jump force
        if (isJumping) {
            wafflePos.y -= jumpForce;
        }

    // Check for release of the jump button
    if (IsKeyReleased(KEY_UP) || jumpTimer >= maxJumpDuration) {
        StopSound(jump);
        if (isRight){
        waffle_animation = jumpingPhase3AnimationRight;
        }
        else{
        waffle_animation = jumpingPhase3AnimationLeft;
        }
        jumpTimer = 0.0f;  // Reset the jump timer
        jumpForce = 0.0f;  // Reset the jump force
    }


    // special keys
    static bool spaceKeyDown = false; // Static variable to track the state of the space key
     if (IsKeyPressed(KEY_SPACE)) {
        isHissing = true;
        waffle_animation = hissingAnimation;
        PlaySound(hiss);
        spaceKeyDown = true; // Set the flag to true
    }

    // Check if the space key is released
    if (IsKeyReleased(KEY_SPACE)) {
        spaceKeyDown = false; // Reset the flag
    }

    if (!spaceKeyDown) {
        StopSound(hiss);
        isHissing = false;
    }
    
    if (!isHissing && isRight){ // its because when you hold down it 
    static bool sKeyDown = false; // Static variable to track the state of the s key
     if (IsKeyPressed(KEY_DOWN)) {
        isHitting = true;
        waffle_animation = clawRightAnimation;
        PlaySound(claw);
        sKeyDown = true; // Set the flag to true
    }

    // Check if the space key is released
    if (IsKeyReleased(KEY_DOWN)) {
        sKeyDown = false; // Reset the flag
    }

    if (!sKeyDown) {
        StopSound(claw);
        isHitting = false;
    }
    }

    else if (!isHissing && isLeft){
    static bool sKeyDownn = false; // Static variable to track the state of the s key
     if (IsKeyPressed(KEY_DOWN)) {
        isHitting = true;
        waffle_animation = clawLeftAnimation;
        PlaySound(claw);
        sKeyDownn = true; // Set the flag to true
    }

    // Check if the space key is released
    if (IsKeyReleased(KEY_DOWN)) {
        sKeyDownn = false; // Reset the flag
    }

    if (!sKeyDownn) {
        StopSound(claw);
        isHitting = false;
    }
    }
    
    if (isHitting){
        if(isRight){
            hittingHitbox = {
            wafflePos.x+32, 
            wafflePos.y, 
            waffleSize, 
            waffleSize
        };
        }
    }
    else{
            hittingHitbox = {
            wafflePos.x-32, 
            wafflePos.y, 
            waffleSize, 
            waffleSize
        };
    }
    if (!isMoving && !isJumping && !isHissing && !isHitting){
        waffle_animation = idleAnimation; // this sets it to the idle if nothing else is pressed
    }
    if (wafflePos.y >= screenHeight - waffleSize) {
        canJump = 1; // Reset the ability to jump when on the ground
        isJumping = 0;
    }
    hitbox = {wafflePos.x, wafflePos.y, waffleSize, waffleSize}; // update hitbox
    }

}
void Waffle::UpdatePhysics(bool hasCollided){
    if (hasCollided) {
        y_velocity = 0;
        isJumping = false;
        canJump = true;
    }
    else {
    y_velocity += gravity; // apply gravity
    wafflePos.y += y_velocity; // update postion
    if (wafflePos.y > screenHeight - waffleSize) {
        // Ensure the character stays on the ground
        wafflePos.y = screenHeight - waffleSize;
        y_velocity = 0;
    hitbox = {wafflePos.x, wafflePos.y, waffleSize, waffleSize}; // update hitbox
    }
    }
}
bool Waffle::lose(){
    // lose makes waffle nap and not able to move
    lost = true;
    UpdatePhysics(false);
    waffle_animation = nappingAnimation;
    return lost;
}

void Waffle::cleanUp() {
    // Release any allocated resources here
    UnloadSound(hiss);
    UnloadSound(meow);
    UnloadSound(claw);
    UnloadSound(jump);



    // Release textures if you have any
    UnloadTexture(waffle); // Replace `yourTexture` with the actual texture you want to release
}


void Waffle::waffleWins(){ // if waffle wins play the animation and win
    waffle_animation = winningAnimation; // need to do this
    win = true;
    UpdatePhysics(false);
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
    walkingForwardAnimation = CreateSpriteAnimation(waffle, 8, walkingForwardFrames, 8);


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
    walkingBackwardAnimation = CreateSpriteAnimation(waffle, 8, walkingBackwardFrames, 8);

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
    hissingAnimation = CreateSpriteAnimation(waffle, 8, hissingFrames, 8);

    Rectangle nappingFrames[] = {
    (Rectangle){waffle_index * waffleSize, 192, waffleSize, waffleSize},
    (Rectangle){waffle_index + 1 * waffleSize, 192, waffleSize, waffleSize},
    (Rectangle){waffle_index + 2 * waffleSize, 192, waffleSize, waffleSize},
    (Rectangle){waffle_index + 3 * waffleSize, 192, waffleSize, waffleSize},
    };

    nappingAnimation = CreateSpriteAnimation(waffle, 4, nappingFrames, 4);

    Rectangle clawRightFrames[] = {
    (Rectangle){waffle_index * waffleSize, 224, waffleSize, waffleSize},
    (Rectangle){waffle_index + 1 * waffleSize, 224, waffleSize, waffleSize},
    (Rectangle){waffle_index + 2 * waffleSize, 224, waffleSize, waffleSize},
    (Rectangle){waffle_index + 3 * waffleSize, 224, waffleSize, waffleSize},
    (Rectangle){waffle_index + 4 * waffleSize, 224, waffleSize, waffleSize},
    (Rectangle){waffle_index + 5 * waffleSize, 224, waffleSize, waffleSize}

    };

    clawRightAnimation = CreateSpriteAnimation(waffle, 6, clawRightFrames, 6);

    Rectangle clawLeftFrames[] = {
    (Rectangle){waffle_index * waffleSize, 96, waffleSize, waffleSize},
    (Rectangle){waffle_index + 1 * waffleSize, 96, waffleSize, waffleSize},
    (Rectangle){waffle_index + 2 * waffleSize, 96, waffleSize, waffleSize},
    (Rectangle){waffle_index + 3 * waffleSize, 96, waffleSize, waffleSize},
    (Rectangle){waffle_index + 4 * waffleSize, 96, waffleSize, waffleSize},
    (Rectangle){waffle_index + 5 * waffleSize, 96, waffleSize, waffleSize}

    };

    clawLeftAnimation = CreateSpriteAnimation(waffle, 6, clawLeftFrames, 6);

    Rectangle winningFrames[] = {
        (Rectangle){waffle_index * waffleSize, 64, waffleSize, waffleSize},
        (Rectangle){waffle_index + 1 * waffleSize, 64, waffleSize, waffleSize},
        (Rectangle){waffle_index + 2* waffleSize, 64, waffleSize, waffleSize},
        (Rectangle){waffle_index + 3* waffleSize, 64, waffleSize, waffleSize}

    };

    winningAnimation = CreateSpriteAnimation(waffle, 4, winningFrames, 4);

    // Create the first phase of the jump animation for right-facing waffle
    Rectangle jumpingPhase1FramesRight[] = {
        (Rectangle){waffle_index * waffleSize, 256, waffleSize, waffleSize},
        (Rectangle){waffle_index + 1 * waffleSize, 256, waffleSize, waffleSize}
    };
    jumpingPhase1AnimationRight = CreateSpriteAnimation(waffle, 2, jumpingPhase1FramesRight, 2);

    // Create the second phase of the jump animation for right-facing waffle
    Rectangle jumpingPhase2FramesRight[] = {
        (Rectangle){waffle_index + 2 * waffleSize, 256, waffleSize, waffleSize},
    };
    jumpingPhase2AnimationRight = CreateSpriteAnimation(waffle, 1, jumpingPhase2FramesRight, 1);

    // Create the third phase of the jump animation for right-facing waffle
    Rectangle jumpingPhase3FramesRight[] = {
        (Rectangle){waffle_index + 3 * waffleSize, 256, waffleSize, waffleSize},
        (Rectangle){waffle_index + 4 * waffleSize, 256, waffleSize, waffleSize}
    };
    jumpingPhase3AnimationRight = CreateSpriteAnimation(waffle, 2, jumpingPhase3FramesRight, 2);

    // Create the fourth phase of the jump animation for right-facing waffle
    Rectangle jumpingPhase4FramesRight[] = {
        (Rectangle){waffle_index + 5 * waffleSize, 256, waffleSize, waffleSize},
        (Rectangle){waffle_index + 6 * waffleSize, 256, waffleSize, waffleSize}
    };
    jumpingPhase4AnimationRight = CreateSpriteAnimation(waffle, 2, jumpingPhase4FramesRight, 2);




    // left

    // Create the first phase of the jump animation for right-facing waffle
    Rectangle jumpingPhase1FramesLeft[] = {
        (Rectangle){waffle_index + 6 * waffleSize, 320, waffleSize, waffleSize},
        (Rectangle){waffle_index + 5 * waffleSize, 320, waffleSize, waffleSize}
    };
    jumpingPhase1AnimationLeft= CreateSpriteAnimation(waffle, 2, jumpingPhase1FramesLeft, 2);

    // Create the second phase of the jump animation for right-facing waffle
    Rectangle jumpingPhase2FramesLeft[] = {
        (Rectangle){waffle_index + 4 * waffleSize, 320, waffleSize, waffleSize}
    };
    jumpingPhase2AnimationLeft = CreateSpriteAnimation(waffle, 1, jumpingPhase2FramesLeft, 1);

    // Create the third phase of the jump animation for right-facing waffle
    Rectangle jumpingPhase3FramesLeft[] = {
        (Rectangle){waffle_index + 3 * waffleSize, 320, waffleSize, waffleSize},
        (Rectangle){waffle_index + 2 * waffleSize, 320, waffleSize, waffleSize}
    };
    jumpingPhase3AnimationLeft = CreateSpriteAnimation(waffle, 2, jumpingPhase3FramesLeft, 2);

    // Create the fourth phase of the jump animation for right-facing waffle
    Rectangle jumpingPhase4FramesLeft[] = {
        (Rectangle){waffle_index + 1 * waffleSize, 320, waffleSize, waffleSize},
        (Rectangle){waffle_index * waffleSize, 320, waffleSize, waffleSize}
    };
    jumpingPhase4AnimationLeft = CreateSpriteAnimation(waffle, 2, jumpingPhase4FramesLeft, 2);


}
void Waffle::initializeSounds(){
    hiss = LoadSound("Sounds/hissing.wav");
    meow = LoadSound("Sounds/meow.wav");
    claw = LoadSound("Sounds/claw.wav");
    jump = LoadSound("Sounds/jump.wav");

}