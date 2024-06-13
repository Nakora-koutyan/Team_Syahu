#include "StageBlock.h"
#include "../Scene/GameMain/GameMainScene.h"
#include "../Actor/Character/Player/Player.h"
#include "../Actor/Camera/Camera.h"
#include "../ResourceManager/ResourceManager.h"

StageBlock::StageBlock(int x, int y, int type)
{
	location.x = x;
	location.y = y;

	area.width = BLOCK_WIDTH;
	area.height = BLOCK_HEIGHT;

	DrawType = type;
	IsDraw = true;

	switch (DrawType)
	{
	case 0:
		blockImg = ResourceManager::GetImage("Stage/Tiles/brick_1");
		break;
	case 1:
		blockImg = ResourceManager::GetImage("Stage/Tiles/brick_2");
		break;
	case 2:
		blockImg = ResourceManager::GetImage("Stage/Tiles/brick_3");
		break;
	case 3:
		blockImg = ResourceManager::GetImage("Stage/Tiles/brick_4");
		break;
	case 4:
		blockImg = ResourceManager::GetImage("Stage/Tiles/brick_5");
		break;
	case 5:
		blockImg = ResourceManager::GetImage("Stage/Tiles/brick_6");
		break;
	case 6:
		blockImg = ResourceManager::GetImage("Stage/Tiles/brick_7");
		break;
	case 7:
		blockImg = ResourceManager::GetImage("Stage/Tiles/brick_8");
		break;
	case 8:
		blockImg = ResourceManager::GetImage("Stage/Tiles/brick_9");
		break;
	case 9:
		blockImg = ResourceManager::GetImage("Stage/Tiles/brick_10");
		break;
	case 10:
		blockImg = ResourceManager::GetImage("Stage/Tiles/brick_11");
		break;
	case 11:
		blockImg = ResourceManager::GetImage("Stage/Tiles/brick_12");
		break;
	case 12:
		blockImg = ResourceManager::GetImage("Stage/Tiles/brick_13");
		break;
	case 13:
		blockImg = ResourceManager::GetImage("Stage/Tiles/brick_14");
		break;
	case 14:
		blockImg = ResourceManager::GetImage("Stage/Tiles/brick_15");
		break;
	case 15:
		blockImg = ResourceManager::GetImage("Stage/Tiles/brick_16");
		break;
	default:
		break;
	}
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
	DrawExtendGraph
	(
		screenLocation.x, screenLocation.y,
		GetMaxScreenLocation().x, GetMaxScreenLocation().y,
		blockImg, TRUE
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
	if ((objectLoc.y + objectSize.height - 40) <= blockLoc.y && chara->GetDirection().y >= 0.f /* &&
		(move.x != 0 || (objectLoc.x + objectSize.width - dropWidth <= blockLoc.x + blockSize.width && objectLoc.x + dropWidth >= blockLoc.x))*/) {
		chara->Landing(blockLoc.y);
	}
	// 下から
	else if (objectLoc.y >= (blockLoc.y + blockSize.height - 40) && chara->GetDirection().y <= 0.f) {
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
		//右から
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
