#pragma once
#include "../CharaBase.h"
#include "../Player/Player.h"

#define MAX_COOL_TIME 100
#define MAX_ATTACK_TIME 100

struct EnemyStatus
{
	int AttackStandBy;
};

class EnemyBase :public CharaBase
{
protected:
	//追跡する？
	bool isChase;

	//パトロールする？
	bool isPatrol;

	//パトロール方向切り替え用のタイマー
	float patrolCounter;

	//攻撃のクールタイム
	int attackCoolTime;

	//攻撃時間
	int attackTime;

	//自身の行動を禁止する？
	bool noMove;

public:
	//コンストラクタ
	EnemyBase();
	//デストラクタ
	~EnemyBase();

	//更新処理
	void Update(Player* player);

	//描画処理
	void Draw(Player* player);

protected:

	//パトロール関数
	virtual void EnemyPatrol(Player* player) = 0;

	//攻撃範囲
	virtual void AttackRange() = 0;

	//プレイヤーを発見するためのセンサー
	virtual void ChaseRange() = 0;

	//攻撃準備
	virtual void AttackStandBy(Player* player) = 0;

	//攻撃開始
	virtual void AttackStart(Player* player) = 0;

	//攻撃終了
	virtual void AttackEnd() = 0;

	//プレイヤーとの当たり判定
	virtual void ClashToPlayer(Player* player) = 0;
};

