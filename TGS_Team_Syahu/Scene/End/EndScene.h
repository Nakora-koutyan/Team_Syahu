#pragma once
#include "../SceneBase.h"

#define SCENE_INTERVAL  120          //シーン切り替えを行うインターバル

class EndScene :public SceneBase
{
private:
    int intervalCount;                  //インターバル

public:
    //コンストラクタ
    EndScene();

    //デストラクタ
    ~EndScene();

    //初期化処理
    void Initialize()override;

    //終了処理
    void Finalize()override;

    //更新
    SceneBase* Update()override;

    //描画
    void Draw()const override;

};

