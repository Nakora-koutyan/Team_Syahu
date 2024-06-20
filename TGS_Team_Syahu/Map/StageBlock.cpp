#include "StageBlock.h"
#include "../Scene/GameMain/GameMainScene.h"
#include "../Actor/Character/Player/Player.h"
#include "../Actor/Camera/Camera.h"
#include "../ResourceManager/ResourceManager.h"
#include "BlockDeta.h"

StageBlock::StageBlock(float x, float y, int type)
{
	location.x = x;
	location.y = y;

	area.width = BLOCK_WIDTH;
	area.height = BLOCK_HEIGHT;

	DrawType = type;
	IsDraw = true;
	blockImg = NULL;

	blockdeta = new BlockDeta;

	int blockLocationX = (int)x / (int)BLOCK_WIDTH;
	int blockLocationY = (int)y / (int)BLOCK_HEIGHT;
	blockdeta->setStageBlockData(blockLocationX, blockLocationY, true);

	switch (DrawType)
	{
	case 0:
		blockImg = ResourceManager::GetImage("Stage/Tiles/blank");
		break;
	case 1:
		blockImg = ResourceManager::GetImage("Stage/Tiles/ceiling_1");
		break;
	case 2:
		blockImg = ResourceManager::GetImage("Stage/Tiles/ceiling_2");
		break;
	case 3:
		blockImg = ResourceManager::GetImage("Stage/Tiles/ceiling_3");
		break;
	case 4:
		blockImg = ResourceManager::GetImage("Stage/Tiles/ceiling_4");
		break;
	case 5:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_tile_1");
		break;
	case 6:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_tile_2");
		break;
	case 7:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_tile_3");
		break;
	case 8:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_tile_4");
		break;
	case 9:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_tile_corner_left");
		break;
	case 10:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_tile_corner_right");
		break;
	case 11:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_tile_carpet_1");
		break;
	case 12:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_tile_carpet_2");
		break;
	case 13:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_tile_carpet_3");
		break;
	case 14:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_tile_carpet_4");
		break;
	case 15:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_tile_carpet_corner_left");
		break;
	case 16:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_tile_carpet_corner_right");
		break;
	case 17:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_tile_carpet_transition_1");
		break;
	case 18:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_tile_carpet_transition_2");
		break;
	case 19:
		blockImg = ResourceManager::GetImage("floor_tile_wood_carpet_transition_1");
		break;
	case 20:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_tile_carpet_transition_2");
		break;
	case 21:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_tile_wood_transition_1");
		break;
	case 22:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_tile_wood_transition_2");
		break;
	case 23:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_wood_1");
		break;
	case 24:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_wood_2");
		break;
	case 25:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_wood_3");
		break;
	case 26:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_wood_4");
		break;
	case 27:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_wood_corner_left");
		break;
	case 28:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_wood_corner_right");
		break;
	case 29:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_wood_carpet_1");
		break;
	case 30:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_wood_carpet_2");
		break;
	case 31:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_wood_carpet_3");
		break;
	case 32:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_wood_carpet_4");
		break;
	case 33:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_wood_carpet_corner_left");
		break;
	case 34:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_wood_carpet_corner_right");
		break;
	case 35:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_wood_carpet_transition_1");
		break;
	case 36:
		blockImg = ResourceManager::GetImage("Stage/Tiles/floor_wood_carpet_transition_2");
		break;
	case 37:
		blockImg = ResourceManager::GetImage("Stage/Tiles/tile_side_left");
		break;
	case 38:
		blockImg = ResourceManager::GetImage("Stage/Tiles/tile_side_right");
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
	DrawExtendGraphF
	(
		screenLocation.x, screenLocation.y,
		GetMaxScreenLocation().x, GetMaxScreenLocation().y,
		blockImg, TRUE
	);
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
	if ((objectLoc.y + objectSize.height - 40 <= blockLoc.y) && (chara->GetDirection().y >= 0.f)) 
	{
		chara->Landing(blockLoc.y);
	}
	else if (objectLoc.y >= (blockLoc.y + blockSize.height-20) && chara->GetDirection().y <= 0.f) 
	{
		// Dropwidth以上ブロックからはみ出してないか
		if ((objectLoc.x + objectSize.width - dropWidth) <= (blockLoc.x + blockSize.width) 
			&& objectLoc.x + dropWidth >= blockLoc.x)
		{
			objectLoc.y = blockLoc.y + blockSize.height;
			object->SetLocation(objectLoc);
			move.y = 0;
			chara->SetMove(move);
		}
		else
		{
			int blockLocationX = (int)blockLoc.x / (int)BLOCK_WIDTH;
			int blockLocationY = (int)blockLoc.y / (int)BLOCK_HEIGHT;
			// 右にずれる
			if (objectLoc.x + objectSize.width / 2 >= blockLoc.x + blockSize.width / 2)
			{
				if (blockdeta->getStageBlockData(blockLocationX + 1, blockLocationY) != true) {
					objectLoc.x = blockLoc.x + blockSize.width;
				}
			}
			// 左にずれる
			else
			{
				if (blockdeta->getStageBlockData(blockLocationX - 1, blockLocationY) != true) {
					objectLoc.x = blockLoc.x - objectSize.width;
				}
			}
			object->SetLocation(objectLoc);
		}
	}
	else {
		object->SetOldLocationX();
		objectLoc = object->GetLocation();
		objectLoc.x = objectLoc.x - move.x;
		chara->SetLocationX(objectLoc.x);

		if (object ->GetObjectType() == ObjectType::Player&& chara->GetIsKnockBack())
		{
			chara->SetKnockBackCount(int (PLAYER_KNOCKBACK_TIME));
		}
		// oldLocationがブロック内になってしまった場合強制的に外に出す
		Vector2D ba = object->GetOldLocation();
		if (blockLoc.x <= ba.x && ba.x <= blockLoc.x + (int)BLOCK_WIDTH || blockLoc.y <= ba.y && ba.y <= blockLoc.y + (int)BLOCK_HEIGHT ||
 			blockLoc.x <= ba.x + objectSize.width && ba.x + objectSize.width <= blockLoc.x + (int)BLOCK_WIDTH || blockLoc.y <= ba.y + objectSize.height && ba.y + objectSize.height < blockLoc.y + (int)BLOCK_HEIGHT) {
			if (objectLoc.x + objectSize.width / 2 >= blockLoc.x + blockSize.width / 2)
			{
				objectLoc.x = blockLoc.x + blockSize.width;
			}
			// 左にずれる
			else
			{
				objectLoc.x = blockLoc.x - objectSize.width;
			}
			move.x = 0;
		}
		chara->SetLocationX(objectLoc.x);
		chara->SetMove(move);
	}
}
