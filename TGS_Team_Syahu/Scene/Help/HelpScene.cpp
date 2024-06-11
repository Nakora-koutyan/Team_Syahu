#include "HelpScene.h"

//コンストラクタ
HelpScene::HelpScene():helpTextImage(NULL),enemyTextImage(NULL),operationTextImage(NULL),
closeTextImage(NULL)
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

	cursorImage = LoadGraph("Resource/Images/UI/cursor.png");
}

void HelpScene::Finalize()
{
}

//描画以外の更新
SceneBase* HelpScene::Update()
{
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

	DrawRotaGraphF(100, 350 + cursorLocY, 1, DEGREE_TO_RADIAN(90.f), cursorImage, TRUE);
}
