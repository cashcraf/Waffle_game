#ifndef GAME_H
#define GAME_H
#include <vector>
#include <stdlib.h>
#include "raylib.h"
#include "animation.h"
#include "camera.h"
#include "waffle.h"
#include "rat.h"
#include "owl.h"
#include "game_objects.h"


class Game {
public:
    Game(int numRats, int numOwls, int level);
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
    int numOwls;
    bool infiniteStamina;

    // boolean values for enemy collisions
    std::vector<bool> isWaffleHitRat;
    std::vector<bool> isWaffleHitOwl;
    std::vector<bool> ratDead;
    std::vector<bool> owlDead;
    std::vector<bool> isWaffleHittingRat;
    std::vector<bool> isWaffleHittingOwl;
    bool isHitting;
    bool game_restart;
    Rectangle winningHitbox;
    bool win;

    // camera stuff
    Camera2D camera;
    Waffle waffle;
    std::vector<Rat> rats;
    std::vector<Owl> owls;


    // game objects
    GameObjects *game_objects;
    bool waffleHasCollided = false;
    std::vector<bool> ratHasCollided;
    std::vector<bool> owlHasCollided;

    bool collisionSideRightGame = false;
    bool collisionSideLeftGame = false;

    // sounds
    Sound hurt = LoadSound("Sounds/hurt.wav");

};

#endif
