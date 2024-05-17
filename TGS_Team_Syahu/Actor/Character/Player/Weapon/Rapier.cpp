#include "Rapier.h"
#include"../../Player/Player.h"
#include"../../../Camera/Camera.h"
#include"ResourceManager.h"

Rapier::Rapier()
{
	directionVector.x = RAPIER_LENGTH;
	directionVector.y = 0.f;

	damage = 0.f;

	direction = 0;

	framCount = 0;

	angle = 0.f;
	imageAngle = 0.f;
	dis = 0.f;
	length = 0.f;

	isShow = false;
	isHit = false;
	isUnable = false;
	stepFlg = false;
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
			imageAngle = DEGREE_TO_RADIAN(45.f);
			chara->SetMove({ RAPIER_MOVE ,chara->GetMove().y });
		}
		else
		{
			location.x = chara->GetMinLocation().x - WEAPON_DISTANCE;
			directionVector.x = -RAPIER_LENGTH;
			imageAngle = DEGREE_TO_RADIAN(-45.f);
			chara->SetMove({ -RAPIER_MOVE ,chara->GetMove().y });
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
		isHit = false;
		isUnable = false;
		stepFlg = true;
		chara->SetIsAttack(false);
	}

	damage = chara->GetDamage() + RAPIER_DAMAGE;
	location.y = chara->GetCenterLocation().y;
	screenLocation = Camera::ConvertScreenPosition(location);
}

void Rapier::Draw() const
{
	if (isShow)DrawLineAA(screenLocation.x, screenLocation.y,
		screenLocation.x + directionVector.x, screenLocation.y + directionVector.y,
		0x000000, 1);

	if (isShow)
	{
		if (direction > 0)
		{
			DrawRotaGraph2F(screenLocation.x, screenLocation.y, 0, 100,
				1, imageAngle, ResourceManager::GetImage("Weapon/rapier"), TRUE);
		}
		else
		{
			DrawRotaGraph2F(screenLocation.x, screenLocation.y, 100, 100,
				1, imageAngle, ResourceManager::GetImage("Weapon/rapier"), TRUE, TRUE);
		}
	}

}

void Rapier::Attack(const CharaBase* chara)
{
	isShow = true;

	//まだ方向が決まってないなら
	if (direction == 0)
	{
		//プレイヤーの方向情報を保持する
		direction = (short)chara->GetDirection().x;
	}

}

void Rapier::Hit(ObjectBase* target, const float damage)
{
	CharaBase* enemy = static_cast<CharaBase*>(target);

	if (isShow && !isUnable)
	{
		if (enemy->GetIsShow() && !enemy->GetIsHit())
		{
			enemy->SetHp(enemy->GetHp() - (damage + RAPIER_DAMAGE));
			enemy->SetKnockBackMove(RAPIER_KNOCKBACK);
			isHit = true;
			isUnable = true;
		}
	}
}
