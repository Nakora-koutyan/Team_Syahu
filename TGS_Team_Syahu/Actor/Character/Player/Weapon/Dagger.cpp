#include "Dagger.h"
#include"../../Player/Player.h"
#include"../../../Camera/Camera.h"

Dagger::Dagger()
{
	directionVector.x = DAGGER_LENGTH;
	directionVector.y = 0.f;

	direction = 0;

	framCount = 0;

	angle = 0.f;

	isShow = false;
}

Dagger::~Dagger()
{

}

void Dagger::Update()
{
	screenLocation = Camera::ConvertScreenPosition(location);
}

void Dagger::Draw() const
{
	if (isShow)DrawLineAA(screenLocation.x, screenLocation.y,
		screenLocation.x + directionVector.x, screenLocation.y + directionVector.y,
		0x000000, 1);
}

void Dagger::Appearance(CharaBase* chara)
{
	if (isShow)
	{
		framCount++;
		directionVector.x = directionVector.x * cos(DEGREE_TO_RADIAN(angle)) - directionVector.y * sin(DEGREE_TO_RADIAN(angle));
		directionVector.y = directionVector.x * sin(DEGREE_TO_RADIAN(angle)) + directionVector.y * cos(DEGREE_TO_RADIAN(angle));

		//右に出す
		if (direction > 0)
		{
			location.x = chara->GetMaxLocation().x + WEAPON_DISTANCE;
		}
		//左に出す
		else
		{
			location.x = chara->GetMinLocation().x - WEAPON_DISTANCE;
		}
	}
	else
	{
		location = chara->GetCenterLocation();
	}

	//攻撃時間を超えたら
	if (framCount > DAGGER_ATTACK_TIME || chara->GetIsKnockBack())
	{
		framCount = 0;
		direction = 0;
		angle = 0.f;
		isShow = false;
		chara->SetIsAttack(false);
	}

	location.y = chara->GetCenterLocation().y;
}

void Dagger::Attack(const Player* player)
{
	isShow = true;

	//まだ方向が決まってないなら
	if (direction == 0)
	{
		//プレイヤーの方向情報を保持する
		direction = (short)player->GetDirection().x;
	}

	//右に出す
	if (direction > 0)
	{
		directionVector.x = DAGGER_LENGTH;
		angle = DAGGER_ANGLE;
	}
	//左に出す
	else
	{
		directionVector.x = -DAGGER_LENGTH;
		angle = -DAGGER_ANGLE;
	}

	directionVector.y = -40.f;
}

void Dagger::Hit(ObjectBase* object, const float damage)
{
	CharaBase* enemy = static_cast<CharaBase*>(object);

	if (isShow)
	{
		if (enemy->GetIsShow() && !enemy->GetIsHit())
		{
			enemy->SetHp(enemy->GetHp() - (damage + DAGGER_DAMAGE));
			enemy->SetIsHit(true);
			enemy->SetIsKnockBack(true);
		}
	}
}