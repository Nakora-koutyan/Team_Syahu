#include "NormalEnemy.h"
#include "../../Scene/GameMain/GameMainScene.h"
#include "../Player/Player.h"

NormalEnemy::NormalEnemy():enemy_color(0),damage_color(0),attack_color(0),usual_color(0)
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
	
	area = { 70.f,70.f };
	location = { 1200,GROUND_LINE - area.height };
}

void NormalEnemy::Update(GameMainScene* object)
{
	/*screenLocation = object->GetCamera()->ConvertScreenPosition(location);

	if (HitCheck(object->GetPlayer()))
	{
		
	}

	Movement(object->GetPlayer());*/
}

void NormalEnemy::Draw() const
{
	DrawBoxAA
	(
		screenLocation.x, screenLocation.y,
		screenLocation.x + area.width + 2, screenLocation.y + area.height,
		enemy_color, TRUE, 1.0f
	);
}

void NormalEnemy::Movement()
{
	/*vector.x = MAX_ENEMY_SPEED;

	location.x += vector.x;
	if (
		(player->GetMinLocation().x - 150) < location.x
		&& (player->GetMinLocation().y - 50) < location.y
		&& (player->GetMaxLocation().x + 150) > location.x
		&& (player->GetMaxLocation().y + 50) > location.y
		)
	{
		enemy_color = attack_color;
	}
	else
	{
		enemy_color = usual_color;
	}*/
}