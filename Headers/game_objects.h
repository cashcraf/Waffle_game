/**
*  @file: game_objects.h
*  @author: cashcraf
*  @date: 2023-11-08 
*  @brief: 
*/
 
#ifndef GAMEOBJECTS
#define GAMEOBJECTS

#include "raylib.h"
#include <vector>

class GameObjects {
public:
    // constructor
    GameObjects();

    // Initialize the game objects
    void InitializeObjects(int levelNum);

    // Check collision with a given rectangle
    bool CheckCollisionWithObject(Rectangle rect, bool is_waffle);

    // Draw all game objects
    void DrawObjects();

    // Clean up
    void cleanUp();

    bool getCollisionSideRight() {return collisionSideRight;}
    bool getCollisionSideLeft() {return collisionSideLeft;}


private:
    int screenHeight;
    int screenWidth;
    int level_num;
    int NUM_OBJECTS = 21; // Change this value to 14 if you want 2 of each type
    std::vector<Rectangle> objectRectangles;

    Texture2D small_tower;
    Texture2D large_tower;
    Texture2D boxes;
    Texture2D tree;
    Texture2D bush;
    Texture2D bookshelf;
    Texture2D desk;

    bool collisionSideRight = false;
    bool collisionSideLeft = false;




};

#endif