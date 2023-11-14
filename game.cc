/**
*  @file: game.cc
*  @author: cashcraf
*  @date: 2023-11-06 
*  @brief: 
*/

#include "Headers/game.h"

Game::Game(int numRats, int numOwls, int level) : waffle(Vector2{1, (float)screenHeight - 32}) { // this is passed a number of rats and then the level number
    game_objects = new GameObjects();
    levelnum = level;
    this->numRats = numRats;
    this->numOwls = numOwls;
    isWaffleHitRat.resize(numRats, false);
    isWaffleHitOwl.resize(numOwls, false);
    ratDead.resize(numRats, false);
    owlDead.resize(numOwls, false);
    isWaffleHittingRat.resize(numRats, false);
    isWaffleHittingOwl.resize(numRats, false);
    ratHasCollided.resize(numRats, false);
    owlHasCollided.resize(numOwls, false);

    isHitting = false;

    // camera
    camera = waffle.getWafflesCamera();

    // stamina
    stamina = 400; // reset to 400 or whatever you want 
    staminaBar = {camera.target.x + 10, camera.target.y + 10, stamina, 20};

}

void Game::initializeGame() {
    infiniteStamina = false;
    game_restart = false;
    win = false;
    waffle.initializeAnimations();
    rats.reserve(numRats);
    


    for (int i = 0; i < numRats; i++) {
        Vector2 startingPositionRat = {(float)GetRandomValue(0, 10000), screenHeight - 32};
        Rat rat(startingPositionRat);
        rat.initializeAnimations();
        rats.push_back(rat);
    }

    owls.reserve(numOwls);
    for (int i = 0; i < numOwls; i++) {
        Vector2 startingPositionOwl = {(float)GetRandomValue(0, 10000), (screenHeight +32)/2};
        Owl owl(startingPositionOwl);
        owl.initializeAnimations();
        owls.push_back(owl);
    }

    // stamina
    staminaSubtract = false;
    staminaSubtractJump = false;
    staminaSubtractHit = false;

    // level drawing
    if (levelnum == 1) {
        background = LoadTexture("Images/2D_courtSt.png");
    }
    else if (levelnum == 2){
        background = LoadTexture("Images/2D_college_green.png");
    }
    else if (levelnum == 3){
        background = LoadTexture("Images/2D_alden.png");
    }

    // sprite drawing
    winningTexture = LoadTexture("Images/winning.png"); // cant get data
    winningHitbox = (Rectangle){6950, (float)screenHeight - 100, 32*2, 32*4};


    // sound
    waffle.initializeSounds();

    // game objects
    game_objects->InitializeObjects(levelnum);

}

void Game::updateGame() {
    Vector2 wafflePos = waffle.getWafflePos();
    if (wafflePos.x < 6500) {
        camera.target = (Vector2){wafflePos.x + 32, screenHeight};
    }
    
    Rectangle waffleHitbox = waffle.getHitbox();
    waffleHasCollided = game_objects->CheckCollisionWithObject(waffleHitbox, true);
    
    for (int i = 0; i < numRats; i++) {
        Rectangle ratHitbox = rats[i].getHitbox();
        if (ratHasCollided[i]){
            ratHasCollided[i] = false;
        }
        ratHasCollided[i] = game_objects->CheckCollisionWithObject(ratHitbox, false);
        

        
        if (!ratDead[i]){
            isWaffleHitRat[i] = CheckCollisionRecs(waffleHitbox, ratHitbox);
        }
        if (isWaffleHitRat[i] && !ratDead[i]){
            PlaySound(hurt);
            stamina -= 4;
        }
    }

     for (int i = 0; i < numOwls; i++) {
        Rectangle owlHitbox = owls[i].getHitbox();
        if (owlHasCollided[i]){
            owlHasCollided[i] = false;
        }
        owlHasCollided[i] = game_objects->CheckCollisionWithObject(owlHitbox, false);

        
        if (!owlDead[i]){
            isWaffleHitOwl[i] = CheckCollisionRecs(waffleHitbox, owlHitbox);
        }
        if (isWaffleHitOwl[i] && !owlDead[i]){
            PlaySound(hurt);
            stamina -= 4;
        }
    }

    isHitting = waffle.getIsHitting();
    if (isHitting){
    stamina -= 4;
    Rectangle waffleHittingHitbox = waffle.getHittingHitbox();
        for (int i = 0; i < numRats; i++) {
            Rectangle ratHitbox2 = rats[i].getHitbox();
            
            if (!ratDead[i]){
                isWaffleHittingRat[i] = CheckCollisionRecs(waffleHittingHitbox, ratHitbox2);
            }
            if (isWaffleHittingRat[i] && !ratDead[i]){
                ratDead[i] = rats[i].Dead();
                stamina += 100;
            }
        }

        for (int i = 0; i < numOwls; i++) {
            Rectangle owlHitbox2 = owls[i].getHitbox();
            
            if (!owlDead[i]){
                isWaffleHittingOwl[i] = CheckCollisionRecs(waffleHittingHitbox, owlHitbox2);
            }
            if (isWaffleHittingOwl[i] && !owlDead[i]){
                owlDead[i] = owls[i].Dead();
                stamina += 100;
            }
        }
    }

    win = CheckCollisionRecs(waffleHitbox, winningHitbox);
    if (win){
        waffle.waffleWins();
    }

    staminaSubtract = waffle.getIsMoving();
    staminaSubtractJump = waffle.getIsJumping();
    staminaSubtractHit = waffle.getIsHitting();
    
    if (staminaSubtract && stamina != 0) {
        stamina -= 0.05;
    }
    if (staminaSubtractJump && stamina != 0) {
        stamina -= 1;
    }

    if (stamina <= 0) {
        game_restart = waffle.lose();
    }

    if (IsKeyPressed(KEY_S)){
        stamina += 5000;    // "infinite" stamina mode!
        infiniteStamina = true;      
    }

    collisionSideRightGame = game_objects->getCollisionSideRight();
    collisionSideLeftGame = game_objects->getCollisionSideLeft();
    if (collisionSideRightGame){
        stamina -= 0.1;
    }

    waffle.Update(waffleHasCollided, collisionSideRightGame, collisionSideLeftGame);
    for (size_t i = 0; i < rats.size(); i++) {
        rats[i].Update(ratHasCollided[i]);  
    }

    for (size_t i = 0; i < owls.size(); i++) {
        owls[i].Update(owlHasCollided[i]);  // Using owlHasCollided indexed to correspond to the respective owl
    }
    
    staminaBar.x = camera.target.x - 100;
    staminaBar.y = camera.target.y - 400;
    
}

void Game::drawGame() {
    BeginMode2D(camera);
    ClearBackground(WHITE);
    DrawTexture(background, -(float)screenWidth / 6, 0, WHITE);
    if (infiniteStamina){
        Vector2 wafflePos = waffle.getWafflePos();
        DrawText("\"Infinite\" stamina mode activated!", wafflePos.x, 10, 30, GREEN);
        
    }
    if (levelnum == 1){
    DrawText("Level 1: Court St", 10, 10, 20, WHITE);
    }
    if (levelnum == 2){
    DrawText("Level 2: College Green", 10, 10, 20, WHITE);
    }
        if (levelnum == 3){
    DrawText("Level 3: Alden Library", 10, 10, 20, WHITE);
    }
    game_objects->DrawObjects();


    // draw winning waffle
    Rectangle dest = (Rectangle){7000, (float)screenHeight - 100, 32*2, 32*2}; 
    Vector2 origin = {0, 0};
    Rectangle source = { 0, 0, (float)winningTexture.width, (float)winningTexture.height };

    DrawTexturePro(winningTexture, source, dest, origin, 0, WHITE);



    waffle.doAnimations();
    for (Rat& rat : rats) {
        rat.doAnimations();
    }

    for (Owl& owl : owls) {
        owl.doAnimations();
    }
    
    float greenWidth = (stamina / 400.0f) * (staminaBar.width - 4);
    
    DrawRectangle(staminaBar.x, staminaBar.y, greenWidth, staminaBar.height - 4, LIME);
    DrawRectangleLinesEx(staminaBar, 5, BLACK);
    
    EndMode2D();
    EndDrawing();
}

bool Game::checkLose(){
    return game_restart;
}

bool Game::checkWin(){
    return win;
}


void Game::cleanUp() {
    UnloadTexture(background);
    for (int i = 0; i < numRats; i++) {
        rats[i].cleanUp();
    }
    for (int i = 0; i < numOwls; i++) {
        owls[i].cleanUp();
    }
    waffle.cleanUp();
    UnloadSound(hurt);
    game_objects->cleanUp();
    delete game_objects;
}

