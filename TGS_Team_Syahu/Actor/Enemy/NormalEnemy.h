#pragma once
#include"../CharaBase.h"

#define ENEMY_SPEED -1.5
#define ATTACK_FORM_RANGE_X 150
#define ATTACK_FORM_RANGE_Y 50

#define GIVE_DAMAGE		10.f			//プレイヤーへ与えるダメ―ジad

class NormalEnemy :public CharaBase
{
private:
	int enemy_color;

	int usual_color;	//通常色(確認用)
	int damage_color;	//ダメージを受けた時の色(確認用)
	int attack_color;	//攻撃時の色(確認用)

	int hp;				//自身のHP
	int find_mark;		//プレイヤーを発見した際に出現する画像

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