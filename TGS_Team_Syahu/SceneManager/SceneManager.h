#pragma once
#include "../Scene/SceneBase.h"

class SceenManager :public SceneBase
{
private:
    //現在のシーン
    SceneBase* now_sceen;
public:
    //コンストラクタ
    SceenManager(SceneBase* scene) :now_sceen(scene) {};

    //デストラクタ
    ~SceenManager() { delete now_sceen; }

    //更新
    SceneBase* Update()override;

    //描画
    void Draw()const override;
};
