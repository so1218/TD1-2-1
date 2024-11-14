#include "Structures.h"
#include "GrovalTextureHandles.h"

extern int GHs[128];

//テキスチャの読み込み
void TextureManager::LoadTextures()
{
    GHs[TextureName::Particle1] = Novice::LoadTexture("./Resources/Images/sparkle.png");
}