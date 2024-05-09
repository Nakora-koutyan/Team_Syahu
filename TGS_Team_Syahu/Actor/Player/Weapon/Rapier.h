#pragma once
#include "../../../Collision/Line/LineCollision.h"

#define RAPIER_ATTACK_TIME				FPS * 0.3		//レイピア攻撃の時間
#define RAPIER_MOVE						10.5f			//レイピアの移動量/f
#define RAPIER_LENGTH					90.f			//レイピアの長さ
#define RAPIER_WEIGHT					0.35f			//レイピアの重さ
#define RAPIER_DAMAGE					3.f				//レイピアのダメージ

class CharaBase;
class Player;

class Rapier :public LineCollision
{
private:
	short direction;		//方向

	int framCount;			//フレームカウント

	float angle;			//角度

	bool isShow;			//表示させる？

public:
	//コンストラクタ
	Rapier();

	//デストラクタ
	~Rapier();

	//更新
	void Update(CharaBase* chara);

	//描画
	void Draw()const;

	//攻撃
	void Attack(const Player* player);

	//当たった時の処理
	void Hit(CharaBase* enemy, const Player* player);

};

