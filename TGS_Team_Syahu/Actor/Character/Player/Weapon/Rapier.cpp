#include "Rapier.h"
#include"../../Player/Player.h"
#include"../../../Camera/Camera.h"
#include"../../../../ResourceManager/ResourceManager.h"

Rapier::Rapier()
{
	objectType = ObjectType::Weapon;

	directionVector.x = RAPIER_LENGTH;
	directionVector.y = 0.f;

	direction = 0;

	framCount = 0;
	chargeTime = 0;

	angle = 0.f;
	imageAngle = 0.f;
	dis = 0.f;
	length = 0.f;

	isShow = false;
	isHit = false;
	isUnable = false;
	stepFlg = false;
	isAirAttack = false;
}

Rapier::~Rapier()
{

}

void Rapier::Update(CharaBase* chara)
{
	//地上での攻撃なら
	if (isShow && !isAirAttack)
	{
		chargeTime++;
		if (chargeTime > RAPIER_CHARGE_TIME)
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
	}
	//空中攻撃なら
	else if (isAirAttack)
	{
		directionVector.x = 0;
		directionVector.y = RAPIER_LENGTH;
		chara->SetMove({ chara->GetMove().x , RAPIER_AIR_MOVE });
		chara->SetInvincibleFlg(true);
		//右に出す
		if (direction > 0)
		{
			location.x = chara->GetMaxLocation().x + WEAPON_DISTANCE;
			imageAngle = DEGREE_TO_RADIAN(135.f);
		}
		else
		{
			location.x = chara->GetMinLocation().x - WEAPON_DISTANCE;
			imageAngle = DEGREE_TO_RADIAN(-135.f);
		}
	}
	else
	{
		location = chara->GetCenterLocation();
	}

	//地上攻撃の時間を超えたら
	if ((framCount > RAPIER_ATTACK_TIME || chara->GetIsKnockBack()) && !isAirAttack)
	{
		framCount = 0;
		chargeTime = 0;
		direction = 0;
		angle = 0.f;
		isShow = false;
		isHit = false;
		isUnable = false;
		stepFlg = true;
		chara->SetIsAttack(false);
	}
	//空中攻撃が地面に着地したら
	else if (isAirAttack && !chara->GetIsAir())
	{
		framCount = 0;
		direction = 0;
		angle = 0.f;
		directionVector.x = 0.f;
		directionVector.y = 0.f;
		isShow = false;
		isHit = false;
		isUnable = false;
		stepFlg = true;
		isAirAttack = false;
		chara->SetIsAttack(false);
		chara->SetInvincibleFlg(false);
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

	//右に出す
	if (direction > 0)
	{
		location.x = chara->GetMaxLocation().x + WEAPON_DISTANCE;
		directionVector.x = RAPIER_LENGTH;
		imageAngle = DEGREE_TO_RADIAN(45.f);
	}
	else
	{
		location.x = chara->GetMinLocation().x - WEAPON_DISTANCE;
		directionVector.x = -RAPIER_LENGTH;
		imageAngle = DEGREE_TO_RADIAN(-45.f);
	}

	if (chara->GetIsAir())
	{
		isAirAttack = true;
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
			isHit = true;
			isUnable = true;
			if (isAirAttack)
			{
				enemy->SetKnockBackMove(RAPIER_AIR_ATTAK_KNOCKBACK);
			}
			else
			{
				enemy->SetKnockBackMove(RAPIER_KNOCKBACK);
			}
		}
	}
}
