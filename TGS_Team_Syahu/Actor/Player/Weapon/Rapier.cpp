#include "Rapier.h"
#include"../../Player/Player.h"
#include"../../Camera/Camera.h"

Rapier::Rapier()
{
	directionVector.x = RAPIER_LENGTH;
	directionVector.y = 0.f;

	direction = 0;

	framCount = 0;

	angle = 0.f;

	isShow = false;
}

Rapier::~Rapier()
{

}

void Rapier::Update(CharaBase* chara)
{
	if (isShow)
	{
		framCount++;
		//右に出す
		if (direction > 0)
		{
			location.x = chara->GetMaxLocation().x + WEAPON_DISTANCE;
			directionVector.x = RAPIER_LENGTH;
			chara->SetLocationX(chara->GetLocation().x + RAPIER_MOVE);
		}
		else
		{
			location.x = chara->GetMinLocation().x - WEAPON_DISTANCE;
			directionVector.x = -RAPIER_LENGTH;
			chara->SetLocationX(chara->GetLocation().x - RAPIER_MOVE);
		}
	}
	else
	{
		location = chara->GetCenterLocation();
	}

	//攻撃時間を超えたら
	if (framCount > RAPIER_ATTACK_TIME || chara->GetIsKnockBack())
	{
		framCount = 0;
		direction = 0;
		angle = 0.f;
		isShow = false;
		chara->SetIsAttack(false);
		chara->SetMove({ 0,0 });
	}

	location.y = chara->GetCenterLocation().y;
	screenLocation = Camera::ConvertScreenPosition(location);
}

void Rapier::Draw() const
{
	if (isShow)DrawLineAA(screenLocation.x, screenLocation.y,
		screenLocation.x + directionVector.x, screenLocation.y + directionVector.y,
		0x000000, 1);
}

void Rapier::Attack(const Player* player)
{
	isShow = true;

	//まだ方向が決まってないなら
	if (direction == 0)
	{
		//プレイヤーの方向情報を保持する
		direction = (short)player->GetDirection().x;
	}
}

void Rapier::Hit(CharaBase* enemy, const Player* player)
{
	if (isShow)
	{
		if (enemy->GetIsShow() && !enemy->GetIsHit())
		{
			enemy->SetHp(enemy->GetHp() - (player->GetDamage() + RAPIER_DAMAGE));
			enemy->SetIsHit(true);
		}
	}
}
