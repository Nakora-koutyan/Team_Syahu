#include "HelpScene.h"
#include"../../InputControl/Key/KeyInput.h"
#include"../../InputControl/Pad/PadInput.h"
#include "../GameMain/GameMainScene.h"
#include "../Title/TitleScene.h"
#include "../../ResourceManager/ResourceManager.h"

//コンストラクタ
HelpScene::HelpScene() :enemyTextImage(NULL), operationTextImage(NULL), nowManualText(NULL), 
menuNum(0), manualType{},helpScreen(NULL), enemyManualImage(NULL), operationManualImage(NULL), 
nowManualImage(NULL),buttonGuideImage01(NULL),buttonGuideImage02(NULL),nowButton(NULL),
buttonMoveInterval(0),buttonImageFlg(false),backToHelp(NULL),allowImage01(NULL),allowImage02(NULL),
leftNowAllowImage(NULL),rightNowAllowImage(NULL)
{
}

//デストラクタ
HelpScene::~HelpScene()
{
}

//初期化関数
void HelpScene::Initialize()
{
	//テキスト画像
	enemyTextImage = LoadGraph("Resource/Images/Help/EnemyText.png");
	operationTextImage = LoadGraph("Resource/Images/Help/OperationText.png");

	//説明画像
	enemyManualImage = LoadGraph("Resource/Images/Help/EnemyManual.png");
	operationManualImage = LoadGraph("Resource/Images/Help/OperationManual.png");

	//ボタン画像
	buttonGuideImage01 = LoadGraph("Resource/Images/Help/ButtonGuide01.png");
	buttonGuideImage02 = LoadGraph("Resource/Images/Help/ButtonGuide02.png");

	//「戻る」画像
	backToHelp = LoadGraph("Resource/Images/Help/BackToHelp.png");

	//矢印画像
	allowImage01 = LoadGraph("Resource/Images/Help/Allow01.png");
	allowImage02 = LoadGraph("Resource/Images/Help/Allow02.png");

	manualType = Manual::Operation;
	helpScreen = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
	nowManualText = operationTextImage;
	nowManualImage = operationManualImage;
	leftNowAllowImage = allowImage02;
	rightNowAllowImage = allowImage01;
}

void HelpScene::Finalize()
{
}

//描画以外の更新
SceneBase* HelpScene::Update()
{
	ButtonControl();
	switch (menuNum)
	{
	case 0:
		if (PadInput::OnButton(XINPUT_BUTTON_A) || KeyInput::GetKey(KEY_INPUT_SPACE))
		{
			manualType = Manual::Operation;
			//表示する説明書画像を操作方法の説明書画像にする
			nowManualImage = operationManualImage;
			nowManualText = operationTextImage;
			break;
		}

	case 1:
		if (PadInput::OnButton(XINPUT_BUTTON_A) || KeyInput::GetKey(KEY_INPUT_SPACE))
		{
			manualType = Manual::Enemy;
			//表示する説明書画像を敵の説明書画像にする
			nowManualImage = enemyManualImage;
			nowManualText = enemyTextImage;
		}
		break;
	}
	//ボタンガイドの表示と画像の繰り返し
	ButtonGuide();
	//矢印画像の制御
	AllowControl();

	//ゲームメインシーンに戻る
	if (KeyInput::GetKey(KEY_INPUT_B)|| PadInput::OnButton(XINPUT_BUTTON_B))
	{
		//ゲームメインシーンに遷移
		return new TitleScene();
	}

	//この画面を維持
	return this;
}

//描画に関する更新
void HelpScene::Draw() const
{
	//仮背景の表示
	DrawGraphF(0.f, 0.f, ResourceManager::GetImage("Stage/Background/layer_1"), TRUE);
	DrawGraphF(0.f, 200.f, ResourceManager::GetImage("Stage/Background/layer_2"), TRUE);
	//現在の画面を一枚のデータとして保存
	GetDrawScreenGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, helpScreen);
	//画面を初期化
	ClearDrawScreen();
	//保存した画像に「ぼかし」を加える
	GraphFilter(helpScreen, DX_GRAPH_FILTER_GAUSS, 16, 1200);
	//「ぼかし」を加えた画像を現在のシーンとして描画する
	DrawGraphF(0.f, 0.f, helpScreen, TRUE);

	//現在の説明対象の表示
	DrawGraphF(450.f, 30.f, nowManualText, TRUE);

	//矢印画像の表示
	DrawRotaGraphF(50.f,60.f , 1, 0, leftNowAllowImage,TRUE,TRUE,FALSE);
	DrawRotaGraphF(1220, 60.f, 1, 0, rightNowAllowImage, TRUE, FALSE, FALSE);

	//現在の説明書画像を表示
	DrawGraphF(90.f, 110.f, nowManualImage, TRUE);

	//現在のボタン画像を表示
	DrawGraph(500, 670, nowButton, TRUE);
	DrawGraph(555, 670, backToHelp, TRUE);
}

void HelpScene::ButtonControl()
{
	//カーソルの右移動
	if ((KeyInput::GetKey(KEY_INPUT_D) || KeyInput::GetKey(KEY_INPUT_RIGHT) ||
		PadInput::GetLStickRationX() > 0.2 || PadInput::OnButton(XINPUT_BUTTON_DPAD_RIGHT)))
	{
		menuNum++;
		if (menuNum >= 2)
		{
			menuNum = 0;
		}
	}
	//カーソルの左移動
	else if ((KeyInput::GetKey(KEY_INPUT_A) || KeyInput::GetKey(KEY_INPUT_LEFT) ||
		PadInput::GetLStickRationX() < -0.2 || PadInput::OnButton(XINPUT_BUTTON_DPAD_LEFT)))
	{
		menuNum--;
		if (menuNum <= -1)
		{
			menuNum = 1;
		}
	}
}
//ボタンガイドの画像番号の制御
void HelpScene::ButtonGuide()
{
	buttonMoveInterval++;
	//3フレーム毎に画像を切り替える
	if (buttonMoveInterval % 30 == 0)
	{
		buttonImageFlg = !buttonImageFlg;
	}

	//画像切り替え
	if (buttonImageFlg)
	{
		nowButton = buttonGuideImage01;
	}
	else if (buttonGuideImage02)
	{
		nowButton = buttonGuideImage02;
	}
}
//矢印の制御
void HelpScene::AllowControl()
{
	if (menuNum == 0)
	{
		leftNowAllowImage = allowImage02;
		rightNowAllowImage = allowImage01;
	}
	else if (menuNum != 0)
	{
		leftNowAllowImage = allowImage01;
		rightNowAllowImage = allowImage02;
	}
}
