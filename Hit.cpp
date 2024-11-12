#include "Structures.h"

bool CheckRectangleRectangleCollision(RectangleObject* rect1, RectangleObject* rect2)
{

    if (rect1->vertex.rightTop.x < rect2->vertex.leftTop.x)
        return false;
   
    if (rect1->vertex.leftTop.x > rect2->vertex.rightTop.x)
        return false;
    
    if (rect1->vertex.leftTop.y < rect2->vertex.rightBottom.y)
        return false;
    
    if (rect1->vertex.rightBottom.y > rect2->vertex.leftTop.y)
        return false;

    // 矩形が重なっている
    return true;

}

