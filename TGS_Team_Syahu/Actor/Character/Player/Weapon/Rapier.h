#pragma once
#include "../../../../Collision/Line/LineCollision.h"

#define RAPIER_ATTACK_TIME				FPS * 0.4		//レイピア攻撃の時間
#define RAPIER_MOVE						15.5f			//レイピアの移動量/f
#define RAPIER_LENGTH					100.f			//レイピアの長さ
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
	bool isHit;				//当たったか？
	bool isUnable;			//当たり判定ができない？

public:
	//コンストラクタ
	Rapier();

	//デストラクタ
	~Rapier();

	//更新
	void Update(CharaBase* chara);

	//描画
	void Draw()const override;

	//攻撃
	void Attack(const CharaBase* chara);

	//ヒット処理
	void Hit(ObjectBase* object, const float damage)override;

public:
	//当たったかどうか取得
	bool GetIsHit()const { return isHit; }

	//当たっているかどうかを設定
	void SetIsHit(const bool flg) { isHit = flg; }

};

