#pragma once
#include "../SceneBase.h"
#include "../../Utility/common.h"

enum Manual
{
	Enemy,
	Operation,
	None
};

class HelpScene :public SceneBase
{
private:
	//テキスト：「HELP」
	int helpTextImage;
	//テキスト：「Enemy」
	int enemyTextImage;
	//テキスト：「Operation」
	int operationTextImage;
	//テキスト：「Close」
	int closeTextImage;

	//敵の説明書画像
	int enemyManualImage;
	//操作方法の説明書画像
	int operationManualImage;
	//現在の説明書画像
	int nowManualImage;


	//カーソル表示
	int cursorImage;
	
	//カーソルの座標
	float cursorLocX;
	float cursorLocY;

	//メニュー番号
	int menuNum;
	//ヘルプ画面の現在の画面を格納する画像
	int nowHelpScene;

	//説明書の種類
	Manual manualType;

public:
	//コンストラクタ
	HelpScene();

	//デストラクタ
	~HelpScene();

	//初期化関数
	void Initialize()override;

	//終了時関数
	void Finalize()override;

	//描画以外の更新
	SceneBase* Update()override;

	//描画に関する更新
	void Draw()const override;

private:
	void CursolControl();

	void EnemyManual();

	void OperationManual();

};

