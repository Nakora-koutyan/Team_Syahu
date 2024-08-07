#pragma once
#include "../SceneBase.h"

class GameClearScene :public SceneBase
{
private:
    int intervaSceneCount;              //シーンインターバル
    int animCount;                      //アニメーションカウント
    int playerIdle;                     //プレイヤーのアイドル番号

public:
    //コンストラクタ
    GameClearScene();

    //デストラクタ
    ~GameClearScene();

    //初期化処理
    void Initialize()override;

    //終了処理
    void Finalize()override;

    //更新
    SceneBase* Update()override;

    //描画
    void Draw()const override;

};

