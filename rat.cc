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

    }
    void Rat::Update(){
        UpdatePhysics();
        UpdateKeysAndAnimations();
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

        // die animations
        Rectangle ratDieFrames[] = {
        (Rectangle){0, 32, ratSize, ratSize},
        (Rectangle){ 1 * ratSize, 32, ratSize, ratSize},
        (Rectangle){2 * ratSize, 32, ratSize, ratSize},
        (Rectangle){3 * ratSize, 32, ratSize, ratSize},
        (Rectangle){4 * ratSize, 32, ratSize, ratSize},   
        (Rectangle){5 * ratSize, 32, ratSize, ratSize}, 
        (Rectangle){6 * ratSize, 32, ratSize, ratSize},
        (Rectangle){7 * ratSize, 32, ratSize, ratSize}


        };
        ratDie = CreateSpriteAnimation(rat, 10, ratDieFrames, 10);


    }

    void Rat::UpdatePhysics(){
        // to do
        float moveSpeed = 1.0;
        ratPos.x -= moveSpeed;
    }

    void Rat::UpdateKeysAndAnimations(){
        // to do
    }

    void Rat::doAnimations(){ // not working its not the camera or the background not include path its not waffle not update
        // animations 
        Rectangle ratDest = (Rectangle){ratPos.x, ratPos.y, ratSize *scale, ratSize*scale}; 
        Vector2 ratOrigin = {0,ratSize*(scale-1)};
        if (rat_animation.rectangles != NULL) {
        DrawSpriteAnimationPro(rat_animation, ratDest, ratOrigin, 0, WHITE); // has this in it //DrawTexturePro(Waffle, source, dest, (Vector2){0, 0}, 0, WHITE); // Change the origin of the waffle and this //Rectangle source = (Rectangle){waffle_index * waffleSize, 0, waffleSize, waffleSize};
        }
}
    bool Rat::Dead(){ // Idk what I want this to return yet
        bool isDead = 1;
        rat_animation = ratDie;
        return isDead;
    }