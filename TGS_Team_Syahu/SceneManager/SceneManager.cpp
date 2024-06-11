#include"SceneManager.h"
#include"../Scene/GameMain/GameMainScene.h"
#include"../ResourceManager/ResourceManager.h"
#include"../Scene/Title/TitleScene.h"

void SceneManager::Update()
{
	SceneBase* next_scene;

	double nextTime = GetNowCount();	//システム時間の取得

	ResourceManager::Initialize();

	//ゲームループ
	while ((ProcessMessage() == 0) && !(CheckHitKey(KEY_INPUT_ESCAPE)))
	{			
		if (now_sceen == nullptr)break;

		//画面の初期化
		ClearDrawScreen();

		KeyInput::Update();

		PadInput::Update();

		if (!initFlg)
		{
			initFlg = true;
			now_sceen->Initialize();
		}

		next_scene = now_sceen->Update();

		Draw();

		if (next_scene != now_sceen)
		{
			now_sceen->Finalize();
			delete now_sceen;
			now_sceen = next_scene;
			initFlg = false;
		}

		nextTime += 1.0 / 60.0 * 1000.0;		//フレームレートの設定＋ミリ単位に合わせる

		if (nextTime > GetNowCount())
		{
			WaitTimer((int)nextTime - GetNowCount());
		}
		else
		{
			nextTime = GetNowCount();
		}

		//裏画面の内容を表画面に反映
		ScreenFlip();
	}
}

void SceneManager::Draw() const
{
	now_sceen->Draw();
}

void SceneManager::Initialize()
{
	//Log.txtを作成しない
	SetOutApplicationLogValidFlag(FALSE);

	//タイトル
	SetMainWindowText("");

	//ウィンドウモードで起動
	ChangeWindowMode(TRUE);

	//常にアクティブ状態にする
	//SetAlwaysRunFlag(TRUE);	

	//画面サイズの設定
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	//サウンドの再生にWASAPIを使用する
	SetEnableWASAPIFlag(TRUE);

	//DXライブラリの初期化処理
	if (DxLib_Init() == -1)throw ("初期化失敗");

	//描画先を裏にする
	SetDrawScreen(DX_SCREEN_BACK);

	//背景の色を灰色にする
	SetBackgroundColor(128, 128, 128);

	//マウスカーソルを画面中央に設定
	SetMousePoint(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//マウスカーソルを表示しない
	SetMouseDispFlag(FALSE);

	if (now_sceen == nullptr)
	{
		now_sceen = dynamic_cast<SceneBase*>(new TitleScene());
	}

	ResourceManager::CreateManager();
}

void SceneManager::Finalize()
{
	if (now_sceen != nullptr)
	{
		now_sceen->Finalize();
		delete now_sceen;
		now_sceen = nullptr;
		initFlg = false;
	}

	ResourceManager::DeleteManager();

	//DXライブラリ使用の終了処理
	DxLib_End();
}
