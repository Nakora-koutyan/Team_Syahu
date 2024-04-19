#pragma once
#include"../CharaBase.h"

#define ENEMY_SPEED 1.5f
#define RUSH_DIAMETER 2.f

#define ATTACK_FORM_RANGE_X 150
#define ATTACK_FORM_RANGE_Y 50

#define DIRECTION_LEFT 0
#define DIRECTION_RIGHT 1

class Player;

class NormalEnemy :public CharaBase
{
private:
	int enemy_color;

	int usual_color;	//通常色(確認用)
	int damage_color;	//ダメージを受けた時の色(確認用)
	int attack_color;	//攻撃時の色(確認用)

	int hp;				//自身のHP

	int direction;		//進行方向

	bool isChase;		//追跡

	Vector2D attack_range[2];
	Vector2D chase_censer[2];		//0:左センサー	1:右センサー

	int find_mark;		//プレイヤーを発見した際に出現する画像
	int angry_mark;		//プレイヤーに攻撃する際の画像

public:
	//コンストラクタ
	NormalEnemy();
	//デストラクタ
	~NormalEnemy();

	//初期化処理
	void Initialize();

	//更新処理
	void Update(Player* player);
	//描画更新処理
	void Draw()const;

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