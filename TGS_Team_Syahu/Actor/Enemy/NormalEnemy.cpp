#include "NormalEnemy.h"
#include "../../Scene/GameMain/GameMainScene.h"
#include "../Player/Player.h"

//コンストラクタ
NormalEnemy::NormalEnemy():enemy_color(0),damage_color(0),attack_color(0),usual_color(0),
attack_range{},chase_censer{},hp(100),find_mark(NULL),angry_mark(NULL),direction(0),isChase(false)
{
}

//デストラクタ
NormalEnemy::~NormalEnemy()
{
}

//初期化処理
void NormalEnemy::Initialize()
{
	//仮の色付け
	//通常のカラー
	usual_color = GetColor(0, 255, 0);
	//ダメージを受けた時の色
	damage_color = GetColor(255, 0, 0);
	//攻撃をするときの色
	attack_color = GetColor(0, 0, 255);

	//体の色の情報を受け取る変数
	enemy_color = usual_color;
	
	//サイズ{ x , y }
	area = { 90.f,90.f };
	//表示座標{ x , y }
	location = { 1200,GROUND_LINE - area.height };
	//キャラクターの能力
	abilityType = Ability::Slashing;	//かり

	//攻撃範囲
	attack_range[0] = { GetCenterLocation() };
	attack_range[1] = { GetCenterLocation() };

	//プレイヤーを追跡する範囲
	chase_censer[0] = { GetCenterLocation() };
	chase_censer[1] = { GetCenterLocation() };

	//プレイヤーを見つけた際の座標
	find_mark = LoadGraph("Resource/Images/Exclamation.png");
	angry_mark = LoadGraph("Resource/images/Angry.png");

	//体の向き
	direction = DIRECTION_LEFT;

	//体力
	hp = 100;

	/*　状態　*/
	//表示するか?
	isShow = true;
}

//描画以外の内容を更新
void NormalEnemy::Update(GameMainScene* object)
{
	//現在の座標をスクリーン座標へ変換
	screenLocation = object->GetCamera()->ConvertScreenPosition(location);
	DamageInterval(60);

	//エネミーの移動
	EnemyPatrol(object);

	//エネミーの攻撃範囲
	AttackRange();

	//プレイヤーを検知するセンサー
	ChaseRange();

	//プレイヤーへの追跡
	ChaseToPlayer(object);

	//プレイヤーへの攻撃
	AttackToPlayer(object);
}

//描画に関する更新
void NormalEnemy::Draw() const
{
	//エネミー表示
	DrawBoxAA
	(
		screenLocation.x, screenLocation.y,
		screenLocation.x + area.width, screenLocation.y + area.height,
		isAttack ? attack_color : isHit ? 0xff0000 : usual_color, TRUE, 1.0f
	);
	DrawFormatStringF(500.f, 550.f, GetColor(255, 0, 255), "%f", GetMinLocation().x);
	
	//プレイヤーを発見した場合、「！」を表示する
	if (isChase == true)
	{
		if (direction == DIRECTION_LEFT)
		{
			DrawGraphF
			(
				screenLocation.x + 75, screenLocation.y - 30,
				isAttack ? angry_mark:find_mark, TRUE
			);
		}
		if (direction == DIRECTION_RIGHT)
		{
			DrawGraphF
			(
				screenLocation.x - 25, screenLocation.y - 30,
				isAttack ? angry_mark : find_mark, TRUE
			);
		}
	}
}

//プレイヤーのいる方向に向かう
void NormalEnemy::EnemyPatrol(GameMainScene* player)
{
	if (player->GetPlayer()->GetCenterLocation().x < location.x)
	{
		if (isChase == true)
		{
			vector.x = (ENEMY_SPEED * 1.5);
		}
		else
		{
			vector.x = ENEMY_SPEED;
		}
		direction = DIRECTION_LEFT;
	}
	else if (player->GetPlayer()->GetCenterLocation().x > location.x)
	{
		if (isChase == true)
		{
			vector.x =  -(ENEMY_SPEED * 1.5);
		}
		else
		{
			vector.x = -ENEMY_SPEED;
		}
		direction = DIRECTION_RIGHT;
	}

	//パリィ状態でなければ進行する
	if (!player->GetPlayer()->GetParryFlg())
	{
		location.x += vector.x;
	}
}

//攻撃範囲
void NormalEnemy::AttackRange()
{
	attack_range[0] = { GetMinLocation().x - 45.f,GetCenterLocation().y };
	attack_range[1] = { GetMaxLocation().x + 45.f , GetCenterLocation().y };
}

//戦闘態勢に入る範囲
void NormalEnemy::ChaseRange()
{
	chase_censer[0] = { GetMinLocation().x - 500.f,GetCenterLocation().y };
	chase_censer[1] = { GetMaxLocation().x + 500.f,GetCenterLocation().y };
}

void NormalEnemy:: ChaseToPlayer(GameMainScene* object)
{
	//プレイヤーが追跡範囲内にいるかのチェック
	if (chase_censer[0].x < object->GetPlayer()->GetMaxLocation().x &&
		chase_censer[1].x > object->GetPlayer()->GetMinLocation().x)
	{
		isChase = true;
	}
	else
	{
		isChase = false;
	}
}

void NormalEnemy::AttackToPlayer(GameMainScene* object)
{
	//プレイヤーが攻撃範囲にいるかのチェック
	if (attack_range[0].x < object->GetPlayer()->GetMaxLocation().x &&
		attack_range[1].x > object->GetPlayer()->GetMinLocation().x)
	{
		isAttack = true;
	}
	else
	{
		isAttack = false;
	}
}