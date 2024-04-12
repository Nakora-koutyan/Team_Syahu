#include"NormalWeapon.h"
#include"../../../Scene/GameMain/GameMainScene.h"
#include"../../../Actor/Player/Player.h"

NormalWeapon::NormalWeapon()
{
	location = { 300.f,GROUND_LINE + radius };
	radius = 30.f;

	framCount = 0;
}

NormalWeapon::~NormalWeapon()
{

}

void NormalWeapon::Update(GameMainScene* object)
{
	if (object->GetPlayer()->GetIsAttack())
	{
		framCount++;
	}
	else
	{
		location = object->GetPlayer()->GetLocation();
		screenLocation = object->GetCamera()->ConvertScreenPosition(location);
	}

	if (framCount > NORMAL_WEAPON_ATTACK_TIME)
	{
		object->GetPlayer()->SetIsAttack(false);
		framCount = 0;
	}

	screenLocation = object->GetCamera()->ConvertScreenPosition(location);
}

void NormalWeapon::Draw() const
{
	DrawCircleAA(screenLocation.x, screenLocation.y, radius, 90, 0xff0000, TRUE);
}

void NormalWeapon::Attack(const Player* player)
{
	if (player->GetDirection().x > 0)
	{
		location.x = player->GetMaxLocation().x + radius;
	}
	else
	{
		location.x = player->GetMinLocation().x - radius;
	}

	location.y = player->GetCenterLocation().y;
}
