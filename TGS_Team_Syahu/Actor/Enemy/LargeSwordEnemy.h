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

	//徘徊状態から警戒状態に入る範囲
	void AttackRange()override;

	//攻撃に入る範囲
	void AttackCenser() override;

	//追跡を行うか？
	void AttackStandBy(Player* player) override;

	//攻撃を行うか？
	void AttackStart(Player* player) override;

	void AttackEnd() override;

	void ClashToPlayer(Player* player)override;
};

