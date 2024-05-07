#include "StageBlock.h"
#include "../Scene/GameMain/GameMainScene.h"
#include "../Actor/Player/Player.h"
#include "../Actor/Camera/Camera.h"

StageBlock::StageBlock() {
	location.x = 1000.f;
	location.y = 1240.f;

	area.width = 100.f;
	area.height = 100.f;

	DrawType = 0;
	IsDraw = TRUE;
};

StageBlock::~StageBlock() {

};

void StageBlock::Update() {
	//カメラに応じて座標を変化
	screenLocation = Camera::ConvertScreenPosition(location);

	
};

void StageBlock::Draw()const {
	//ブロックの描画
	DrawBoxAA
	(
		screenLocation.x, screenLocation.y,
		GetMaxScreenLocation().x, GetMaxScreenLocation().y,
		0x00ff00 , TRUE
	);

	//タイプ表示(仮)
	DrawFormatStringF(screenLocation.x + 5, screenLocation.y + 5, 0x660066, "%d", DrawType);

	//画面描画(仮)
	DrawFormatStringF(screenLocation.x + 15, screenLocation.y + 5, 0x660066, "%d", IsDraw);
};