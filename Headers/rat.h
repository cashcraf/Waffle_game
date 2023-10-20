/**
*  @file: rat.h
*  @author: cashcraf
*  @date: 2023-10-18 
*  @brief: 
*/
 
#ifndef RAT
#define RAT
#include "raylib.h"
#include "animation.h"
#include "camera.h"
#include "waffle.h"

using namespace std;
 
class Rat
{
public:
//your code here (constructors getters setters and function headers)
Rat(Vector2 startingPosition); // constructor

// getters
Vector2 GetPosition(){return ratPos;}

// animation stuff
void initializeAnimations();
void doAnimations();

// physics and updating 
void UpdatePhysics();
void UpdateKeysAndAnimations();

void Update();
bool Dead();


private:
    const int screenWidth = 800;
    const int screenHeight = 450;
    SpriteAnimation rat_animation; // enemy rats updated animation
    SpriteAnimation ratWalk;
    SpriteAnimation ratDie;
    Texture2D rat = LoadTexture("Images/enemy_rat.png");
    const float ratSize = 32;
    float scale = 4.0f;
    Vector2 ratPos;
};
#endif