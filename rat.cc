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

    Rat::Rat(Vector2 position, float width, float height){
    position.x = position.x;
    position.y = position.y;

    width = width;
    height = height;
    }
    void Rat::Update(){

        Rectangle ratWalkFrames[] = {
        (Rectangle){0, 0, ratSize, ratSize},
        (Rectangle){ 1 * ratSize, 0, ratSize, ratSize},
        (Rectangle){2 * ratSize, 0, ratSize, ratSize},
        (Rectangle){3 * ratSize, 0, ratSize, ratSize},
        (Rectangle){0, 32, ratSize, ratSize},  // collum 2 
        (Rectangle){1 * ratSize, 32, ratSize, ratSize}, 
        (Rectangle){2 * ratSize, 32, ratSize, ratSize},
        (Rectangle){3 * ratSize, 32, ratSize, ratSize}


        };
        ratWalk = CreateSpriteAnimation(rat, 2, ratWalkFrames, 8);
    }

    bool Rat::Dead(){ // Idk what I want this to return
        bool isDead = 1;
        return isDead;
    }