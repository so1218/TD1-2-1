#include "Structures.h"
#include "Rectangle.h"
#include "Calculate.h"
#include "Particle.h"

// ボスの行動パターン

//弾をいくつかの方向に発射する関数
void FireSomewayDirectionBullet(Bullet* bullet, Vector2 startPos)
{
    

    bullet->isAction = false;

   
    for (int i = 0; i < bullet->amount; ++i)
    {
        if (!bullet[i].hasAction)
        {
            if (!bullet[i].isExist)
            {
                bullet[i].pos = startPos;
                bullet->angleStep = 2.0f / bullet->directionCount;
                bullet[i].angle = bullet->angleStep * i;
                bullet[i].velocity.x = bullet->speed * cosf(bullet[i].angle * float(M_PI));
                bullet[i].velocity.y = bullet->speed * sinf(bullet[i].angle * float(M_PI));

                bullet[i].hasAction = true;
                bullet[i].isExist = true;

                break;
            }
        }
    }
    
       
   

    for (int i = 0; i < bullet->amount; ++i)
    {
        if (bullet[i].isExist)
        {
            bullet->isAction = true;

            bullet[i].pos.x += bullet[i].velocity.x;
            bullet[i].pos.y += bullet[i].velocity.y;
        }

        if (bullet[i].pos.x > kWindowWidth || bullet[i].pos.x < 0
            || bullet[i].pos.y > kWindowHeight || bullet[i].pos.y < 0)
        {
            bullet[i].isExist = false;
            
        }

        CalcVertexRectangle(&bullet[i]);
        ConvertWorldToScreenRectangle(&bullet[i]);
    }

}

void DrawSomewayDirectionBullet(Bullet* bullet)
{
    for (int i = 0; i < bullet->amount; i++)
    {
        if (bullet[i].isExist)
        {
            Novice::DrawQuad(
                static_cast<int>(bullet[i].screenVertex.leftTop.x),
                static_cast<int>(bullet[i].screenVertex.leftTop.y),
                static_cast<int>(bullet[i].screenVertex.rightTop.x),
                static_cast<int>(bullet[i].screenVertex.rightTop.y),
                static_cast<int>(bullet[i].screenVertex.lehtBottom.x),
                static_cast<int>(bullet[i].screenVertex.lehtBottom.y),
                static_cast<int>(bullet[i].screenVertex.rightBottom.x),
                static_cast<int>(bullet[i].screenVertex.rightBottom.y),
                0, 0, 0, 0, 0, bullet[i].color);
        }
    };

    Novice::ScreenPrintf(40, 100, "%d", bullet->frameCount);
}

void InitSomewayDirectionBullet(Bullet* bullet)
{
    bullet->speed = 5.0f;
    for (int i = 0; i < bullet->amount; ++i)
    {

        bullet[i].width = 10;
        bullet[i].height = 10;

        bullet[i].isExist = false;
        bullet[i].hasAction = false;

    }
}

//弾をプレイヤーに向かって撃つ関数
void FireToSomethingBullet(Bullet* bullet, Vector2* start, Vector2* end)
{
    if (bullet->frameCount <= 0)
    {
        bullet->frameCount = bullet->appearInterval;
    }

    bullet->isAction = false;

    if (bullet->frameCount == bullet->appearInterval)
    {
        for (int i = 0; i < bullet->amount; ++i)
        {
            if (!bullet[i].hasAction)
            {
                if (!bullet[i].isExist)
                {
                    // startからendへの方向ベクトルを計算
                    bullet[i].directionVec = { end->x - start->x, end->y - start->y };

                    // 方向ベクトルを正規化して弾の速度にする
                    bullet[i].normalizedDirection = CalculateNormalize(bullet[i].directionVec);

                    // 弾の速度
                    bullet->speed = 5.0f;

                    bullet[i].isExist = true;

                    bullet[i].pos = *start;

                    bullet[i].hasAction = true;

                   

                    break;
                }
            }
        }
    }

    bullet->frameCount -= 1;

    for (int i = 0; i < bullet->amount; ++i)
    {
        if (bullet[i].isExist)
        {
            bullet->isAction = true;

            // 弾の進行方向に基づいて弾の新しい位置を計算
            bullet[i].pos.x += bullet[i].normalizedDirection.x * bullet->speed;
            bullet[i].pos.y += bullet[i].normalizedDirection.y * bullet->speed;
        }

        if (bullet[i].pos.x > kWindowWidth || bullet[i].pos.x < 0
            || bullet[i].pos.y>kWindowHeight || bullet[i].pos.y < 0)
        {
            bullet[i].isExist = false;
            
        }

        

        CalcVertexRectangle(&bullet[i]);
        ConvertWorldToScreenRectangle(&bullet[i]);

    }
}

void DrawToSomethingBullet(Bullet* bullet)
{
    for (int i = 0; i < bullet->amount; i++)
    {
        if (bullet[i].isExist)
        {
            Novice::DrawQuad(
                static_cast<int>(bullet[i].screenVertex.leftTop.x),
                static_cast<int>(bullet[i].screenVertex.leftTop.y),
                static_cast<int>(bullet[i].screenVertex.rightTop.x),
                static_cast<int>(bullet[i].screenVertex.rightTop.y),
                static_cast<int>(bullet[i].screenVertex.lehtBottom.x),
                static_cast<int>(bullet[i].screenVertex.lehtBottom.y),
                static_cast<int>(bullet[i].screenVertex.rightBottom.x),
                static_cast<int>(bullet[i].screenVertex.rightBottom.y),
                0, 0, 0, 0, 0, 0x00ff00ff);

           
        }
    };

}

void InitToSomethingBullet(Bullet* bullet)
{
    bullet->speed = 5.0f;
    for (int i = 0; i < bullet->amount; ++i)
    {
        

        bullet[i].width = 10;
        bullet[i].height = 10;

        bullet[i].isExist = false;
        bullet[i].hasAction = false;

    }
}

