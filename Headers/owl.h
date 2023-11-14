/**
*  @file: owl.h
*  @author: cashcraf
*  @date: 2023-11-8 
*  @brief: 
*/
 
#ifndef OWL
#define OWL
#include "raylib.h"
#include <stdlib.h>
#include "animation.h"
#include "camera.h"
 
class Owl
{
public:
//your code here (constructors getters setters and function headers)
Owl(Vector2 startingPosition); // constructor

// getters
Vector2 GetPosition(){return owlPos;}
Rectangle getHitbox(){return hitbox;}

// animation stuff
void initializeAnimations();
void doAnimations();

// physics and updating 
void UpdatePhysics(bool hasCollided);

void Update(bool hasCollided);
bool Dead();
void cleanUp();


private:
    Rectangle hitbox;
    const int screenWidth = 800;
    const int screenHeight = 450;
    SpriteAnimation owl_animation; // enemy rats updated animation
    SpriteAnimation owlFlyRight;
    SpriteAnimation owlFlyLeft;
    SpriteAnimation owlDie;
    SpriteAnimation owlDead;
    int currentFrame = 0;
    Texture2D owl = LoadTexture("Images/enemy_owl.png");
    const float owlSize = 32;
    float scale = 4.0f;
    Vector2 owlPos;
    bool isDead;
    bool owlDied = 0;
    bool isLeft = true;

    const float gravity = 0.2;
    float x_velocity = 5;
    float y_velocity = 0; // because of the origin being 0,0 being the top left
};
#endif