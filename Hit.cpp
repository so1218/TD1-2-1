#include "Structures.h"
#include "Calculate.h"

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

void ApplyKnockback(Knockback* knockback, RectangleObject* rect1, RectangleObject* rect2, Vector2* beDonePos, Vector2* doPos)
{
	if (CheckRectangleRectangleCollision(rect1, rect2))
	{

		knockback->dir = { beDonePos->x - doPos->x, beDonePos->y - doPos->y };

		knockback->normalizedDir = CalculateNormalize(knockback->dir);

		knockback->velocity.x = knockback->normalizedDir.x * knockback->strength;
		knockback->velocity.y = knockback->normalizedDir.y * knockback->strength;

		knockback->isKnockback = true;


	}

	if (knockback->isKnockback)
	{
		knockback->velocity.x *= 0.95f;
		knockback->velocity.y *= 0.95f;
		beDonePos->x += knockback->velocity.x;
		beDonePos->y += knockback->velocity.y;
	}
	if (fabs(knockback->velocity.x) < 0.1f || fabs(knockback->velocity.y) < 0.1f)
	{
		knockback->isKnockback = false;
		knockback->velocity.x = 0.0f;
		knockback->velocity.y = 0.0f;
	}
}

//無敵時間があるノックバック関数
void ApplyKnockbackPlayer(Knockback* knockback, RectangleObject* rect1, RectangleObject* rect2, Vector2* beDonePos, Vector2* doPos, Player* player)
{
	if (CheckRectangleRectangleCollision(rect1, rect2) && !player->knockback.isKnockbacked)
	{

		knockback->dir = { beDonePos->x - doPos->x, beDonePos->y - doPos->y };

		knockback->normalizedDir = CalculateNormalize(knockback->dir);

		knockback->velocity.x = knockback->normalizedDir.x * knockback->strength;
		knockback->velocity.y = knockback->normalizedDir.y * knockback->strength;

		knockback->isKnockback = true;


	}

	if (knockback->isKnockback)
	{
		knockback->velocity.x *= 0.95f;
		knockback->velocity.y *= 0.95f;
		beDonePos->x += knockback->velocity.x;
		beDonePos->y += knockback->velocity.y;
	}
	if (fabs(knockback->velocity.x) < 0.1f || fabs(knockback->velocity.y) < 0.1f)
	{
		knockback->isKnockback = false;
		knockback->velocity.x = 0.0f;
		knockback->velocity.y = 0.0f;
	}
}
