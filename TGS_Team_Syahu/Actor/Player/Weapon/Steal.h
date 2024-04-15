#pragma once
#include "../../../Collision/Sphere/SphereCollision.h"

#define STEAL_ATTACK_TIME	FPS * 0.5		//奪う攻撃の時間

class GameMainScene;
class Player;

class Steal :public SphereCollision
{
private:
	short direction;		//方向

	int framCount;			//フレームカウント

	bool isShow;			//表示させる？

public:
	//コンストラクタ
	Steal();

	//デストラクタ
	~Steal();

	//更新
	void Update(GameMainScene* object);

	//描画
	void Draw()const;

	//攻撃
	void Attack(const Player* player);

	//当たり判定
	void Hit(GameMainScene* object);

	//表示フラグを取得
	bool GetIsShow()const { return isShow; }

private:
	//奪う攻撃
	void StealAttack(class CharaBase* enemy, Player* player);

};
