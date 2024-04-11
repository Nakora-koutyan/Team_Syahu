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

    //描画に関すること以外の更新を実装する
    SceneBase* Update()override;

    //描画に関することを
    void Draw()const override;
};
