#pragma once
#include"../../../Collision/Sphere/SphereCollision.h"

#define NORMAL_WEAPON_ATTACK_TIME	FPS * 5.5f		//通常攻撃の時間
#define NORMAL_WEAPON_SPEED				15.f		//弾の速さ

class CharaBase;
class Player;

class NormalWeapon :public SphereCollision
{
private:
	short direction;		//方向

	int framCount;			//フレームカウント

	bool isShow;			//表示させる？

public:
	//コンストラクタ
	NormalWeapon();

	//デストラクタ
	~NormalWeapon();

	//更新
	void Update(Player* player);

	//描画
	void Draw()const;

	//攻撃
	void Attack(const Player* player);

	//当たった時の処理
	void Hit(CharaBase* enemy, Player* player);

	//表示フラグを取得
	bool GetIsShow()const { return isShow; }
};

