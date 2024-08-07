#pragma once
#include "EnemyBase.h"

class LargeSwordEnemy :public EnemyBase
{
private:

	BoxCollision* largeSwordCollisionBox;

	int largeSwordEnemyImage[115];		//敵画像
	int largeSwordEnemyImageNumber;		//画像番号

	int weaponNoneEnemyImage[115];		//敵画像配列
	int weaponNoneEnemyImageNumber;		//画像番号

	int animInterval;					//画像のインターバル
	bool animCountDown;					//画像インターバルのカウントダウン
	bool animTurnFlg;					//アニメーションを左右反転する？(yes：true,no：false)

	float distance;						//プレイヤーとエネミーとの距離
	int restTime;						//回転時の休憩

	int attackCountDown;				//攻撃までのカウントダウン

	int largeSwordAttackTime;			//大剣時の攻撃時間
	int rushAttackTime;					//攻撃時間

	bool canAttack;						//攻撃できる？
	bool didAttack;						//攻撃をした？

	bool closeToPlayer;					//プレイヤーに近い？

	int attackChargeTime;					//攻撃エネルギーを貯める？

	float correctLocX;					//画像のX座標の修正用変数

	bool once;							//LargeSwordのAttack関数を一度の攻撃で一回だけ呼ぶためのフラグ

	int attackEndCounter;				//attackEnd時に呼ばれるカウンター変数

	int largeSwordAttackCoolTime;		//攻撃終了後のクールタイム

public:
	//コンストラクタ
	LargeSwordEnemy(float x, float y);
	//デストラクタ
	~LargeSwordEnemy();

	//初期化処理
	void Initialize()override;

	//終了処理
	void Finalize()override;

	//描画以外の更新
	void Update()override;
	//描画に関する更新
	void Draw()const override;

	//プレイヤーを見つけた？
	void FindPlayer(const Player* player)override;

public:
	//largeSwordCollisionBoxを取得
	BoxCollision* GetLargeSwordCollisionBox()const { return largeSwordCollisionBox; }

	//武器のヒット処理
	void HitWeapon(ObjectBase* object)override;

protected:
	//攻撃範囲関数
	void AttackRange()override;

	//攻撃センサー
	void AttackCenser();

	//エネミーのアニメーション制御関数
	void EnemyAnimationManager() override;

	//パトロール関数
	void EnemyPatrol() override;

	//プレイヤーに急接近する
	void SuddenApproachToPlayer(const Player* player);

protected:
	//武器ありの場合に呼び出される関数
	//攻撃準備
	void AttackStandBy() override;

	//攻撃開始
	void AttackStart() override;

	//攻撃終了
	void AttackEnd() override;

	//死亡時
	void Death() override;

	//ダメージを受けた時
	void Damage() override;

protected:
	//ステータスアニメーション用関数
	//パトロールアニメーション
	void LargeSwordPatrolAnim();
	void WeaponNonePatrolAnim();
	
	//攻撃準備アニメーション
	void LargeSwordAttackStandByAnim();
	void WeaponNoneAttackStandByAnim();

	//攻撃開始アニメーション
	void LargeSwordAttackStartAnim();
	void WeaponNoneAttackStartAnim();

	//攻撃終了
	void LargeSwordAttackEndAnim();
	void WeaponNoneAttackEndAnim();

	//死亡時のアニメーション
	void LargeSwordEnemyDeathAnim();
	void WeaponNoneEnemyDeathAnim();

	//ダメージを受けた際のアニメーション
	void LargeSwordEnemyDamageAnim();
	void WeaponNoneEnemyDamageAnim();
};

