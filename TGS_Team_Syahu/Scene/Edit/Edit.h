#pragma once
#include "stdio.h"
#include "../SceneBase.h"
#include "../../Actor/ObjectBase.h"
#include "../../InputControl/Key/KeyInput.h"
#include "../../Actor/Camera/Camera.h"

class GameMainScene;

#define OBJECT_TYPE_MAX 5

static char objString[OBJECT_TYPE_MAX][256] =
{
    "None",
    "Block",
    "Sword",
    "Dagger",
    "Rapier",
};

enum MODE {
    Normal,
    Range,
};

class Edit : public SceneBase
{
private:
    Camera* camera;

    Vector2D move;

    MODE mode = Normal;

    int mouseX, mouseY;
    int blockX, blockY;
    int rSelectX, rSelectY;
    bool rangeflg;
    int stageWidth, stageHeight;
    int stageNum;
    int stageData[100][100];
    int stageOldData[100][100];

    int toolSelect;

    bool success;
    int resultDisplay;

    bool cameraflg = true;

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

