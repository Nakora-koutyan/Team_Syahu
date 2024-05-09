#pragma once
#include<map>
#include<string>
#include"../Utility/Vector2D.h"
#include"../Actor/Character/CharaBase.h"	

class Player;

class UI
{
private:
	std::map<std::string, int> playerHpBarImage;		//プレイヤーのHPバーの画像

	Weapon stockIcon[5];								//ストックのアイコン
	Vector2D playerHpBarLocation;						//プレイヤーのHPバーの座標

	short selectCount;									//選択しているストックの番号

	int stockImage;										//ストックの画像
	int selectImage[2];									//選択しているアイコンの画像
	int largeSwordIcon;									//大剣のアイコン

	float playerHp;										//プレイヤーのHP

	bool decisionFlg;									//決定している？

public:
	//コンストラクタ
	UI();

	//デストラクタ
	~UI();

	//更新
	void Update(const Player* player);

	//描画
	void Draw()const;

public:
	//プレイヤーのHPバー
	void PlayerHPBar()const;

	//プレイヤーのストック
	void PlayerStock()const;
};

