#pragma once
#include "../SceneBase.h"
#include"../../Actor/Character/Player/Player.h"
#include"../../Actor/Camera/Camera.h"
#include"../../Actor/Character/Enemy/NormalEnemy.h"
#include"../../Actor/Character//Enemy/LargeSwordEnemy.h"
#include"../../Map/StageBlock.h"
#include"../../UI/UI.h"

#define LINE_NUM 12                     //ラインの数

class GameMainScene :public SceneBase
{
private:
    Player* player;                     //プレイヤーのオブジェクト
    Camera* camera;                     //カメラのオブジェクト
    NormalEnemy* enemy;                 //雑魚敵のオブジェクト
    LargeSwordEnemy* enemy1;            //敵(大剣)のオブジェクト
    StageBlock* stageblock;
    UI* ui;                             //UIのオブジェクト

    int kari;                           //かり

    bool debugModeFlg;                  //デバッグ状態にする？ 

public:
    //コンストラクタ
    GameMainScene();

    //デストラクタ
    ~GameMainScene();

    //初期化処理
    void Initialize()override;

    //終了処理
    void Finalize()override;

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
