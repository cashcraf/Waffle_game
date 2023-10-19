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
Rat(Vector2 position, float width, float height); // constructor

Rectangle GetPosition(){return position;}
float GetWidth(){return width;}
float GetHeight(){return height;}


void Update();
bool Dead();


private:
    Rectangle position;
    float width;
    float height;
    SpriteAnimation rat_animation; // enemy rats updated animation
    SpriteAnimation ratWalk;
    Texture2D rat = LoadTexture("Images/enemy_rat.png");
    const float ratSize = 32;
};
#endif