#pragma once
#include"../SceneBase.h"
#include"../Utility/Vector2D.h"

class GameOverScene :public SceneBase
{
private:
    Vector2D cursorLocation;            //カーソルの座標

    int intervaSceneCount;              //シーンインターバル
    int intervalCursorCount;            //カーソルインターバル
    int cursorNum;                      //カーソルの番号                    

public:
    //コンストラクタ
    GameOverScene();

    //デストラクタ
    ~GameOverScene();

    //初期化処理
    void Initialize()override;

    //終了処理
    void Finalize()override;

    //更新
    SceneBase* Update()override;

    //描画
    void Draw()const override;
};

