#pragma once
#include"EnemyBase.h"

#define NORMAL_WALK_SPEED 0.5f			//徘徊時のスピード
#define ATTACK_SPEED 9.f				//攻撃時のスピード

class Player;

class NormalEnemy :public EnemyBase
{
private:
	int enemyImage[6];			//敵画像
	int enemyDeathImage[11];	//死亡時の画像
	int enemyNumber;			//画像番号

	int animInterval;			//画像のインターバル
	bool animCountDown;			//画像インターバルのカウントダウン
	bool animTurnFlg;			//アニメーションを左右反転する？(yes：true,no：false)

	int attackTime;				//攻撃時間

	int CountChangeCounter;

	bool isFirst;				//初めて死亡処理に入った時に使われるbool変数
	bool onlyOnce;				//死亡時に一度だけ呼ばれる変数

	float locXCorrect;			//画像のX座標の補正用変数
	float locYCorrect;			//画像のY座標の補正用変数

	Rapier* rapier;				//レイピアを呼び出す

public:
	//コンストラクタ
	NormalEnemy(float x, float y);
	//デストラクタ
	~NormalEnemy();

	//初期化処理
	void Initialize()override;
	//終了処理
	void Finalize()override;

	//更新処理
	void Update()override;
	//描画更新処理
	void Draw()const override;

public:

	Rapier* GetRapier()const { return rapier; }

	//プレイヤーを見つけた？
	void FindPlayer(const Player* player)override;

	void HitWeapon(ObjectBase* object)override;

private:
	//攻撃範囲関数
	void AttackRange()override;

	//パトロール関数
	void EnemyPatrol() override;

	//追跡を行うか？
	void AttackStandBy() override;

	//攻撃を行うか？
	void AttackStart() override;

	//攻撃終了
	void AttackEnd() override;

	//死亡処理
	void Death() override;

	//ダメージを受けた時
	void Damage()override;

private:
	//エネミーのアニメーション制御関数
	void EnemyAnimationManager() override;

	void PatrolAnim();
	
	void AttackStandByAnim();

	void NormalEnemyAttackStartAnim();
	void WeaponNoneAttackStartAnim();

	void AttackEndAnim();

	void NormalEnemyDeathAnim();

	void NormalEnemyDamageAnim();
};