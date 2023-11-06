/**
*  @file: animation.cc
*  @author: cashcraf
*  @date: 2023-11-06 
*  @brief: 
*/
 
#include "Headers/animation.h"

SpriteAnimation CreateSpriteAnimation(Texture2D atlas, int framesPerSecond, Rectangle rectangles[], int Length){
    SpriteAnimation SpriteAnimation = 
    {
    .atlas = atlas,
    .framesPerSecond = framesPerSecond,
    .rectangles = NULL,
    .rectanglesLength = Length
    };
    Rectangle* mem = (Rectangle*) malloc(sizeof(Rectangle) * Length);
    
    if (mem == NULL){ // a very cautious check
        TraceLog(LOG_FATAL, "No memory for CreateSpriteAnimation");
        SpriteAnimation.rectanglesLength = 0;
         return SpriteAnimation;
    
    }
    SpriteAnimation.rectangles = mem;
    for (int i = 0; i < Length; i++){
        SpriteAnimation.rectangles[i] = rectangles[i];
    }

    return SpriteAnimation;
}

void DisposeSpriteAnimation(SpriteAnimation animation){ // deallocate memory
    free(animation.rectangles);
}

void DrawSpriteAnimationPro(SpriteAnimation animation, Rectangle destination, Vector2 theOrigin, float rotation, Color tint){
    int index = (int) (GetTime() * animation.framesPerSecond) % animation.rectanglesLength;
    
    Rectangle source = animation.rectangles[index];
    DrawTexturePro(animation.atlas, source, destination, theOrigin, rotation, tint);
}