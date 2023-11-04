    /**
    *  @file: rat.cc
    *  @author: cashcraf
    *  @date: 2023-10-18 
    *  @brief: 
    */
     
    #include "raylib.h"
    #include <stdlib.h>
    #include "Headers/animation.h"
    #include "Headers/camera.h"
    #include "Headers/rat.h"
    using namespace std;
    // function defs here

    Rat::Rat(Vector2 startingPosition){
        ratPos = startingPosition; // initialize rat pos at its staring position
        hitbox = {ratPos.x, ratPos.y, ratSize*(scale-1), ratSize*(scale-1)};
        isDead = 0;

    }
    void Rat::Update(){
        UpdatePhysics();
    }

    void Rat::UpdatePhysics(){
        // to do
        if (!isDead){
        float moveSpeed = 1.0;
        ratPos.x -= moveSpeed;
        hitbox = {ratPos.x, ratPos.y, ratSize-10, ratSize+10};
        }
        else {
            // do nothing
        }
    }

void Rat::doAnimations() {
    Rectangle ratDest = {ratPos.x, ratPos.y, ratSize * scale, ratSize * scale};
    Vector2 ratOrigin = {0, ratSize * (scale - 1)};

    if (isDead && !ratDied) {
        // Play the dying animation
        DrawSpriteAnimationPro(ratDie, ratDest, ratOrigin, 0, WHITE);
        currentFrame ++;

        if (currentFrame >= 10) {
            // Once the dying animation finishes, switch to the dead state
            currentFrame = 0;
            rat_animation = ratDead;
            ratDied = 1;

        }
    } else {
        // Draw the living animation
        if (rat_animation.rectangles != NULL) {
            DrawSpriteAnimationPro(rat_animation, ratDest, ratOrigin, 0, WHITE);
        }
    }
}

    bool Rat::Dead(){ // Idk what I want this to return yet
        isDead = 1;
        //rat_animation = ratDie;
        return isDead;
    }

    void Rat::cleanUp(){
        UnloadTexture(rat);
    }

    void Rat::initializeAnimations(){
        Rectangle ratWalkFrames[] = {
        (Rectangle){0, 0, ratSize, ratSize},
        (Rectangle){ 1 * ratSize, 0, ratSize, ratSize},
        (Rectangle){2 * ratSize, 0, ratSize, ratSize},
        (Rectangle){3 * ratSize, 0, ratSize, ratSize},
        (Rectangle){4 * ratSize, 0, ratSize, ratSize},  
        (Rectangle){5 * ratSize, 0, ratSize, ratSize}, 
        (Rectangle){6 * ratSize, 0, ratSize, ratSize},
        (Rectangle){7 * ratSize, 0, ratSize, ratSize},
        (Rectangle){8 * ratSize, 0, ratSize, ratSize},
        (Rectangle){9 * ratSize, 0, ratSize, ratSize}

        };
        ratWalk = CreateSpriteAnimation(rat, 10, ratWalkFrames, 10);
        rat_animation = ratWalk; // starts out alive and walking

        // dying animations
        Rectangle ratDyingFrames[] = {
        (Rectangle){0, 32, ratSize, ratSize},
        (Rectangle){ 1 * ratSize, 32, ratSize, ratSize},
        (Rectangle){2 * ratSize, 32, ratSize, ratSize},
        (Rectangle){3 * ratSize, 32, ratSize, ratSize},
        (Rectangle){4 * ratSize, 32, ratSize, ratSize},   
        (Rectangle){5 * ratSize, 32, ratSize, ratSize}, 
        (Rectangle){6 * ratSize, 32, ratSize, ratSize},
        (Rectangle){7 * ratSize, 32, ratSize, ratSize}


        };
        ratDie = CreateSpriteAnimation(rat, 10, ratDyingFrames, 10);

        Rectangle ratDeadFrame[] = { 7* ratSize, 32, ratSize, ratSize};
        ratDead = CreateSpriteAnimation(rat, 1, ratDeadFrame, 1);

    }