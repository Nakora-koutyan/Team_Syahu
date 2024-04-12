#pragma once
#include"../CharaBase.h"

#define ENEMY_SPEED -1.5
#define ATTACK_FORM_RANGE_X 150
#define ATTACK_FORM_RANGE_Y 50

class NormalEnemy :public CharaBase
{
private:
	int enemy_color;

	int usual_color;
	int damage_color;
	int attack_color;

	Vector2D attack_range[2];
	Vector2D attack_censer[2];

public:
	//コンストラクタ
	NormalEnemy();

	//デストラクタ
	~NormalEnemy();

	//初期化処理
	void Initialize();

	//更新処理
	void Update(GameMainScene* object)override;

	//描画更新処理
	void Draw()const override;

	//パトロール関数
	void EnemyPatrol(GameMainScene* player);

	//攻撃範囲
	void AttackRange();

	//プレイヤーを発見するためのセンサー
	void DiscoveryPlayer();

	//プレイヤーにダメージを与える処理
	float GiveDamage(GameMainScene* player_hp);
};