/**
*  @file: rat.h
*  @author: cashcraf
*  @date: 2023-10-18 
*  @brief: 
*/
 
#ifndef RAT
#define RAT
#include "raylib.h"
#include <stdlib.h>
#include "animation.h"
#include "camera.h"
 
class Rat
{
public:
//your code here (constructors getters setters and function headers)
Rat(Vector2 startingPosition); // constructor

// getters
Vector2 GetPosition(){return ratPos;}
Rectangle getHitbox(){return hitbox;}

// animation stuff
void initializeAnimations();
void doAnimations();

// physics and updating 
void UpdatePhysics();

void Update();
bool Dead();
void cleanUp();


private:
    Rectangle hitbox;
    const int screenWidth = 800;
    const int screenHeight = 450;
    SpriteAnimation rat_animation; // enemy rats updated animation
    SpriteAnimation ratWalk;
    SpriteAnimation ratDie;
    SpriteAnimation ratDead;
    int currentFrame = 0;
    Texture2D rat = LoadTexture("Images/enemy_rat.png");
    const float ratSize = 32;
    float scale = 4.0f;
    Vector2 ratPos;
    bool isDead;
    bool ratDied = 0;
};
#endif