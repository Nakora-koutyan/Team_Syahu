#pragma once
#include "../SceneBase.h"
#include"../../Actor/Player/Player.h"
#include"../../Actor/Camera/Camera.h"

#define LINE_NUM 12                     // ラインの数

class GameMainScene :public SceneBase
{
private:
    Player* player;         //プレイヤーのオブジェクト
    Camera* camera;         //カメラのオブジェクト

public:
    //コンストラクタ
    GameMainScene();

    //デストラクタ
    ~GameMainScene();

    //描画に関すること以外の更新を実装する
    SceneBase* Update()override;

    //描画に関することの更新を実装する
    void Draw()const override;

private:
    //デバッグステージの描画
    void DebugStage()const;

public:
    //プレイヤーオブジェクトの取得
    Player* GetPlayer()const { return player; }

    //カメラオブジェクトの取得
    Camera* GetCamera()const { return camera; }

};
