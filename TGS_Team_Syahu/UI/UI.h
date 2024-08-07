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
	Vector2D playerLocation;							//プレイヤーの座標

	short selectCount;									//選択しているストックの番号

	int playerDaggerCnt[5];								//ダガーの本数
	int playerWeaponDurability[5];						//耐久値
	const int maxIcon = 5;

	float playerHp;										//プレイヤーのHP
	float playerAttackCoolTime;							//プレイヤーの攻撃のクールタイム

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
	//エネミーのHPバー
	void EnemyHPBar(const Vector2D location, const float hp)const;

private:
	//プレイヤーのHPバー
	void PlayerHPBar()const;

	//プレイヤーのストック
	void PlayerStock()const;

	//プレイヤーの装備している武器
	void PlayerEquipmentWeapon()const;

	//プレイヤーの攻撃のクールタイム
	void PlayerAttackCoolTimeBar()const;

	//ボタンのUI
	void Button()const;
};

