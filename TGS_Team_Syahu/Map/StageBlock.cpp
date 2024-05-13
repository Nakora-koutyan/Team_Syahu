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
	CharaBase* chara = static_cast<CharaBase*>(object);
	// 座標、移動量取得
	Vector2D objectLoc = object->GetLocation();
	Vector2D blockLoc = GetLocation();
	Vector2D move = chara->GetMove();
	Area objectSize = chara->GetArea();
	Area blockSize = GetArea();
	int dropWidth = 21;
	// 上から
	if ((objectLoc.y + objectSize.height - 20) <= blockLoc.y && chara->GetDirection().y >= 0.f &&
		(move.x != 0 || (objectLoc.x + objectSize.width - dropWidth <= blockLoc.x + blockSize.width && objectLoc.x + dropWidth >= blockLoc.x))) {
		chara->Landing(blockLoc.y);
	}
	// 下から
	else if (objectLoc.y >= (blockLoc.y + blockSize.height - 20) && chara->GetDirection().y <= 0.f) {
		// Dropwidth以上ブロックからはみ出してないか
		if (objectLoc.x + objectSize.width - dropWidth <= blockLoc.x + blockSize.width && objectLoc.x + dropWidth >= blockLoc.x) {
			objectLoc.y = blockLoc.y + blockSize.height;
			object->SetLocation(objectLoc);
			move.y = 0;
			chara->SetMove(move);
		}
		else
		{
			// 右から
			if (objectLoc.x + objectSize.width / 2 >= blockLoc.x + blockSize.width / 2) {
				objectLoc.x = blockLoc.x + blockSize.width;
			}
			// 左から
			else {
				objectLoc.x = blockLoc.x - objectSize.width;
			}
			object->SetLocation(objectLoc);
		}
	}
	else {
		// 右から
		if (objectLoc.x + objectSize.width / 2 >= blockLoc.x + blockSize.width / 2) {
			objectLoc.x = blockLoc.x + blockSize.width;
		}
		// 左から
		else {
			objectLoc.x = blockLoc.x - objectSize.width;
		}
		object->SetLocation(objectLoc);
		move.x = 0;
		chara->SetMove(move);
	}
}
;