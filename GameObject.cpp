#include "Structures.h"



void ConvertUnitPixelToMap(GameObject* gameObject) 
{

	gameObject->currentChipNo.x = static_cast<int>(gameObject->pos.x / 50.0f);
	gameObject->currentChipNo.y = static_cast<int>((700.0f - gameObject->pos.y) / 50.0f);

}