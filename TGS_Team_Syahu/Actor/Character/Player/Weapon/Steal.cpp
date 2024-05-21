#include "Steal.h"
#include"../../../../Scene/GameMain/GameMainScene.h"
#include"../../../../Actor/Character/Player/Player.h"
#include"../../../../Utility/common.h"

Steal::Steal()
{	
	objectType = ObjectType::Weapon;

	keepType = Weapon::None;

	damage = 10.f;

	direction = 0;

	framCount = 0;

	isShow = false;
}

Steal::~Steal()
{

}

void Steal::Update(CharaBase* chara)
{
	if (isShow)
	{
		framCount++;
	}
	else
	{
		location = chara->GetCenterLocation();
		sideClaw[0].SetLocation(chara->GetCenterLocation());
		sideClaw[1].SetLocation(chara->GetCenterLocation());

	}

	//攻撃時間を超えたら
	if (framCount > STEAL_ATTACK_TIME || chara->GetIsKnockBack())
	{
		framCount = 0;
		direction = 0;
		isShow = false;
		chara->SetIsAttack(false);
	}
	screenLocation = Camera::ConvertScreenPosition(location);
	sideClaw[0].SetScreenLocation(Camera::ConvertScreenPosition(sideClaw[0].GetLocation()));
	sideClaw[1].SetScreenLocation(Camera::ConvertScreenPosition(sideClaw[1].GetLocation()));
}

void Steal::Draw() const
{
	if (isShow)
	{
		DrawLineAA(screenLocation.x, screenLocation.y,
			screenLocation.x + directionVector.x, screenLocation.y + directionVector.y,
			0x00ff00, 1);
		DrawLineAA(sideClaw[0].GetScreenLocation().x, sideClaw[0].GetScreenLocation().y,
			sideClaw[0].GetScreenLocation().x + sideClaw[0].GetDirectionVector().x,
			sideClaw[0].GetScreenLocation().y + sideClaw[0].GetDirectionVector().y,
			0x00ff00, 1);
		DrawLineAA(sideClaw[1].GetScreenLocation().x, sideClaw[1].GetScreenLocation().y,
			sideClaw[1].GetScreenLocation().x + sideClaw[1].GetDirectionVector().x,
			sideClaw[1].GetScreenLocation().y + sideClaw[1].GetDirectionVector().y,
			0x00ff00, 1);
	}
}

void Steal::Attack(const CharaBase* chara)
{
	//出現させる
	isShow = true;

	//右に出す
	if (chara->GetDirection().x > 0)
	{
		location.x = chara->GetMaxLocation().x + (STEAL_DISTANCE - 20.f);
		sideClaw[0].SetLocationX(chara->GetMaxLocation().x + (STEAL_DISTANCE - 10.f));
		sideClaw[1].SetLocationX(chara->GetMaxLocation().x + (STEAL_DISTANCE + 10.f));

		directionVector.x = 100.f;
		sideClaw[0].SetDirectionVectorX(60.f);
		sideClaw[1].SetDirectionVectorX(70.f);
	}
	//左に出す
	else
	{
		location.x = chara->GetMinLocation().x - (STEAL_DISTANCE - 20.f);
		sideClaw[0].SetLocationX(chara->GetMinLocation().x - (STEAL_DISTANCE - 10.f));
		sideClaw[1].SetLocationX(chara->GetMinLocation().x - (STEAL_DISTANCE + 10.f));
	
		directionVector.x = -100.f;
		sideClaw[0].SetDirectionVectorX(-60.f);
		sideClaw[1].SetDirectionVectorX(-70.f);
	}		

	location.y = chara->GetCenterLocation().y + 30.f;
	sideClaw[0].SetLocationY(chara->GetCenterLocation().y);
	sideClaw[1].SetLocationY(chara->GetCenterLocation().y + 30.f);

	directionVector.y = -100.f;
	sideClaw[0].SetDirectionVectorY(-60.f);
	sideClaw[1].SetDirectionVectorY(-70.f);

	//まだ方向が決まってないなら
	if (direction == 0)
	{
		//プレイヤーの方向情報を保持する
		direction = (short)chara->GetDirection().x;
	}
}

void Steal::Hit(ObjectBase* target, const float damage)
{
	CharaBase* chara = static_cast<CharaBase*>(target);

	if (isShow)
	{
		if (chara->GetIsShow() && !chara->GetIsHit())
		{
			//能力の種類が空ではないなら
			if (chara->GetWeaponType() != Weapon::None)
			{
				//敵の能力を奪う
				keepType = chara->GetWeaponType();

					//敵は無能力になる
					chara->SetWeaponType(Weapon::None);

				chara->SetHp(chara->GetHp() - (damage));
				chara->SetKnockBackMove(STEAL_KNOCKBACK);
			}
		}
	}

}
