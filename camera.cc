/**
*  @file: camera.cc
*  @author: cashcraf
*  @date: 2023-11-06 
*  @brief: 
*/
 
#include "Headers/camera.h"

Camera2D InitiateCamera(Vector2 target, int screenWidth, int screenHeight) {
    Camera2D camera = {0};
    camera.target = target;
    camera.offset = (Vector2){(float)screenWidth /6, (float)screenHeight};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    return camera;
}
