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
	
	area = { 135.f,135.f };
	location = { 1200,GROUND_LINE - area.height };
}

void NormalEnemy::Update(GameMainScene* object)
{
	screenLocation = object->GetCamera()->ConvertScreenPosition(location);

	if (HitCheck(object->GetPlayer()))
	{
		isHit = true;
	}
	else
	{
		isHit = false;
	}

	Movement();
}

void NormalEnemy::Draw() const
{
	DrawBoxAA
	(
		screenLocation.x, screenLocation.y,
		screenLocation.x + area.width, screenLocation.y + area.height,
		0xff00ff, FALSE, 1.0f
	);
	DrawBoxAA
	(
		screenLocation.x + ( area.width / 3.5f ), screenLocation.y + ( area.height / 3.5f),
		screenLocation.x + area.width, screenLocation.y + area.height,
		isHit ? attack_color : usual_color, TRUE, 1.0f
	);
}

void NormalEnemy::Movement()
{
	vector.x = MAX_ENEMY_SPEED;

	location.x += vector.x;
}