#include"ResourceManager.h"
#include<stdexcept>

ResourceManager* ResourceManager::manager = nullptr;

void ResourceManager::CreateManager()
{
	//オブジェクトの作成
	if (manager == nullptr)
	{
		manager = new ResourceManager();
	}
}

void ResourceManager::DeleteManager()
{
	InitSoundMem();
	InitGraph();
	delete manager;
	manager = nullptr;
}

void ResourceManager::Initialize()
{
	//画像
	SetDivImage("Player/player", 72, 8, 9, 96, 96);
	SetImage("UI/bar");
	SetImage("UI/barBackground");
	SetImage("UI/healthBar");
	SetImage("UI/durabilityBar");
	SetImage("UI/attackCoolTimeBar");
	SetImage("UI/barFram");
	SetImage("UI/barFramEnemy");
	SetImage("UI/stock");
	SetImage("UI/selectStock");
	SetImage("UI/kariSelect");
	SetImage("UI/dagger");
	SetImage("UI/largeSword");
	SetImage("UI/rapier");	
	SetImage("UI/cursor");
	SetImage("UI/ButtonA");
	SetImage("UI/ButtonB");
	SetImage("UI/ButtonX");
	SetImage("UI/ButtonY");
	SetImage("UI/ButtonLB");
	SetImage("UI/ButtonRB");
	SetImage("UI/Attack");
	SetImage("UI/Jump");
	SetImage("UI/Steal");
	SetImage("Weapon/dagger");
	SetImage("Weapon/largeSword");
	SetImage("Weapon/rapier");
	SetDivImage("Effect/jumpEffect", 14, 14, 1, 60, 32);
	SetDivImage("Effect/rapierEffect", 7, 1, 7, 312, 78);
	SetDivImage("Effect/slashEffect", 7, 7, 1, 224, 208);
	SetDivImage("Effect/fallAttackEffect", 7, 7, 1, 200, 224);
	SetImage("Effect/Steal/steal_1");
	SetImage("Effect/Steal/steal_2");
	SetImage("Effect/Steal/steal_3");
	SetImage("Effect/Steal/steal_4");
	SetImage("Effect/Steal/steal_5");
	SetImage("Effect/Steal/steal_6");
	SetImage("Effect/Steal/steal_7");
	SetImage("Effect/Steal/steal_8");
	SetImage("Effect/Steal/steal_9");
	SetImage("Effect/Steal/steal_10");
	SetDivImage("Effect/transformEffect", 9, 9, 1, 240, 240);
	SetImage("Stage/Background/layer_1");
	SetImage("Stage/Background/layer_2");
	SetImage("Title/TitleText");
	SetImage("Title/StartText");
	SetImage("Title/HelpText");
	SetImage("Title/EndText");
	SetImage("GameClear/CongratulationsText");
	SetImage("GameClear/BackGround1");
	SetImage("GameClear/BackGround2");
	SetImage("GameClear/BackGround3");
	SetImage("GameClear/Tile");
	SetImage("GameOver/BackTitleText");
	SetImage("GameOver/ContinueText");
	SetImage("GameOver/GameOverText");
	SetImage("GameOver/GameOverBackGround");
	SetImage("Stage/Tiles/blank");
	SetImage("Stage/Tiles/ceiling_1");
	SetImage("Stage/Tiles/ceiling_2");
	SetImage("Stage/Tiles/ceiling_3");
	SetImage("Stage/Tiles/ceiling_4");
	SetImage("Stage/Tiles/floor_tile_1");
	SetImage("Stage/Tiles/floor_tile_2");
	SetImage("Stage/Tiles/floor_tile_3");
	SetImage("Stage/Tiles/floor_tile_4");
	SetImage("Stage/Tiles/floor_tile_corner_left");
	SetImage("Stage/Tiles/floor_tile_corner_right");
	SetImage("Stage/Tiles/floor_tile_carpet_1");
	SetImage("Stage/Tiles/floor_tile_carpet_2");
	SetImage("Stage/Tiles/floor_tile_carpet_3");
	SetImage("Stage/Tiles/floor_tile_carpet_4");
	SetImage("Stage/Tiles/floor_tile_carpet_corner_left");
	SetImage("Stage/Tiles/floor_tile_carpet_corner_right");
	SetImage("Stage/Tiles/floor_tile_carpet_transition_1");
	SetImage("Stage/Tiles/floor_tile_carpet_transition_2");
	SetImage("Stage/Tiles/floor_tile_wood_carpet_transition_1");
	SetImage("Stage/Tiles/floor_tile_carpet_transition_2");
	SetImage("Stage/Tiles/floor_tile_wood_transition_1");
	SetImage("Stage/Tiles/floor_tile_wood_transition_2");
	SetImage("Stage/Tiles/floor_wood_1");
	SetImage("Stage/Tiles/floor_wood_2");
	SetImage("Stage/Tiles/floor_wood_3");
	SetImage("Stage/Tiles/floor_wood_4");
	SetImage("Stage/Tiles/floor_wood_corner_left");
	SetImage("Stage/Tiles/floor_wood_corner_right");
	SetImage("Stage/Tiles/floor_wood_carpet_1");
	SetImage("Stage/Tiles/floor_wood_carpet_2");
	SetImage("Stage/Tiles/floor_wood_carpet_3");
	SetImage("Stage/Tiles/floor_wood_carpet_4");
	SetImage("Stage/Tiles/floor_wood_carpet_corner_left");
	SetImage("Stage/Tiles/floor_wood_carpet_corner_right");
	SetImage("Stage/Tiles/floor_wood_carpet_transition_1");
	SetImage("Stage/Tiles/floor_wood_carpet_transition_2");
	SetImage("Stage/Tiles/tile_side_left");
	SetImage("Stage/Tiles/tile_side_right");
	SetImage("End/credit");
	SetImage("End/thanks");

	//BGM
	SetBGM("gamemain");
	SetBGM("title");
	SetBGM("gameover");
	SetBGM("gameclear");

	SetLoopPosSoundMem(25900, manager->bgm["gamemain"]);
	SetLoopPosSoundMem(56400, manager->bgm["gameclear"]);

	SetVolumeAllBGM(50);
	
	//SE
	SetSE("dagger");
	SetSE("largeSword");
	SetSE("rapier");
	SetSE("fallAttack");
	SetSE("equipment");
	SetSE("steal");
	SetSE("damage");
	SetSE("walk");
	SetSE("stockSelect");
	SetSE("jump");
	SetSE("cursorMove");
	SetSE("cursorSelect");

	SetVolumeAllSE(50);

}

void ResourceManager::SetBGM(const std::string fileName)
{
	//ローカル変数iteratorにfileNameキーの検索結果を代入
	auto iterator = manager->bgm.find(fileName);

	//設定されていない場合
	if (iterator == manager->bgm.end())
	{
		//ファイルのパス
		std::string filePath;
		filePath = std::string("Resource/Sounds/BGM/") + fileName + std::string(".wav");

		//キーにBGMを読みこむ
		manager->bgm[fileName] = LoadSoundMem(filePath.c_str());

		if (manager->bgm[fileName] == -1)
		{
			throw(std::invalid_argument("BGMが読み込めません。"));
		}
	}
}

void ResourceManager::SetSE(const std::string fileName)
{
	//ローカル変数iteratorにfileNameキーの検索結果を代入
	auto iterator = manager->se.find(fileName);

	//設定されていない場合
	if (iterator == manager->se.end())
	{
		//ファイルのパス
		std::string filePath;
		filePath = std::string("Resource/Sounds/SE/") + fileName + std::string(".wav");

		//キーにSEを読みこむ
		manager->se[fileName] = LoadSoundMem(filePath.c_str());
		
		if (manager->se[fileName] == -1)
		{
			throw(std::invalid_argument("SEが読み込めません。"));
		}
	}
}

void ResourceManager::SetImage(const std::string fileName)
{
	//ローカル変数iteratorにfileNameキーの検索結果を代入
	auto iterator = manager->image.find(fileName);

	//設定されていない場合
	if (iterator == manager->image.end())
	{
		//ファイルのパス
		std::string filePath;
		filePath = std::string("Resource/Images/") + fileName + std::string(".png");

		//キーにImageを読みこむ
		manager->image[fileName] = LoadGraph(filePath.c_str());

		if (manager->image[fileName] == -1)
		{
			throw(std::invalid_argument("Imageが読み込めません。"));
		}
	}
}

void ResourceManager::SetDivImage(const std::string fileName, const int max, const int x, const int y, const int sizeX, const int sizeY)
{
	//ローカル変数iteratorにfileNameキーの検索結果を代入
	auto iterator = manager->divImage.find(fileName);

	//設定されていない場合
	if (iterator == manager->divImage.end())
	{
		//ファイルのパス
		std::string filePath;
		filePath = std::string("Resource/Images/") + fileName + std::string(".png");

		manager->divImage[fileName].reserve(max);

		for (int i = 0; i < max; i++)
		{
			manager->divImage[fileName].push_back(0);
		}

		//キーにImageを読みこむ
		LoadDivGraph(filePath.c_str(), max, x, y, sizeX, sizeY, manager->divImage[fileName].data());
		//LoadDivGraph(filePath.c_str(), max, x, y, sizeX, sizeY, manager->divImage[fileName]);

		if (manager->divImage[fileName][0] == -1)
		{
			throw(std::invalid_argument("Imageが読み込めません。"));
		}
	}
}

void ResourceManager::SetVolumeAllBGM(const int volume)
{
	for (auto iterator = manager->bgm.begin(); iterator != manager->bgm.end(); ++iterator)
	{
		ChangeVolumeSoundMem((255 * volume) / 100, manager->bgm[iterator->first]);
	}
}

void ResourceManager::SetVolumeAllSE(const int volume)
{
	for (auto iterator = manager->se.begin(); iterator != manager->se.end(); ++iterator)
	{
		ChangeVolumeSoundMem((255 * volume) / 100, manager->se[iterator->first]);
	}
}

void ResourceManager::SetPositionAllBGM(LONGLONG time)
{
	for (auto iterator = manager->bgm.begin(); iterator != manager->bgm.end(); ++iterator)
	{
		SetSoundCurrentTime(time, manager->bgm[iterator->first]);
	}
}

void ResourceManager::SetPositionAllSE(LONGLONG time)
{
	for (auto iterator = manager->se.begin(); iterator != manager->se.end(); ++iterator)
	{
		SetSoundCurrentTime(time, manager->se[iterator->first]);
	}
}

void ResourceManager::PlayBGM(const std::string fileName, bool isSingleUnit, int playType, int topPositionFlag)
{
	//音を重ねない
	if (isSingleUnit)
	{
		if (!CheckSoundMem(manager->bgm[fileName]))
		{
			//現在なっている音を止める
			for (auto iterator = manager->bgm.begin(); iterator != manager->bgm.end(); ++iterator)
			{
				if (CheckSoundMem(manager->bgm[iterator->first]))
				{
					StopSoundMem(manager->bgm[iterator->first]);
					SetSoundCurrentTime(0, manager->bgm[iterator->first]);
				}
			}
			PlaySoundMem(manager->bgm[fileName], playType, topPositionFlag);
		}
	}
	//音を重ねる
	else
	{
		if (!CheckSoundMem(manager->bgm[fileName]))
		{
			PlaySoundMem(manager->bgm[fileName], playType, topPositionFlag);
		}
	}
}

void ResourceManager::PlaySE(const std::string fileName, bool isSingleUnit, int playType, int topPositionFlag)
{
	//音を重ねない
	if (isSingleUnit)
	{
		if (!CheckSoundMem(manager->se[fileName]))
		{
			PlaySoundMem(manager->se[fileName], playType, topPositionFlag);
		}
	}
	//音を重ねる
	else
	{
		PlaySoundMem(manager->se[fileName], playType, topPositionFlag);
	}
}

void ResourceManager::StopBGM(const std::string fileName)
{
	StopSoundMem(manager->bgm[fileName]);
}

void ResourceManager::StopAllBGM()
{
	for (auto iterator = manager->bgm.begin(); iterator != manager->bgm.end(); ++iterator)
	{
		StopSoundMem(manager->bgm[iterator->first]);
	}
}

void ResourceManager::StopSE(const std::string fileName)
{
	StopSoundMem(manager->se[fileName]);
}

void ResourceManager::StopAllSE()
{
	for (auto iterator = manager->se.begin(); iterator != manager->se.end(); ++iterator)
	{
		StopSoundMem(manager->se[iterator->first]);
	}
}
