    /**
    *  @file: Owl.cc
    *  @author: cashcraf
    *  @date: 2023-11-8 
    *  @brief: 
    */
     
    #include "Headers/owl.h"

    Owl::Owl(Vector2 startingPosition){
        owlPos = startingPosition; // initialize owl pos at its staring position
        hitbox = {owlPos.x, owlPos.y, owlSize*(scale-1), owlSize*(scale-1)};
        isDead = 0;

    }
    void Owl::Update(bool hasCollided){
        UpdatePhysics(hasCollided);
    }

    void Owl::UpdatePhysics(bool hasCollided){
        // to do: add a if collision with any of the objects class and is left is already true isLeft = false
        // but if collision with any of the objects class and is not left is left = true
        
        if (hasCollided && isLeft){
            isLeft = false;    
        }
        else if (hasCollided && !isLeft){
            isLeft = true;
        }

        if (!isDead && isLeft){
        owl_animation = owlFlyLeft; // starts out alive and walking left
        float moveSpeed = 1.0;
        owlPos.x -= moveSpeed;
        hitbox = {owlPos.x, owlPos.y, owlSize-10, owlSize+10};
        }
        else if (!isDead && !isLeft){
        owl_animation = owlFlyRight;
        float moveSpeed = 1.0;
        owlPos.x += moveSpeed;
        hitbox = {owlPos.x, owlPos.y, owlSize-10, owlSize+10};
        }
        else {
            // do nothing
        }
    }

void Owl::doAnimations() {
    Rectangle owlDest = {owlPos.x, owlPos.y, owlSize * scale, owlSize * scale};
    Vector2 owlOrigin = {0, owlSize * (scale - 1)};

    if (isDead && !owlDied) {
        // Play the dying animation
        DrawSpriteAnimationPro(owlDead, owlDest, owlOrigin, 0, WHITE);
            owl_animation = owlDead;
            owlDied = 1;

        
    } else {
        // Draw the living animation
        if (owl_animation.rectangles != NULL) {
            DrawSpriteAnimationPro(owl_animation, owlDest, owlOrigin, 0, WHITE);
        }
    }
}

    bool Owl::Dead(){ // Idk what I want this to return yet
        isDead = 1;
        //owl_animation = owlDie;
        
        while (currentFrame < 240){
        currentFrame++;
        y_velocity += gravity; // apply gravity
        owlPos.y += y_velocity; // update postion
        if (owlPos.y > screenHeight - owlSize) {
            // Ensure the character stays on the ground
            owlPos.y = screenHeight;
            y_velocity = 0;
        hitbox = {owlPos.x, owlPos.y, owlSize, owlSize}; // update hitbox
        }
        }
        return isDead;
    }

    void Owl::cleanUp(){
        UnloadTexture(owl);
    }

    void Owl::initializeAnimations(){
        Rectangle owlFlyLeftFrames[] = {
        (Rectangle){0, 0, owlSize, owlSize},
        (Rectangle){ 1 * owlSize, 0, owlSize, owlSize},
        (Rectangle){2 * owlSize, 0, owlSize, owlSize},
        };
        owlFlyLeft = CreateSpriteAnimation(owl, 6, owlFlyLeftFrames, 3);

        // dying animation
        Rectangle owlDeadFrame[] = { 6 * owlSize, 0, owlSize, owlSize};
        owlDead = CreateSpriteAnimation(owl, 1, owlDeadFrame, 1);

        Rectangle owlFlyRightFrames[] = {
        (Rectangle){3* owlSize, 0, owlSize, owlSize},
        (Rectangle){ 4 * owlSize, 0, owlSize, owlSize},
        (Rectangle){5 * owlSize, 0, owlSize, owlSize}

        };
        owlFlyRight = CreateSpriteAnimation(owl, 6, owlFlyRightFrames, 3);

    }