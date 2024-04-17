#pragma once
#include "../../../Collision/Sphere/SphereCollision.h"
#include "../../../Collision/Line/LineCollision.h"
#include"../../CharaBase.h"

#define STEAL_ATTACK_TIME	FPS * 0.1		//奪う攻撃の時間

class Player;
class CharaBase;

class Steal :public LineCollision
{
private:
	Ability keepType;		//能力の保存用

	short direction;		//方向

	int framCount;			//フレームカウント

	bool isShow;			//表示させる？

public:
	//コンストラクタ
	Steal();

	//デストラクタ
	~Steal();

	//更新
	void Update(Player* player);

	//描画
	void Draw()const;

	//攻撃
	void Attack
	(const Player* player, const float distance, const float direX, const float direY, const float locY);

	//当たった時の処理
	void Hit(CharaBase* enemy, Player* player);

	//表示フラグを取得
	bool GetIsShow()const { return isShow; }

	//能力の保存用を取得
	Ability GetKeepType()const { return keepType; }

	//能力の保存用を設定
	void SetKeepType(const Ability ability) { keepType = ability; }

private:
	//奪う攻撃
	void StealAttack(class CharaBase* enemy, Player* player);

};
