#pragma once
#include "stdio.h"
#include "../SceneBase.h"
#include "../../Actor/ObjectBase.h"
#include "../../InputControl/Key/KeyInput.h"
#include "../../Actor/Camera/Camera.h"

class GameMainScene;

#define OBJECT_TYPE_MAX 4+15

static char objString[20][256] =
{
    "None",
    "Sword",
    "Rapier",
    "Dagger",
};

enum MODE {
    Normal,
    Range,
};

class Edit : public SceneBase
{
private:
    Vector2D move;

    MODE mode = Normal;

    int mouseX, mouseY;
    int blockX, blockY;
    int rSelectX, rSelectY;
    bool rangeflg;
    const int color[4]{ 0xDDDDDD,0x8524F4,0xAF2F3E,0x49FFF3, };
    int stageWidth, stageHeight;
    int stageNum;
    int stageData[100][100];
    int stageOldData[100][100];

    int toolSelect;

    int blockImg[16];
    
    bool success;
    int resultDisplay;

    bool cameraflg = true;

    void LoadStage(int Stage);

    void SaveStage();

    void ObjectExchange(int watch, int target, int exchange);

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

