#pragma once
#include<DxLib.h>
#include<map>
#include<string>
#include<vector>

class ResourceManager
{
private:
	static ResourceManager* manager;								//オブジェクト

	std::string path;												//パス

	std::map<std::string, int> bgm;									//BGM
	std::map<std::string, int> se;									//SE
	std::map<std::string, int> image;								//画像
	std::map<std::string, std::vector<int>> divImage;				//分割読み込みの画像

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
	//bgm配列の取得
	static std::map<std::string,int> GetMapBgm() { return manager->bgm; }

	//BGMを取得
	static int GetBGM(const std::string fileName) { return manager->bgm[fileName]; }

	//se配列の取得
	static std::map<std::string, int> GetMapSe() { return manager->se; }

	//SEを取得
	static int GetSE(const std::string fileName) { return manager->se[fileName]; }

	//画像配列の取得
	static std::map<std::string, int> GetMapImage() { return manager->image; }

	//画像を取得
	static int GetImage(const std::string fileName) { return manager->image[fileName]; }

	//分割読み込みの画像配列を取得
	static std::map<std::string, std::vector<int>> GetMapDivImage() { return manager->divImage; }

	//分割読み込みの画像を取得
	static int GetDivImage(const std::string fileName, const int element) { return manager->divImage[fileName][element]; }

public:
	//BGMを設定
	static void SetBGM(const std::string fileName);

	//SEを設定
	static void SetSE(const std::string fileName);

	//画像を設定
	static void SetImage(const std::string fileName);

	//分割読み込みの画像を設定
	static void SetDivImage(const std::string fileName, const int max, const int x, const int y, const int sizeX, const int sizeY);

public:
	//すべてのBGMの音量を設定
	static void SetVolumeAllBGM(const int volume);

	//すべてのSEの音量を設定
	static void SetVolumeAllSE(const int volume);

	//すべてのBGMの再生位置を設定
	//再生位置をミリ秒単位で変更
	static void SetPositionAllBGM(LONGLONG time);

	//すべてのSEの再生位置を設定
	//再生位置をミリ秒単位で変更
	static void SetPositionAllSE(LONGLONG time);

	//BGMを再生
	//isSingleUnitはtrueなら音を重ねない、falseなら音を重ねる、デフォルトはtrue
	//デフォルトの再生形式はループ
	//デフォルトの再生位置は最後に止めたところか、再生位置を指定したところから
	static void PlayBGM(const std::string fileName, bool isSingleUnit = true, int playType = DX_PLAYTYPE_LOOP, int topPositionFlag = FALSE);

	//SEを再生
	//isSingleUnitはtrueなら音を重ねない、falseなら音を重ねる、デフォルトはtrue
	//デフォルトの再生形式はバック
	//デフォルトの再生位置は先頭から
	static void PlaySE(const std::string fileName, bool isSingleUnit = true, int playType = DX_PLAYTYPE_BACK, int topPositionFlag = TRUE);

	//BGMを停止
	static void StopBGM(const std::string fileName);

	//すべてのBGMを停止
	static void StopAllBGM();

	//SEを停止
	static void StopSE(const std::string fileName);

	//すべてのSEを停止
	static void StopAllSE();

};