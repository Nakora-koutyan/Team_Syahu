#pragma once
#include "../SceneBase.h"
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
};

