#pragma once
#include "../Scene/SceneBase.h"
#include"../Utility/common.h"

class SceneManager
{
private:
    SceneBase* now_sceen;       //現在のシーン

    bool initFlg;               //初期化した？

public:
    //コンストラクタ
    SceneManager() :now_sceen(nullptr), initFlg(false) {};

    //デストラクタ
    ~SceneManager() { delete now_sceen; }

    //更新
    void Update();

    //描画
    void Draw()const;

    //初期化処理
    void Initialize();

    //終了処理
    void Finalize();

};
