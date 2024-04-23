#pragma once
#include "../SceneBase.h"
#include"../../Actor/Player/Player.h"
#include"../../Actor/Camera/Camera.h"
#include"../../Actor/Enemy/NormalEnemy.h"
#include"../../Map/StageBlock.h"

#define LINE_NUM 12                     //ラインの数

class GameMainScene :public SceneBase
{
private:
    Player* player;                     //プレイヤーのオブジェクト
    Camera* camera;                     //カメラのオブジェクト
    NormalEnemy* enemy;                 //雑魚敵のオブジェクト
    StageBlock* stageblock;

    int kari;                           //かり

    bool debugModeFlg;                  //デバッグ状態にする？ 

public:
    //コンストラクタ
    GameMainScene();

    //デストラクタ
    ~GameMainScene();

    //更新
    SceneBase* Update()override;

    //描画
    void Draw()const override;

public:
    //プレイヤーオブジェクトの取得
    Player* GetPlayer()const { return player; }

    //カメラオブジェクトの取得
    Camera* GetCamera()const { return camera; }

    //雑魚敵オブジェクトの取得
    NormalEnemy* GetNormalEnemy()const { return enemy; }

private:
    //ヒットチェック
    void HitCheck();

};
