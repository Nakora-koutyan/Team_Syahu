#pragma once
#include "stdio.h"
#include "../SceneBase.h"
#include "../../Actor/ObjectBase.h"
#include "../../InputControl/Key/KeyInput.h"

class GameMainScene;

class Edit : public SceneBase
{
private:

    GameMainScene* GameMain;
    KeyInput* keyInput;

    int mouseX, mouseY;
    int blockX, blockY;
    int stageWidth, stageHeight;
    int stageNum;
    int stageData[100][100];
    int stageOldData[100][100];

    int toolSelect;

    bool success;
    int resultDisplay;

    void LoadStage(int Stage);

    void SaveStage();


public:
    //コンストラクタ
    Edit();

    //デストラクタ
    ~Edit();

    //初期化処理
    void Initialize()override;

    //終了処理
    void Finalize()override;

    //更新
    SceneBase* Update()override;

    //描画
    void Draw()const override;
};
