#pragma once
#include "../CharaBase.h"
#include "../Player/Player.h"

#define MAX_COOL_TIME 30

enum EnemyStatus
{
	Patrol,
	AttackStandBy,
	AttackStart,
	AttackEnd
};

class EnemyBase :public CharaBase
{
protected:
	//パトロールする？
	bool isPatrol;

	//パトロール方向切り替え用のタイマー
	float patrolCounter;

	//状態遷移までの時間
	int statusChangeTime;

	//攻撃待機時間
	int attackWaitingTime;

	//衝突した?
	bool isClash;

	//自身の行動を禁止する？
	bool noMove;

	//エネミーの状態
	EnemyStatus enemyStatus;

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

	virtual void EnemyAnimation() = 0;

	//パトロール関数
	virtual void EnemyPatrol(Player* player) = 0;

	//攻撃範囲
	virtual void AttackCenser() = 0;

	//プレイヤーを発見するためのセンサー
	virtual void AttackRange() = 0;

	//攻撃準備
	virtual void AttackStandBy(Player* player) = 0;

	//攻撃開始
	virtual void AttackStart(Player* player) = 0;

	//攻撃終了
	virtual void AttackEnd() = 0;

	//プレイヤーとの当たり判定
	virtual void ClashToPlayer(Player* player) = 0;
};

