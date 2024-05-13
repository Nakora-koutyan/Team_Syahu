#include "StageBlock.h"
#include "../Scene/GameMain/GameMainScene.h"
#include "../Actor/Character/Player/Player.h"
#include "../Actor/Camera/Camera.h"

StageBlock::StageBlock() 
{
	location.x = 1000.f;
	location.y = 1140.f;

	area.width = 200.f;
	area.height = 100.f;

	DrawType = 0;
	IsDraw = TRUE;
};

StageBlock::~StageBlock() 
{

};

void StageBlock::Update() 
{
	//カメラに応じて座標を変化
	screenLocation = Camera::ConvertScreenPosition(location);

	
};

void StageBlock::Draw()const 
{
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
}

void StageBlock::Hit(ObjectBase* object, const float damage)
{
	//// 座標、移動量取得
	//Vector2D ObjectLoc = object->GetLocation();
	//Vector2D BlockLoc = GetLocation();
	//Vector2D move = object->GetMove();
	//Area ObjectSize = object->GetArea();
	//Area BlockSize = GetArea();
	//int Dropwidth = 21;
	//// 上から
	//if ((ObjectLoc.y + ObjectSize.height - 20) <= BlockLoc.y && object->GetDirection().y >= 0.f &&
	//	(move.x != 0 || (ObjectLoc.x + ObjectSize.width - Dropwidth <= BlockLoc.x + BlockSize.width && ObjectLoc.x + Dropwidth >= BlockLoc.x))) {
	//	object->Landing(BlockLoc.y);
	//}
	//// 下から
	//else if (ObjectLoc.y >= (BlockLoc.y + BlockSize.height - 20) && object->GetDirection().y <= 0.f) {
	//	// Dropwidth以上ブロックからはみ出してないか
	//	if (ObjectLoc.x + ObjectSize.width - Dropwidth <= BlockLoc.x + BlockSize.width && ObjectLoc.x + Dropwidth >= BlockLoc.x) {
	//		ObjectLoc.y = BlockLoc.y + BlockSize.height;
	//		object->SetLocation(ObjectLoc);
	//		move.y = 0;
	//		object->SetMove(move);
	//	}
	//	else
	//	{
	//		// 右から
	//		if (ObjectLoc.x + ObjectSize.width / 2 >= BlockLoc.x + BlockSize.width / 2) {
	//			ObjectLoc.x = BlockLoc.x + BlockSize.width;
	//		}
	//		// 左から
	//		else {
	//			ObjectLoc.x = BlockLoc.x - ObjectSize.width;
	//		}
	//		object->SetLocation(ObjectLoc);
	//	}
	//}
	//else {
	//	// 右から
	//	if (ObjectLoc.x + ObjectSize.width / 2 >= BlockLoc.x + BlockSize.width / 2) {
	//		ObjectLoc.x = BlockLoc.x + BlockSize.width;
	//	}
	//	// 左から
	//	else {
	//		ObjectLoc.x = BlockLoc.x - ObjectSize.width;
	//	}
	//	object->SetLocation(ObjectLoc);
	//	move.x = 0;
	//	object->SetMove(move);
	//}
}
;