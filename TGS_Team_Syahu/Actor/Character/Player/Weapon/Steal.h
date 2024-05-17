#pragma once
#include"../../../../Collision/Line/LineCollision.h"
#include"../../CharaBase.h"

#define STEAL_ATTACK_TIME	FPS * 0.2		//奪う攻撃の時間
#define STEAL_VALUE			3				//奪うの数
#define STEAL_DISTANCE		25.f			//プレイヤーから奪うを出す距離
#define STEAL_KNOCKBACK		1.5f			//奪うのノックバックの移動量/f

class Player;

class Steal :public LineCollision
{
private:
	LineCollision sideClaw[2] = {};		//鉤爪の横2つの判定用 0:上 1:下
	Weapon keepType;					//能力の保存用

	short direction;					//方向

	int framCount;						//フレームカウント

	bool isShow;						//表示させる？

public:
	//コンストラクタ
	Steal();

	//デストラクタ
	~Steal();

	//更新
	void Update(CharaBase* chara);

	//描画
	void Draw()const override;

	//攻撃
	void Attack(const CharaBase* chara);

	//ヒット処理
	void Hit(ObjectBase* target, const float damage)override;

public:
	//鉤爪の判定を取得
	LineCollision GetSideClaw(const int element) { return sideClaw[element]; }

	//表示フラグを取得
	bool GetIsShow()const { return isShow; }

	//能力の保存用を取得
	Weapon GetKeepType()const { return keepType; }

	//能力の保存用を設定
	void SetKeepType(const Weapon ability) { keepType = ability; }

};
