#include "Structures.h"

//カメラ関係

void shakeCamera(Camera* camera) 
{
    if (camera->shakeCounter < camera->shakeDuration) 
    {
        camera->randCameraX = rand() % (camera->magnitude * 2 + 1) - camera->magnitude;
        camera->randCameraY = rand() % (camera->magnitude * 2 + 1) - camera->magnitude;
   
        camera->shakeCounter++;
        camera->magnitude -= 1;
    }
    else 
    {
        // シェイク終了後にカメラを元の位置に戻す
        camera->randCameraX = 0;
        camera->randCameraY = 0;
        camera->shakeCounter = 0; // カウンターをリセット
        camera->magnitude = 20;
        camera->isShake = false;
    }
}