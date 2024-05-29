#include "ResourceManager.h"
#include <stdexcept>

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
	SetImage("UI/stock");
	SetImage("UI/selectStock");
	SetImage("UI/kariSelect");
	SetImage("UI/dagger");
	SetImage("UI/largeSword");
	SetImage("UI/rapier");
	SetImage("Weapon/dagger");
	SetImage("Weapon/largeSword");
	SetImage("Weapon/rapier");
	SetDivImage("Effect/jumpEffect", 9, 9, 1, 60, 38);
	SetDivImage("Effect/rapierEffect", 6, 1, 6, 256, 74);
	SetDivImage("Effect/slashEffect", 7, 7, 1, 224, 208);

	//BGM
	
	//SE
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

		//キーにImageを読みこむ
		LoadDivGraph(filePath.c_str(), max, x, y, sizeX, sizeY, manager->divImage[fileName]);

		if (manager->divImage[fileName][0] == -1)
		{
			throw(std::invalid_argument("Imageが読み込めません。"));
		}
	}
}
