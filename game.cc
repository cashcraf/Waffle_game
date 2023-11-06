#include "Headers/game.h"

Game::Game(int numRats, int level) : waffle(Vector2{1, (float)screenHeight - 32}) { // this is passed a number of rats and then the level number
    levelnum = level;
    this->numRats = numRats;
    isWaffleHit.resize(numRats, false);
    ratDead.resize(numRats, false);
    isWaffleHitting.resize(numRats, false);
    isHitting = false;

    // camera
    camera = waffle.getWafflesCamera();

    // stamina
    stamina = 300;
    staminaBar = {camera.target.x + 10, camera.target.y + 10, stamina, 20};
}

void Game::initializeGame() {
    game_restart = false;
    win = false;
    waffle.initializeAnimations();
    rats.reserve(numRats);

    for (int i = 0; i < numRats; i++) {
        Vector2 startingPosition = {(float)GetRandomValue(0, 10000), screenHeight - 32};
        Rat rat(startingPosition);
        rat.initializeAnimations();
        rats.push_back(rat);
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
        // make background the baker center
    }

    // sprite drawing
    winningTexture = LoadTexture("Images/winning.png"); // cant get data
    winningHitbox = (Rectangle){6950, (float)screenHeight - 100, 32*2, 32*4};


    // sound
    waffle.initializeSounds();

}

void Game::updateGame() {
    Vector2 wafflePos = waffle.getWafflePos();
    if (wafflePos.x < 6500) {
        camera.target = (Vector2){wafflePos.x + 32, screenHeight};
    }
    
    Rectangle waffleHitbox = waffle.getHitbox();
    
    for (int i = 0; i < numRats; i++) {
        Rectangle rat1Hitbox = rats[i].getHitbox();
        
        if (!ratDead[i]){
            isWaffleHit[i] = CheckCollisionRecs(waffleHitbox, rat1Hitbox);
        }
        if (isWaffleHit[i] && !ratDead[i]){
            stamina -= 4;
        }
    }

    isHitting = waffle.getIsHitting();
    if (isHitting){
    stamina -= 4;
    Rectangle waffleHittingHitbox = waffle.getHittingHitbox();
        for (int i = 0; i < numRats; i++) {
            Rectangle rat1Hitbox2 = rats[i].getHitbox();
            
            if (!ratDead[i]){
                isWaffleHitting[i] = CheckCollisionRecs(waffleHittingHitbox, rat1Hitbox2);
            }
            if (isWaffleHitting[i] && !ratDead[i]){
                ratDead[i] = rats[i].Dead();
                stamina += 20;
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

    waffle.Update();
    
    for (Rat& rat : rats) {
        rat.Update();
    }
    
    staminaBar.x = camera.target.x - 100;
    staminaBar.y = camera.target.y - 400;
}

void Game::drawGame() {
    BeginMode2D(camera);
    ClearBackground(WHITE);
    DrawTexture(background, -(float)screenWidth / 6, 0, WHITE);
    DrawText("move waffle with arrow keys", 10, 10, 20, WHITE);


    // draw winning waffle
    Rectangle dest = (Rectangle){7000, (float)screenHeight - 100, 32*2, 32*2}; 
    Vector2 origin = {0, 0};
    Rectangle source = { 0, 0, (float)winningTexture.width, (float)winningTexture.height };

    DrawTexturePro(winningTexture, source, dest, origin, 0, WHITE);



    waffle.doAnimations();
    for (Rat& rat : rats) {
        rat.doAnimations();
    }
    
    float greenWidth = (stamina / 300.0f) * (staminaBar.width - 4);
    
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
    waffle.cleanUp();
}

