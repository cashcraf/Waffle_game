    /**
    *  @file: rat.cc
    *  @author: cashcraf
    *  @date: 2023-10-18 
    *  @brief: 
    */
     
    #include<iostream>
    #include<string>
    
    using namespace std;
    // function defs here
    SpriteAnimation rat_animation; // enemy rats updated animation
    SpriteAnimation ratWalk;

    Rectangle ratWalkFrames[] = {
    (Rectangle){waffle_index * waffleSize, 0, waffleSize, waffleSize},
    (Rectangle){waffle_index + 1 * waffleSize, 0, waffleSize, waffleSize},
    (Rectangle){waffle_index + 2 * waffleSize, 0, waffleSize, waffleSize},
    (Rectangle){waffle_index + 3 * waffleSize, 0, waffleSize, waffleSize},
    (Rectangle){waffle_index * waffleSize, 32, waffleSize, waffleSize},  // collum 2 
    (Rectangle){waffle_index + 1 * waffleSize, 32, waffleSize, waffleSize}, 
    (Rectangle){waffle_index + 2 * waffleSize, 32, waffleSize, waffleSize},
    (Rectangle){waffle_index + 3 * waffleSize, 32, waffleSize, waffleSize}


    };
    ratWalk = CreateSpriteAnimation(rat, 2, ratWalkFrames, 8);