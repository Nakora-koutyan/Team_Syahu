#pragma once
#include "EnemyBase.h"

class LargeSwordEnemy :public EnemyBase
{
private:
	int enemyImage[115];	//敵画像
	int enemyNumber;		//画像番号
	int animInterval;		//画像のインターバル
	bool animCountDown;		//画像インターバルのカウントダウン
	bool animTurnFlg;		//アニメーションを左右反転する？(yes：true,no：false)

	float distance;			//プレイヤーとエネミーとの距離
	int restTime;			//回転時の休憩

	int attackCountDown;	//攻撃までのカウントダウン
	bool didAttack;			//攻撃をした？

public:
	//コンストラクタ
	LargeSwordEnemy();
	//デストラクタ
	~LargeSwordEnemy();

	//初期化処理
	void Initialize();

	//描画以外の更新
	void Update(Player* player);
	//描画に関する更新
	void Draw()const;

protected:
	//エネミーのアニメーション制御関数
	void EnemyAnimation() override;

	//パトロール関数
	void EnemyPatrol(Player* player) override;

	//プレイヤーに急接近する
	void SuddenApproachToPlayer(Player* player);

	//攻撃準備に入るか？
	void AttackStandBy(Player* player) override;

	//攻撃を行うか？
	void AttackStart(Player* player) override;

	//攻撃の終了
	void AttackEnd() override;

	void ReceiveDamage(Player* player)override;

	void Hit(Player* chara)override;
};
