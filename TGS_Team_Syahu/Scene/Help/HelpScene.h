#pragma once
#include "../SceneBase.h"
#include "../../Utility/common.h"

enum Manual
{
	Operation,
	Enemy,
	PlayerOperation,
	PlayerWeapon
};
struct AllowDirection
{
	
};

class HelpScene :public SceneBase
{
private:
	//テキスト：「Monsters」
	int enemyTextImage;
	//テキスト：「Operation」
	int operationTextImage;
	//テキスト：「Player」
	int playerTextImage;
	
	//現在の説明対象を示すテキスト
	int nowManualText;
	//現在の説明書画像
	int nowManualImage;

	//敵の説明書画像
	int enemyManualImage;
	//操作方法の説明書画像
	int operationManualImage;
	//プレイヤーの2段ジャンプに関する説明書画像
	int playerOperationManualImage;
	//プレイヤーの武器に関する説明書画像
	int playerWeaponManualImage;

	//メニュー番号
	int menuNum;

	//ボタンガイド画像01
	int buttonGuideImage01;
	//ボタンガイド画像02
	int buttonGuideImage02;
	//現在のボタンガイドの画像状態
	int nowButton;
	//画像切り替えのインターバル
	int buttonMoveInterval;
	//ボタン画像の切り替えフラグ
	bool buttonImageFlg;

	//ボタンの切り替えフラグ
	bool buttonControlFlg;

	//「Back」の表示
	int backToHelp;

	//ヘルプ画面の最初の画面を格納する画像
	int helpScreen;

	int allowImage01;
	int allowImage02;
	int leftNowAllowImage;
	int rightNowAllowImage;

	//カーソルのインターバル
	int cursorInterval;

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
	
	//カーソルコントロールに関する処理
	void ButtonControl();

	//ボタンガイドに関する処理
	void ButtonGuide();

	void AllowControl();
};

