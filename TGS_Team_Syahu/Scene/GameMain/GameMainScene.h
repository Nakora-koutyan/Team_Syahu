#pragma once
#include"../SceneBase.h"
#include"../../Actor/ObjectBase.h" 
#include"../../UI/UI.h"
#include"vector"

#define LINE_NUM 12                     //ラインの数

class GameMainScene :public SceneBase
{
private:
    std::vector<ObjectBase*>object;     //オブジェクト

    UI* ui;                             //UIのオブジェクト

    int kari;                           //かり

    bool debugModeFlg;                  //デバッグ状態にする？ 

public:
    //コンストラクタ
    GameMainScene();

    //デストラクタ
    ~GameMainScene();

    //初期化処理
    void Initialize()override;

    //終了処理
    void Finalize()override;

    //更新
    SceneBase* Update()override;

    //描画
    void Draw()const override;

private:
    //ヒットチェック
    void HitCheck();

    //プレイヤーの武器のヒットチェック
    void HitCheckPlayerWeapon(const int i, const int j);

    //エネミーの武器のヒットチェック
    void HitCheckEnemyWeapon(const int i, const int j);

    //ステージ生成
    void createStage();

};
