#include "HelpScene.h"
#include"../../InputControl/Key/KeyInput.h"
#include"../../InputControl/Pad/PadInput.h"
#include "../GameMain/GameMainScene.h"
#include "../Title/TitleScene.h"

//コンストラクタ
HelpScene::HelpScene() :helpTextImage(NULL), enemyTextImage(NULL), operationTextImage(NULL),
closeTextImage(NULL), cursorImage(NULL), cursorLocX(0), cursorLocY(0), menuNum(0), manualType{},
nowHelpScene(NULL), enemyManualImage(NULL), operationManualImage(NULL), nowManualImage(NULL)
{
}

//デストラクタ
HelpScene::~HelpScene()
{
}

//初期化関数
void HelpScene::Initialize()
{
	helpTextImage = LoadGraph("Resource/Images/Help/HelpText.png");
	enemyTextImage = LoadGraph("Resource/Images/Help/EnemyText.png");
	operationTextImage = LoadGraph("Resource/Images/Help/OperationText.png");
	closeTextImage = LoadGraph("Resource/Images/Help/CloseText.png");

	enemyManualImage = LoadGraph("Resource/Images/Help/ManualScreen.png");
	operationManualImage = LoadGraph("Resource/Images/Help/ManualScreen02.png");

	cursorImage = LoadGraph("Resource/Images/UI/cursor.png");

	manualType = Manual::None;
}

void HelpScene::Finalize()
{
}

//描画以外の更新
SceneBase* HelpScene::Update()
{
	CursolControl();
	if(PadInput::OnButton(XINPUT_BUTTON_A) || KeyInput::GetKey(KEY_INPUT_SPACE))
	{
		switch (menuNum)
		{
		case 0:
			nowHelpScene = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, TRUE);
			manualType = Manual::Enemy;
			EnemyManual();
			break;

		case 1:
			nowHelpScene = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT, TRUE);
			manualType = Manual::Operation;
			break;

		case 2:
			return new TitleScene();
			break;
		}
	}
	if (manualType != Manual::None)
	{
		GraphFilter(nowHelpScene, DX_GRAPH_FILTER_MONO, -60, 7);
	}

	//ゲームメインシーンに戻る
	if (KeyInput::GetKey(KEY_INPUT_H))
	{
		//ゲームメインシーンに遷移
		return new GameMainScene();
	}

	//この画面を維持
	return this;
}

//描画に関する更新
void HelpScene::Draw() const
{
	//「HELP」の表示
	DrawGraph(415, 90, helpTextImage, TRUE);
	//「Enemy」の表示
	DrawGraph(500, 350, enemyTextImage, TRUE);
	//「Operation」の表示
	DrawGraph(460, 450, operationTextImage, TRUE);
	//「Close」の表示
	DrawGraph(500, 550, closeTextImage, TRUE);

	//カーソルの表示
	DrawRotaGraphF(450.f + cursorLocX, 375.f + cursorLocY, 1, DEGREE_TO_RADIAN(90.f), cursorImage, TRUE);
	//現在説明書がなしの状態でない場合
	if (manualType != Manual::None)
	{
		DrawGraph(0, 0, nowHelpScene, TRUE);
		DrawGraph(90, 60, nowManualImage, TRUE);
	}
}

void HelpScene::CursolControl()
{
	//カーソルの上移動
	if ((KeyInput::GetKeyDown(KEY_INPUT_W) || KeyInput::GetKey(KEY_INPUT_UP) ||
		PadInput::GetLStickRationY() > 0.2 || PadInput::OnButton(XINPUT_BUTTON_DPAD_UP)))
	{
		menuNum--;
		if (menuNum <= -1)
		{
			menuNum = 2;
		}
	}
	//カーソルの下移動
	else if ((KeyInput::GetKeyDown(KEY_INPUT_S) || KeyInput::GetKey(KEY_INPUT_DOWN) ||
		PadInput::GetLStickRationY() < -0.2 || PadInput::OnButton(XINPUT_BUTTON_DPAD_DOWN)))
	{
		menuNum++;
		if (menuNum > 2)
		{
			menuNum = 0;
		}
	}
	//カーソルの動く範囲
	cursorLocX = (menuNum % 3 == 1) ? -50.f : 0;
	cursorLocY = (float)menuNum * 100.f;
}

void HelpScene::EnemyManual()
{
	//表示する説明書画像を敵の説明書画像にする
	nowManualImage = enemyManualImage;
}
