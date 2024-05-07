#pragma once
#include "../CharaBase.h"
#include "../Player/Player.h"

#define MAX_COOL_TIME 50

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

	int markStatus;		//符号の状態遷移
	int findMark;		//プレイヤーを発見した際に出現する画像
	int angryMark;		//プレイヤーに攻撃する際の画像

	bool isBlink;

	int blinkCounter;

	int enemyAlpha;

	int colorRed;
	int colorGreen;
	int colorBlue;

	int hp;				//自身のHP

	int direction;		//進行方向

	Vector2D attackCenser[2];		//0:左センサー	1:右センサー
	Vector2D attackRange[2];		//0:左センサー	1:右センサー

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

	//攻撃準備範囲
	virtual void AttackCenser() = 0;

	virtual void AttackRange() = 0;

	//攻撃準備
	virtual void AttackStandBy(Player* player) = 0;

	//攻撃開始
	virtual void AttackStart(Player* player) = 0;

	//攻撃終了
	virtual void AttackEnd() = 0;

	//プレイヤーとの当たり判定
	virtual void ReceiveDamage(Player* player) = 0;

	//ヒット処理
	virtual void Hit(Player* player) = 0;
};

