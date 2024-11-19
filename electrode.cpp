#include "Calculate.h"
#include "Easing.h"
#include "Rectangle.h"
#include "Structures.h"

IntVector2 ConvertScreenToWorld(const IntVector2& screenPos)
{

    IntVector2 worldMousePos;

    worldMousePos.x = screenPos.x;

    worldMousePos.y = screenPos.y - kWindowHeight;
    worldMousePos.y *= -1;

    return worldMousePos;
}

//==============================
// 初期化
//==============================

// 電極初期化
#pragma region 電極初期化

const int kMaxElectrode = 3;

void InitElectrode(Electrode* electrode, Player* player)
{

    // 電極の初期化
    for (int i = 0; i < kMaxElectrode; i++) {
        electrode[i].pos.x = 0.0f;
        electrode[i].pos.y = 0.0f;

        electrode[i].startPos = { 0.0f };

        electrode[i].goalPos = { 0.0f };

        electrode[i].velocity.x = 0.0f;
        electrode[i].velocity.y = 0.0f;

        electrode->speed = 12.0f;

        electrode[i].dir.x = 0.0f;
        electrode[i].dir.y = 0.0f;

        electrode[i].length = 0.0f;

        electrode[i].width = 15.0f;
        electrode[i].height = 25.0f;

        electrode[i].isActive = false;

        electrode[i].isWallStick = false;

        electrode[i].isGlobalEasingActive = false;

        /* electrode[i].isObjectHit = false;
         electrode[i].isRemainingNumber = 3;*/

        electrode[i].radius = 16.0f;
    }

    // 自機の初期化
    player->pos.x = 0.0f;
    player->pos.y = 0.0f;

    electrode->globalEasedT = 0.0f;
}

#pragma endregion

// マーカー初期化
#pragma region マーカー初期化

const int kMaxMaker = 1;

void InitMaker(Player* player)
{

    player->maker.pos = { player->pos.x, player->pos.y };
    player->maker.velocity = { 0.0f, 0.0f };

    player->maker.speed = 10.0f;

    player->maker.width = 20.0f;
    player->maker.height = 40.0f;

    player->maker.length = 0.0f;

    player->maker.isActive = false;
}

#pragma endregion

//==============================
// 更新処理
//==============================

void MoveElectrode(Electrode* electrode, Player* player, GameManager* gm)
{
    //==============================
    // ↓↓↓自機弾発射処理↓↓↓
    //==============================

#pragma region 自機弾発射

    // マウス座標の取得と座標変換
    IntVector2 screenMousePos;
    IntVector2 worldMousePos;

    Novice::GetMousePosition(&screenMousePos.x, &screenMousePos.y);

    worldMousePos = ConvertScreenToWorld(screenMousePos);

    for (int i = 0; i < kMaxElectrode; i++) {

        // スペースを押したときアクティブ状態なら自機の位置から発射
        if (Novice::IsTriggerMouse(0)) {
            if (!electrode[i].isActive) {

                // 自機から発射
                electrode[i].pos.x = player->pos.x;
                electrode[i].pos.y = player->pos.y;

                // 方向ベクトルを計算
                electrode[i].dir.x = worldMousePos.x - player->pos.x;
                electrode[i].dir.y = worldMousePos.y - player->pos.y;

                electrode[i].length = sqrtf(powf(electrode[i].dir.x, 2) + powf(electrode[i].dir.y, 2));

                // 正規化
                if (electrode[i].length != 0.0f) {
                    electrode[i].dir.x /= electrode[i].length;
                    electrode[i].dir.y /= electrode[i].length;
                }

                // 正規化した値にスピードを掛ける
                electrode[i].velocity.x = electrode[i].dir.x * electrode->speed;
                electrode[i].velocity.y = electrode[i].dir.y * electrode->speed;

                // アクティブにする
                electrode[i].isActive = true;

                break;
            }
        }
    }

    // 弾発射
    for (int i = 0; i < kMaxElectrode; i++) {
        if (electrode[i].isActive) {

            // 速度を加算
            electrode[i].pos.x += electrode[i].velocity.x;
            electrode[i].pos.y += electrode[i].velocity.y;

            // 壁にくっつける処理
            if (electrode[i].pos.x <= 0.0f || electrode[i].pos.x >= 1280.0f) {

                electrode[i].velocity.x = 0.0f;
                electrode[i].velocity.y = 0.0f;
            }
            if (electrode[i].pos.y <= 0.0f || electrode[i].pos.y >= 720.0f) {

                electrode[i].velocity.x = 0.0f;
                electrode[i].velocity.y = 0.0f;
            }
        }

        // 座標変換
        CalcVertexRectangle(&electrode[i]);
        ConvertWorldToScreenRectangle(&electrode[i]);
    }

#pragma endregion

    //==============================
    // ↑↑↑電極発射処理↑↑↑
    //==============================

    //==============================
    // ↓↓↓自機弾のマーカー引き寄せ処理↓↓↓
    //==============================

#pragma region マーカー引き寄せ処理

    if (gm->keys[DIK_R] && !gm->preKeys[DIK_R]) {
        // 引き寄せ開始
        electrode->isGlobalEasingActive = true;
        electrode->globalEasedT = 0.0f; // 線形補間の進行度リセット

        // 各電極の開始位置とゴール位置を設定
        for (int i = 0; i < kMaxElectrode; i++) {
            if (electrode[i].isWallStick) {
                electrode[i].startPos = electrode[i].pos; // 開始位置を記録
                electrode[i].goalPos = player->maker.pos;
                electrode[i].isWallStick = false; // 壁から離れる
            }
        }
    }

    // 線形補間処理
    if (electrode->isGlobalEasingActive) {
        electrode->globalEasedT += 0.01f; // 進行速度を調整
        if (electrode->globalEasedT >= 1.0f) {
            electrode->globalEasedT = 1.0f; // 補間終了
            electrode->isGlobalEasingActive = false;
        }

        // 全ての電極を補間
        for (int i = 0; i < kMaxElectrode; i++) {
            if (!electrode[i].isWallStick) {
                // 線形補間による位置計算
                electrode[i].pos.x = (1.0f - electrode->globalEasedT) * electrode[i].startPos.x + electrode->globalEasedT * electrode[i].goalPos.x;
                electrode[i].pos.y = (1.0f - electrode->globalEasedT) * electrode[i].startPos.y + electrode->globalEasedT * electrode[i].goalPos.y;
            }
        }
    }

#pragma endregion

    //==============================
    // ↑↑↑自機弾のマーカー引き寄せ処理↑↑↑
    //==============================
}

//==============================
// マーカー設置処理
//==============================

#pragma region マーカー処理

void MoveMaker(Player* player)
{

    // マウス座標の取得と座標変換
    IntVector2 screenMousePos;
    IntVector2 worldMousePos;

    Novice::GetMousePosition(&screenMousePos.x, &screenMousePos.y);

    worldMousePos = ConvertScreenToWorld(screenMousePos);

    // マーカー発射処理

    // 右クリック時
    if (Novice::IsTriggerMouse(1)) {
        // アクティブ状態じゃないなら
        if (!player->maker.isActive) {

            // 自機から発射
            player->maker.pos.x = player->pos.x;
            player->maker.pos.y = player->pos.y;

            // 方向ベクトルの計算
            player->maker.dir.x = worldMousePos.x - player->pos.x;
            player->maker.dir.y = worldMousePos.y - player->pos.y;

            player->maker.length = sqrtf(powf(player->maker.dir.x, 2) + powf(player->maker.dir.y, 2));

            // 正規化
            if (player->maker.length != 0.0f) {
                player->maker.dir.x /= player->maker.length;
                player->maker.dir.y /= player->maker.length;
            }

            // 正規化したベクトルに速度を加算
            player->maker.velocity.x = player->maker.dir.x * player->maker.speed;
            player->maker.velocity.y = player->maker.dir.y * player->maker.speed;

            // アクティブにする
            player->maker.isActive = true;
        }
    }

    // マーカー発射処理
    if (player->maker.isActive) {

        player->maker.pos.x += player->maker.velocity.x;
        player->maker.pos.y += player->maker.velocity.y;

        if (player->maker.pos.x <= 0.0f || player->maker.pos.x >= 1280.0f) {
            player->maker.velocity.x = 0.0f;
            player->maker.velocity.y = 0.0f;
        }

        if (player->maker.pos.y <= 0.0f || player->maker.pos.y >= 720.0f) {
            player->maker.velocity.x = 0.0f;
            player->maker.velocity.y = 0.0f;
        }
    }

    // 座標変換
    CalcVertexRectangle(&player->maker);
    ConvertWorldToScreenRectangle(&player->maker);
}

#pragma endregion

//==============================
// 描画処理
//==============================

void DrawElectrode(Electrode* electrode)
{

    // 弾の描画
    for (int i = 0; i < kMaxElectrode; i++) {
        if (electrode[i].isActive) {

            Novice::DrawQuad(
                static_cast<int>(electrode[i].screenVertex.leftTop.x),
                static_cast<int>(electrode[i].screenVertex.leftTop.y),
                static_cast<int>(electrode[i].screenVertex.rightTop.x),
                static_cast<int>(electrode[i].screenVertex.rightTop.y),
                static_cast<int>(electrode[i].screenVertex.lehtBottom.x),
                static_cast<int>(electrode[i].screenVertex.lehtBottom.y),
                static_cast<int>(electrode[i].screenVertex.rightBottom.x),
                static_cast<int>(electrode[i].screenVertex.rightBottom.y),
                0, 0, 0, 0, 0, RED);
        }

        Novice::ScreenPrintf(32, 64, "startPos: %.1f, %.1f", electrode[i].startPos.x, electrode[i].startPos.y);
        Novice::ScreenPrintf(32, 96, "goalPos: %.1f, %.1f", electrode[i].goalPos.x, electrode[i].goalPos.y);
        Novice::ScreenPrintf(32, 128, "currentPos: %.1f, %.1f", electrode[i].pos.x, electrode[i].pos.y);
    }
}
// マーカー描画
void DrawMaker(Player* player)
{

    if (player->maker.isActive) {

        Novice::DrawQuad(static_cast<int>(player->maker.screenVertex.leftTop.x),
            static_cast<int>(player->maker.screenVertex.leftTop.y),
            static_cast<int>(player->maker.screenVertex.rightTop.x),
            static_cast<int>(player->maker.screenVertex.rightTop.y),
            static_cast<int>(player->maker.screenVertex.lehtBottom.x),
            static_cast<int>(player->maker.screenVertex.lehtBottom.y),
            static_cast<int>(player->maker.screenVertex.rightBottom.x),
            static_cast<int>(player->maker.screenVertex.rightBottom.y),
            0, 0, 0, 0, 0, BLUE);
    }
}
