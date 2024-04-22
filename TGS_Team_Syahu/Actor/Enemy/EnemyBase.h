#pragma once
#include "../CharaBase.h"
#include "../Player/Player.h"

#define MAX_COOL_TIME 40
#define MAX_ATTACK_TIME 50

class EnemyBase :public CharaBase
{
protected:
	//追跡する？
	bool isChase;

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

public:
	//更新処理
	void Update(Player* player);

	//描画処理
	void Draw(Player* player);

	//パトロール関数
	void EnemyPatrol(Player* player);
	//攻撃範囲
	void AttackRange();

	//プレイヤーを発見するためのセンサー
	void ChaseRange();

	//追跡を行うか？
	void ChaseToPlayer(Player* player);

	//攻撃を行うか？
	void AttackToPlayer(Player* player);
};

