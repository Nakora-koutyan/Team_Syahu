#pragma once
#include<map>
#include<string>
#include"../Utility/Vector2D.h"
#include"../Actor/Character/CharaBase.h"	

class Player;

class UI
{
private:
	Weapon stockIcon[5];								//ストックのアイコン
	Vector2D playerHpBarLocation;						//プレイヤーのHPバーの座標

	short selectCount;									//選択しているストックの番号

	int playerDaggerCnt[5] = {};						//ダガーの本数

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

	//エネミーのHPバー
	void EnemyHPBar(const Vector2D location, const float hp)const;
};

