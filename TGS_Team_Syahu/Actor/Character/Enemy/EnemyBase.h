#pragma once
#include "../CharaBase.h"
#include "../Player/Player.h"

#define MAX_COOL_TIME 90
#define MAX_WAITING_TIME 60
#define MAX_ATTACK_TIME 90

#define DIRECTION_LEFT -1				//左向き
#define DIRECTION_RIGHT 1				//右向き


enum EnemyStatus
{
	Patrol,				//パトロール
	AttackStandBy,		//攻撃準備
	AttackStart,		//攻撃開始
	AttackEnd,			//攻撃終了
	Death				//死亡時
};

enum class EnemyType
{
	None = 0,				//武器無し
	LargeSwordEnemy,		//大剣持ち
	DaggerEnemy,			//短剣持ち
	RapierEnemy				//レイピア持ち
};

class EnemyBase :public CharaBase
{
protected:
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

	//エネミーの種類
	EnemyType enemyType;

	bool isBlink;					//点滅する？

	int blinkCounter;				//点滅処理専用のカウンター

	int enemyAlpha;

	bool isFind;					//見つけた？

	Vector2D attackCenser[2];		//0:左センサー	1:右センサー
	Vector2D attackRange[2];		//0:左センサー	1:右センサー

	bool signToAttack;					//攻撃の時に呼ばれる変数

public:
	//コンストラクタ
	EnemyBase();
	//デストラクタ
	~EnemyBase();

	//初期化処理
	void Initialize()override;

	//終了処理
	void Finalize()override;

	//更新処理
	void Update();

	//描画処理
	void Draw(Player* player);

	//ヒット処理
	void Hit(ObjectBase* target, const float damage)override;

	//プレイヤーを見つけた？
	virtual void FindPlayer(const Player* player) = 0;

	void DontCrossBorder();

public:
	//エネミーの種類を取得
	EnemyType GetEnemyType()const { return enemyType; }

	bool GetSignToAttack()const { return signToAttack; }

	//武器のヒット処理
	virtual void HitWeapon(ObjectBase* object) = 0;

protected:
	virtual void AttackRange() = 0;

	virtual void EnemyAnimationManager() = 0;

	//パトロール関数
	virtual void EnemyPatrol() = 0;

	//攻撃準備
	virtual void AttackStandBy() = 0;

	//攻撃開始
	virtual void AttackStart() = 0;

	//攻撃終了
	virtual void AttackEnd() = 0;

	//死亡時に呼び出される関数
	virtual void Death() = 0;
};

