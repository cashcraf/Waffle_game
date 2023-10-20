/**
*  @file: annimation.h
*  @author: cashcraf
*  @date: 2023-10-15 
*  @brief: 
*/
 
#ifndef ANNIMATION_H_// name of class in all caps_H
#define ANNIMATION_H_//name of class in all caps_H
#include "raylib.h"
using namespace std;
 
typedef struct SpriteAnimation
{
    Texture2D atlas;
    int framesPerSecond;

    Rectangle* rectangles;
    int rectanglesLength;

} SpriteAnimation;

SpriteAnimation CreateSpriteAnimation(Texture2D atlas, int framesPerSecond, Rectangle rectangles[], int Length);
void DisposeSpriteAnimation(SpriteAnimation animation);
void DrawSpriteAnimationPro(SpriteAnimation animation, Rectangle destination, Vector2 theOrigin, float rotation, Color tint);
#endif