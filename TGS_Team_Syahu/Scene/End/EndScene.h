#pragma once
#include "../SceneBase.h"

class EndScene :public SceneBase
{
private:
    int intervaSceneCount;                  //インターバル

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

