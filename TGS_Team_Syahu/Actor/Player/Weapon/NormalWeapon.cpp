#include"NormalWeapon.h"
#include"../../../Scene/GameMain/GameMainScene.h"
#include"../../../Actor/Player/Player.h"

NormalWeapon::NormalWeapon()
{
	location.x = 300.f;
	location.y = GROUND_LINE + radius;
	radius = 30.f;

	move.x = 0.f;
	move.y = 0.f;

	direction = 0;

	framCount = 0;

	angle = DEGREE_TO_RADIAN(20.f);
	gravityVelocity = 0.f;
	weaponWeight = 0.f;

	isShow = false;
}

NormalWeapon::~NormalWeapon()
{

}

void NormalWeapon::Update(Player* player)
{
	if (isShow)
	{
		framCount++;

		gravityVelocity += NORMAL_WEAPON_GRAVITY + weaponWeight;
	}
	else
	{
		location = player->GetCenterLocation();
	}

	//攻撃時間を超えたら
	if (framCount > NORMAL_WEAPON_ATTACK_TIME || location.y > GROUND_LINE)
	{
		framCount = 0;
		direction = 0;
		move.x = 0.f;
		move.y = 0.f;
		gravityVelocity = 0.f;
		weaponWeight = 0.f;
		isShow = false;
		player->SetIsAttack(false);
	}

	location.x += move.x;
	location.y += gravityVelocity;
	screenLocation = Camera::ConvertScreenPosition(location);
}

void NormalWeapon::Draw() const
{
	if (isShow)DrawCircleAA(screenLocation.x, screenLocation.y, radius, 90, 0xff0000, TRUE);
}

void NormalWeapon::Attack(const Player* player, const float weight)
{
	//出現させる
	isShow = true;

	//まだ方向が決まってないなら
	if (direction == 0)
	{
		direction = (short)player->GetDirection().x;
	}

	if (direction < 0)
	{
		move.x = -NORMAL_WEAPON_SPEED * cos(angle);
		location.x = player->GetMinLocation().x - radius;
	}
	else
	{
		move.x = NORMAL_WEAPON_SPEED * cos(angle);
		location.x = player->GetMaxLocation().x + radius;
	}

	move.y = NORMAL_WEAPON_SPEED * sin(angle);
	location.y = player->GetCenterLocation().y;

	weaponWeight = weight;
}

void NormalWeapon::Hit(CharaBase* enemy, Player* player)
{
	if (isShow)
	{
		if (enemy->GetIsShow() && !enemy->GetIsHit())
		{
			enemy->SetHp(enemy->GetHp() - player->GetDamage());
			enemy->SetIsHit(true);

			framCount = 0;
			direction = 0;
			move.x = 0.f;
			move.y = 0.f;
			gravityVelocity = 0.f;
			weaponWeight = 0.f;
			isShow = false;
		}
	}
}
