#pragma once
#include<DxLib.h>
#include<map>
#include<string>

class ResourceManager
{
private:
	static ResourceManager* manager;						//オブジェクト

	std::string path;										//パス

	std::map<std::string, int> bgm;							//BGM
	std::map<std::string, int> se;							//SE
	std::map<std::string, int> image;						//画像
	std::map<std::string, int[100]> divImage;				//分割読み込み用の画像

public:
	//コンストラクタ
	ResourceManager() {};

	//デストラクタ
	~ResourceManager() {};

	//作成
	static void CreateManager();

	//削除
	static void DeleteManager();

	//初期化
	static void Initialize();

public:
	//BGMを取得
	static int GetBGM(const std::string fileName) { return manager->bgm[fileName]; }

	//SEを取得
	static int GetSE(const std::string fileName) { return manager->se[fileName]; }

	//画像を取得
	static int GetImage(const std::string fileName) { return manager->image[fileName]; }

	//分割読み込みの画像を取得
	static int GetDivImage(const std::string fileName, const int element) { return manager->divImage[fileName][element]; }

	//分割読み込みの画像ポインタを取得
	static int* GetDivImagePtr(const std::string fileName) { return manager->divImage[fileName]; }

public:
	//BGMを設定
	static void SetBGM(const std::string fileName);

	//SEを設定
	static void SetSE(const std::string fileName);

	//画像を設定
	static void SetImage(const std::string fileName);

	//分割読み込みの画像を設定
	static void SetDivImage(const std::string fileName, const int max, const int x, const int y, const int sizeX, const int sizeY);

};

