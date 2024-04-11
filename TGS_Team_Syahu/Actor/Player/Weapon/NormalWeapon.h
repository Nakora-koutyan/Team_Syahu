#pragma once
#include"../../Collision/Sphere/SphereCollision.h"

#define NORMAL_WEAPON_ATTACK_TIME	FPS * 0.5f		//攻撃時間

class GameMainScene;
class Player;

class NormalWeapon :public SphereCollision
{
private:
	int framCount;			//フレームカウント

public:
	//コンストラクタ
	NormalWeapon();

	//デストラクタ
	~NormalWeapon();

	//更新
	void Update(GameMainScene* object);

	//描画
	void Draw()const;

	//攻撃
	void Attack(const Player* player);
};

