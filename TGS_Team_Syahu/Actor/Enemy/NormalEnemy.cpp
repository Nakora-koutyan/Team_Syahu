#include "NormalEnemy.h"
#include "../../Scene/GameMain/GameMainScene.h"
#include "../Player/Player.h"

NormalEnemy::NormalEnemy():enemy_color(0),damage_color(0),attack_color(0),usual_color(0),attack_range{}
{

}

NormalEnemy::~NormalEnemy()
{
}

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
}

void NormalEnemy::Update(GameMainScene* object)
{
	screenLocation = object->GetCamera()->ConvertScreenPosition(location);

	//エネミーの移動
	Movement();
	//エネミーの攻撃範囲
	AttackRange();

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

void NormalEnemy::Draw() const
{
	DrawBoxAA
	(
		screenLocation.x, screenLocation.y,
		screenLocation.x + area.width, screenLocation.y + area.height,
		isHit ? attack_color : usual_color, TRUE, 1.0f
	);
}

void NormalEnemy::Movement()
{
	if(enemy_color == usual_color)
	{
		vector.x = MAX_ENEMY_SPEED;
	}
	else if (enemy_color == attack_color)
	{
		vector.x = (MAX_ENEMY_SPEED + 2);
	}

	location.x += vector.x;
}

void NormalEnemy::AttackRange()
{
	attack_range[0] = { GetMinLocation().x - 45.f,GetCenterLocation().y };
	attack_range[1] = { GetMaxLocation().x + 45.f , GetCenterLocation().y };
}