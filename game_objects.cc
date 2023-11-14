#include "Headers/game_objects.h"

GameObjects::GameObjects(){
    screenHeight = 450;
    screenWidth = 800;
}

void GameObjects::InitializeObjects(int levelNum) {
    objectRectangles.clear();
    objectRectangles.resize(NUM_OBJECTS, Rectangle{0, 0, 0, 0});

    level_num = levelNum;
    // Load the spritesheet

    // Define the y-coordinate for all objects on the spritesheet
    // x needs to be changed

    if (level_num == 1){
    small_tower = LoadTexture("Images/small_pipe.png");
    large_tower = LoadTexture("Images/large_pipe.png");
    boxes = LoadTexture("Images/boxes.png");

    // Object 1: Small Pipe 1
    objectRectangles[0] = {500, (float)(screenHeight/2) + 133, 127, 91}; // Adjust these values based on your needs x y width height

    // Object 2: Large Pipe 1
    objectRectangles[1] = {1000, (float)(screenHeight/2) + 38, 127, 188}; // Adjust these values based on your needs

    // Object 3: Box 1
    objectRectangles[2] = {1500, (float)screenHeight/2, 188, 54}; // Adjust these values based on your needs

    // Object 1: Small Pipe 2
    objectRectangles[3] = {3000, (float)(screenHeight/2) + 133, 127, 91}; // Adjust these values based on your needs x y width height

    // Object 2: Large Pipe 2
    objectRectangles[4] = {3500, (float)(screenHeight/2) + 38, 127, 188}; // Adjust these values based on your needs

    // Object 3: Box 2
    objectRectangles[5] = {4000, (float)screenHeight/2, 188, 54}; // Adjust these values based on your needs

    // Object 1: Small Pipe 3
    objectRectangles[6] = {5000, (float)(screenHeight/2) + 133, 127, 91}; // Adjust these values based on your needs x y width height
 
    // Object 2: Large Pipe 3
    objectRectangles[7] = {5500, (float)(screenHeight/2) + 38, 127, 188}; // Adjust these values based on your needs

    // Object 3: Box 3
    objectRectangles[8] = {6000, (float)screenHeight/2, 188, 54}; // Adjust these values based on your needs
    }

    if (level_num == 2){
    tree = LoadTexture("Images/tree.png");
    bush = LoadTexture("Images/bush.png");

    // Object 4: Tree 1
    objectRectangles[9] = {500, (float) (screenHeight/2) + 32, 202, 197}; // Adjust these values based on your needs

    // Object 5: Bush 1
    objectRectangles[10] = {1500, (float)(screenHeight/2) + 125, 229, 101}; // Adjust these values based on your needs

    // Object 4: Tree 2
    objectRectangles[11] = {2500, (float) (screenHeight/2) + 32, 202, 197}; // Adjust these values based on your needs

    // Object 5: Bush 2
    objectRectangles[12] = {3000, (float)(screenHeight/2) + 125, 229, 101}; // Adjust these values based on your needs
    
    // Object 4: Tree 3
    objectRectangles[13] = {4500, (float) (screenHeight/2) + 32, 202, 197}; // Adjust these values based on your needs

    // Object 5: Bush 3
    objectRectangles[14] = {5500, (float)(screenHeight/2) + 125, 229, 101}; // Adjust these values based on your needs
    
    }

    if (level_num == 3){
    bookshelf = LoadTexture("Images/bookshelf.png");
    desk = LoadTexture("Images/desk.png");

    
    // Object 6: Bookshelf 1
    objectRectangles[15] = {500, (float)(screenHeight/2) + 35, 217, 191}; // Adjust these values based on your needs

    // Object 7: Desk 1
    objectRectangles[16] = {1500,(float)(screenHeight/2) + 100, 180, 191}; // Adjust these values based on your needs

    // Object 6: Bookshelf 2
    objectRectangles[17] = {2500, (float)(screenHeight/2) + 35, 217, 191}; // Adjust these values based on your needs

    // Object 7: Desk 2
    objectRectangles[18] = {3500,(float)(screenHeight/2) + 100, 180, 191}; // Adjust these values based on your needs

    // Object 6: Bookshelf 3
    objectRectangles[19] = {4500, (float)(screenHeight/2) + 35, 217, 191}; // Adjust these values based on your needs

    // Object 7: Desk 3
    objectRectangles[20] = {5500,(float)(screenHeight/2) + 100, 180, 191}; // Adjust these values based on your needs
    }

}


bool GameObjects::CheckCollisionWithObject(Rectangle rect, bool is_waffle) {
    // Check collision with each game object

    if (level_num == 1){
        for (int i = 0; i < objectRectangles.size(); ++i) {
        if (CheckCollisionRecs(rect, objectRectangles[i])) {
            
            if (is_waffle){
                // doesnt work if on top of objects
                if (rect.y > objectRectangles[i].height + screenHeight - 40) {
                // Waffle is above the object, collisions aren't affecting side detection
                collisionSideRight = false;
                collisionSideLeft = false;
                } else {
                if (rect.x > objectRectangles[i].x + (objectRectangles[i].width / 2 )){
                    collisionSideLeft = true;
                }
                else if (rect.x < objectRectangles[i].x + (objectRectangles[i].width / 2)){
                    collisionSideRight = true;
                }
                else {
                    collisionSideRight = false; // false for default
                    collisionSideLeft = false ; // false for default
                }
            }
            }

            return true; // Collision detected
        }

        if (!CheckCollisionRecs(rect, objectRectangles[i])) {
                if(is_waffle){
                collisionSideRight = false;
                collisionSideLeft = false;
                }
            
        }

        }
        
        
        
    }

    else if (level_num == 2){
        for (int i = 9; i < objectRectangles.size(); ++i) {
            if (CheckCollisionRecs(rect, objectRectangles[i])) {
            
                if (is_waffle){
                    // doesnt work if on top of objects
                    if (rect.y > objectRectangles[i].height + screenHeight - 40) {
                    // Waffle is above the object, collisions aren't affecting side detection
                    collisionSideRight = false;
                    collisionSideLeft = false;
                    } else {
                    if (rect.x > objectRectangles[i].x + (objectRectangles[i].width / 2 )){
                        collisionSideLeft = true;
                    }
                    else if (rect.x < objectRectangles[i].x + (objectRectangles[i].width / 2)){
                        collisionSideRight = true;
                    }
                    else {
                        collisionSideRight = false; // false for default
                        collisionSideLeft = false ; // false for default
                    }
                }
                }

            return true; // Collision detected
        }

        if (!CheckCollisionRecs(rect, objectRectangles[i])) {
                if(is_waffle){
                collisionSideRight = false;
                collisionSideLeft = false;
                }
            
        }

        }
        
        
        
    }
    

    else if (level_num == 3){
        for (int i = 15; i < objectRectangles.size(); ++i) {
            if (CheckCollisionRecs(rect, objectRectangles[i])) {
            
                if (is_waffle){
                    // doesnt work if on top of objects
                    if (rect.y > objectRectangles[i].height + screenHeight - 40) {
                    // Waffle is above the object, collisions aren't affecting side detection
                    collisionSideRight = false;
                    collisionSideLeft = false;
                    } else {
                    if (rect.x > objectRectangles[i].x + (objectRectangles[i].width / 2 )){
                        collisionSideLeft = true;
                    }
                    else if (rect.x < objectRectangles[i].x + (objectRectangles[i].width / 2)){
                        collisionSideRight = true;
                    }
                    else {
                        collisionSideRight = false; // false for default
                        collisionSideLeft = false ; // false for default
                    }
                }
                }

            return true; // Collision detected
        }

        if (!CheckCollisionRecs(rect, objectRectangles[i])) {
                if(is_waffle){
                collisionSideRight = false;
                collisionSideLeft = false;
                }
            
        }

        }
        
        
        
    }
        return false; // No collision

}

void GameObjects::DrawObjects() {
    if (level_num == 1){
         // Keep objects 0, 1 and 2 visible

        DrawTexture(small_tower, objectRectangles[0].x + 50, objectRectangles[0].y, WHITE);
        DrawTexture(large_tower, objectRectangles[1].x + 50, objectRectangles[1].y, WHITE);
        DrawTexture(boxes, objectRectangles[2].x + 50, objectRectangles[2].y, WHITE);

        DrawTexture(small_tower, objectRectangles[3].x + 50, objectRectangles[3].y, WHITE);
        DrawTexture(large_tower, objectRectangles[4].x + 50, objectRectangles[4].y, WHITE);
        DrawTexture(boxes, objectRectangles[5].x + 50, objectRectangles[5].y, WHITE);

        DrawTexture(small_tower, objectRectangles[6].x + 50, objectRectangles[6].y, WHITE);
        DrawTexture(large_tower, objectRectangles[7].x + 50, objectRectangles[7].y, WHITE);
        DrawTexture(boxes, objectRectangles[8].x + 50, objectRectangles[8].y, WHITE);
    }

    if (level_num == 2){
         // Keep objects 3 and 4 visible
        DrawTexture(tree, objectRectangles[9].x + 50, objectRectangles[9].y, WHITE);
        DrawTexture(bush, objectRectangles[10].x + 50, objectRectangles[10].y, WHITE);

        DrawTexture(tree, objectRectangles[11].x + 50, objectRectangles[11].y, WHITE);
        DrawTexture(bush, objectRectangles[12].x + 50, objectRectangles[12].y, WHITE);

        DrawTexture(tree, objectRectangles[13].x + 50, objectRectangles[13].y, WHITE);
        DrawTexture(bush, objectRectangles[14].x + 50, objectRectangles[14].y, WHITE);
    }

    if (level_num == 3) {
         // Keep objects 5 and 6 visible
        DrawTexture(bookshelf, objectRectangles[15].x + 50, objectRectangles[15].y, WHITE);
        DrawTexture(desk, objectRectangles[16].x + 50, objectRectangles[16].y, WHITE);

        DrawTexture(bookshelf, objectRectangles[17].x + 50, objectRectangles[17].y, WHITE);
        DrawTexture(desk, objectRectangles[18].x + 50, objectRectangles[18].y, WHITE);

        DrawTexture(bookshelf, objectRectangles[19].x + 50, objectRectangles[19].y, WHITE);
        DrawTexture(desk, objectRectangles[20].x + 50, objectRectangles[20].y, WHITE);
    }

}

void GameObjects::cleanUp(){
    objectRectangles.clear();
    
    if (level_num == 1){
    UnloadTexture(small_tower);
    UnloadTexture(large_tower);
    UnloadTexture(boxes);
    }
    if (level_num == 2){
    UnloadTexture(tree);
    UnloadTexture(bush);
    }
    if (level_num == 3){
    UnloadTexture(bookshelf);
    UnloadTexture(desk);
    }
}