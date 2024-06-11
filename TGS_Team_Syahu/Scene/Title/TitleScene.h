#pragma once
#include"../SceneBase.h"
#include"../Utility/Vector2D.h" 

#define CURSOR_INTERVAL		15		//カーソルのインターバル

class TitleScene :public SceneBase
{
private:
    Vector2D cursorLocation;            //カーソルの座標

    int intervalCount;                  //インターバル
    int cursorNum;                      //カーソルの番号                    

public:
    //コンストラクタ
    TitleScene();

    //デストラクタ
    ~TitleScene();

    //初期化処理
    void Initialize()override;

    //終了処理
    void Finalize()override;

    //更新
    SceneBase* Update()override;

    //描画
    void Draw()const override;

};

