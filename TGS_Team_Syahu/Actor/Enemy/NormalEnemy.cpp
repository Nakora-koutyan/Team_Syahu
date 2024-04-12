#include "NormalEnemy.h"
#include "../../Scene/GameMain/GameMainScene.h"
#include "../Player/Player.h"

//コンストラクタ
NormalEnemy::NormalEnemy():enemy_color(0),damage_color(0),attack_color(0),usual_color(0),attack_range{},attack_censer{}
{

}

//デストラクタ
NormalEnemy::~NormalEnemy()
{
}

//初期化処理
void NormalEnemy::Initialize()
{
	damage_color = GetColor(255, 0, 0);
	attack_color = GetColor(0, 0, 255);
	usual_color = GetColor(0, 255, 0);

	enemy_color = usual_color;
	
	area = { 90.f,90.f };
	location = { 1200,GROUND_LINE - area.height };

	attack_range[0] = { GetCenterLocation() };
	attack_range[1] = { GetCenterLocation() };

	attack_censer[0] = { GetCenterLocation() };
	attack_censer[1] = { GetCenterLocation() };
}

//描画以外の内容を更新
void NormalEnemy::Update(GameMainScene* object)
{
	screenLocation = object->GetCamera()->ConvertScreenPosition(location);

	//エネミーの移動
	EnemyPatrol(object);

	//エネミーの攻撃範囲
	AttackRange();

	//プレイヤーを検知するセンサー
	DiscoveryPlayer();

	if (attack_range[0].x < object->GetPlayer()->GetMaxLocation().x &&
		attack_range[1].x > object->GetPlayer()->GetMinLocation().x)
	{
		isHit = true;
	}
	else
	{
		isHit = false;
	}
}

//描画に関する更新
void NormalEnemy::Draw() const
{
	DrawBoxAA
	(
		screenLocation.x, screenLocation.y,
		screenLocation.x + area.width, screenLocation.y + area.height,
		isHit ? attack_color : usual_color, TRUE, 1.0f
	);
}

//プレイヤーのいる方向に向かう
void NormalEnemy::EnemyPatrol(GameMainScene* player)
{
	if (player->GetPlayer()->GetCenterLocation().x < screenLocation.x)
	{
		vector.x = ENEMY_SPEED;
	}
	else if (player->GetPlayer()->GetCenterLocation().x >= screenLocation.x)
	{
		vector.x = -ENEMY_SPEED;
	}

	location.x += vector.x;
}

//攻撃範囲
void NormalEnemy::AttackRange()
{
	attack_range[0] = { GetMinLocation().x - 45.f,GetCenterLocation().y };
	attack_range[1] = { GetMaxLocation().x + 45.f , GetCenterLocation().y };
}

//戦闘態勢に入る範囲
void NormalEnemy::DiscoveryPlayer()
{
	attack_censer[0] = { GetMinLocation().x - 100.f,GetCenterLocation().y };
	attack_censer[1] = { GetMaxLocation().x + 100.f,GetCenterLocation().y };
}

float NormalEnemy::GiveDamage(GameMainScene* player_hp)
{
	if (isHit == true)
	{

	}
}