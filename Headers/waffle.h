/**
*  @file: waffle.h
*  @author: cashcraf
*  @date: 2023-10-19
*  @brief: 
*/
 
#ifndef WAFFLE
#define WAFFLE
#include "raylib.h"
#include <stdlib.h>
#include "animation.h"
#include "camera.h"
 
class Waffle
{
public:
//your code here (constructors getters setters and function headers)
    Waffle(Vector2 wafflePosition); // constructor

    // initilizers (setters)
    void initializeAnimations();
    Vector2 setCameraTarget();
    void initializeSounds();

    //getters
    Camera2D getWafflesCamera() {return camera;}
    Vector2 getWafflePos(){return wafflePos;}
    Rectangle getHitbox(){return hitbox;}
    Rectangle getHittingHitbox(){return hittingHitbox;}
    bool getIsMoving(){return isMoving;}
    bool getIsJumping(){return isJumping;}
    bool getIsHitting(){return isHitting;}

    // updaters
    void Update();
    void UpdateKeysAndAnimations();
    void UpdatePhysics();
    void doAnimations();
    bool lose(); // loses the game and returns true
    void waffleWins();
    void cleanUp();

private:
    // animation values
    SpriteAnimation waffle_animation; // waffles updated animation
    SpriteAnimation idleAnimation;
    SpriteAnimation walkingForwardAnimation;
    SpriteAnimation walkingBackwardAnimation;
    SpriteAnimation hissingAnimation; // maybe make this left and right really dont know if I wanna do that
    SpriteAnimation nappingAnimation;
    SpriteAnimation clawRightAnimation;
    SpriteAnimation clawLeftAnimation;
    SpriteAnimation winningAnimation;

    SpriteAnimation jumpingPhase1AnimationRight;
    SpriteAnimation jumpingPhase2AnimationRight;
    SpriteAnimation jumpingPhase3AnimationRight;
    SpriteAnimation jumpingPhase4AnimationRight;

    SpriteAnimation jumpingPhase1AnimationLeft;
    SpriteAnimation jumpingPhase2AnimationLeft;
    SpriteAnimation jumpingPhase3AnimationLeft;
    SpriteAnimation jumpingPhase4AnimationLeft;   
    Texture2D waffle = LoadTexture("Images/Waffle_Sprite_Sheet.png");

    // screen values
    const int screenWidth = 800;
    const int screenHeight = 450;

    // camera values
    Camera2D camera; 

    // waffle postion values
    Rectangle hitbox;
    Rectangle hittingHitbox;
    Vector2 wafflePos;
    const float waffleSize = 32; // size of how long and high the sprite is
    float waffle_index = 0; // which animation waffle is on
    float scale = 4.0f; // scales the sprite to 4 times its size
    bool canJump = 1;
    bool isMoving = 0;
    bool isJumping = 0;
    bool isRight = 1;
    bool isHissing = 0;
    bool isLeft = 0;
    bool isHitting = 0;
    bool win = 0;

    // Physics
    int jumpForce = 0; // raylib coordinate system flipped, 0,0 is top left instead of bottom left so every value is flipped from what you think. which fine but its weird
    const float gravity = 0.2;
    float x_velocity = 5;
    float y_velocity = 0; // because of the origin being 0,0 being the top left
    bool lost = 0;

    // Jump timer
    float jumpTimer = 0.0f;       // Timer to control jump height
    float maxJumpDuration = 0.5f; // Maximum duration for a higher jump (adjust as needed)


    // Sound
    Sound meow;
    Sound hiss;
    Sound claw;


};
#endif