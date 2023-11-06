#ifndef GAME_H
#define GAME_H
#include <vector>
#include <stdlib.h>
#include "raylib.h"
#include "animation.h"
#include "camera.h"
#include "waffle.h"
#include "rat.h"


class Game {
public:
    Game(int numRats, int level);
    void initializeGame();
    void updateGame();
    void drawGame();
    void cleanUp();
    bool checkLose();
    bool checkWin();
    Rectangle getWinningHitbox(){return winningHitbox;}

private:
    int levelnum;
    const float screenHeight = 450; // Remove the 'const' keyword for initialization in the constructor
    const float screenWidth = 800;

    Texture2D background;
    Texture2D winningTexture;
    SpriteAnimation winningWaffle;


    // Stamina 
    float stamina;
    Rectangle staminaBar;
    bool staminaSubtract;
    bool staminaSubtractJump;
    bool staminaSubtractHit;
    Color staminaBorderColor;
    Color staminaFillColor;
    int numRats;

    // boolean values for enemy collisions
    std::vector<bool> isWaffleHit;
    std::vector<bool> ratDead;
    std::vector<bool> isWaffleHitting;
    bool isHitting;
    bool game_restart;
    Rectangle winningHitbox;
    bool win;

    // camera stuff
    Camera2D camera;
    Waffle waffle;
    std::vector<Rat> rats;
};

#endif
