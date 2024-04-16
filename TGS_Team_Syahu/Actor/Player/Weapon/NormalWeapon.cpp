#include"NormalWeapon.h"
#include"../../../Scene/GameMain/GameMainScene.h"
#include"../../../Actor/Player/Player.h"

NormalWeapon::NormalWeapon()
{
	location = { 300.f,GROUND_LINE + radius };
	radius = 30.f;

	direction = 0;

	framCount = 0;

	isShow = false;
}

NormalWeapon::~NormalWeapon()
{

}

void NormalWeapon::Update(GameMainScene* object)
{
	if (isShow)
	{
		framCount++;

		Hit(object);

		if (direction < 0)
		{
			location.x -= NORMAL_WEAPON_SPEED;
		}
		else
		{
			location.x += NORMAL_WEAPON_SPEED;
		}
	}
	else
	{
		location = object->GetPlayer()->GetCenterLocation();
		screenLocation = object->GetCamera()->ConvertScreenPosition(location);
	}

	//攻撃時間を超えたら
	if (framCount > NORMAL_WEAPON_ATTACK_TIME)
	{
		framCount = 0;
		direction = 0;
		isShow = false;
		object->GetPlayer()->SetIsAttack(false);
	}

	screenLocation = object->GetCamera()->ConvertScreenPosition(location);
}

void NormalWeapon::Draw() const
{
	if (isShow)DrawCircleAA(screenLocation.x, screenLocation.y, radius, 90, 0xff0000, TRUE);
}

void NormalWeapon::Attack(const Player* player)
{
	//出現させる
	isShow = true;

	//右に出す
	if (player->GetDirection().x > 0)
	{
		location.x = player->GetMaxLocation().x + radius;
	}
	//左に出す
	else
	{
		location.x = player->GetMinLocation().x - radius;
	}

	location.y = player->GetCenterLocation().y;

	//まだ方向が決まってないなら
	if (direction == 0)
	{
		direction =(short)player->GetDirection().x;
	}
}

void NormalWeapon::Hit(GameMainScene* object)
{
	if (isShow)
	{
		if (object->GetNormalEnemy() != nullptr &&
			HitCheck(object->GetNormalEnemy()) && object->GetNormalEnemy()->GetIsShow() &&
			!object->GetNormalEnemy()->GetIsHit())
		{
			object->GetNormalEnemy()->SetHp(object->GetNormalEnemy()->GetHp() - object->GetPlayer()->GetDamage());
			object->GetNormalEnemy()->SetIsHit(true);

			framCount = 0;
			direction = 0;
			isShow = false;
		}
	}
}
