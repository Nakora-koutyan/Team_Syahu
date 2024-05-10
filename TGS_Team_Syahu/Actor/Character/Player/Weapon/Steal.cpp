#include "Steal.h"
#include"../../../../Scene/GameMain/GameMainScene.h"
#include"../../../../Actor/Character/Player/Player.h"
#include"../../../../Utility/common.h"

Steal::Steal()
{	
	keepType = Weapon::Empty;

	direction = 0;

	framCount = 0;

	isShow = false;
}

Steal::~Steal()
{

}

void Steal::Update()
{
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

void Steal::Appearance(Player* player)
{
	if (isShow)
	{
		framCount++;
	}
	else
	{
		location = player->GetCenterLocation();
		sideClaw[0].SetLocation(player->GetCenterLocation());
		sideClaw[1].SetLocation(player->GetCenterLocation());

	}

	//攻撃時間を超えたら
	if (framCount > STEAL_ATTACK_TIME || player->GetIsKnockBack())
	{
		framCount = 0;
		direction = 0;
		isShow = false;
		player->SetIsAttack(false);
	}
}

void Steal::Attack(const Player* player)
{
	//出現させる
	isShow = true;

	//右に出す
	if (player->GetDirection().x > 0)
	{
		location.x = player->GetMaxLocation().x + (STEAL_DISTANCE - 20.f);
		sideClaw[0].SetLocationX(player->GetMaxLocation().x + (STEAL_DISTANCE - 10.f));
		sideClaw[1].SetLocationX(player->GetMaxLocation().x + (STEAL_DISTANCE + 10.f));

		directionVector.x = 100.f;
		sideClaw[0].SetDirectionVectorX(60.f);
		sideClaw[1].SetDirectionVectorX(70.f);
	}
	//左に出す
	else
	{
		location.x = player->GetMinLocation().x - (STEAL_DISTANCE - 20.f);
		sideClaw[0].SetLocationX(player->GetMinLocation().x - (STEAL_DISTANCE - 10.f));
		sideClaw[1].SetLocationX(player->GetMinLocation().x - (STEAL_DISTANCE + 10.f));
	
		directionVector.x = -100.f;
		sideClaw[0].SetDirectionVectorX(-60.f);
		sideClaw[1].SetDirectionVectorX(-70.f);
	}		

	location.y = player->GetCenterLocation().y + 30.f;
	sideClaw[0].SetLocationY(player->GetCenterLocation().y);
	sideClaw[1].SetLocationY(player->GetCenterLocation().y + 30.f);

	directionVector.y = -100.f;
	sideClaw[0].SetDirectionVectorY(-60.f);
	sideClaw[1].SetDirectionVectorY(-70.f);

	//まだ方向が決まってないなら
	if (direction == 0)
	{
		//プレイヤーの方向情報を保持する
		direction = (short)player->GetDirection().x;
	}
}

void Steal::Hit(ObjectBase* object, const float damage)
{
	CharaBase* enemy = static_cast<CharaBase*>(object);

	if (isShow)
	{
		if (isShow)
		{
			if (enemy->GetIsShow() && !enemy->GetIsHit())
			{
				enemy->SetHp(enemy->GetHp() - damage);
				enemy->SetIsHit(true);
				enemy->SetIsKnockBack(true);

				//能力の種類が空ではないなら
				if (enemy->GetWeaponType() != Weapon::Empty)
				{
					//敵の能力を奪う
					keepType = enemy->GetWeaponType();
					//敵は無能力になる
					//enemy->SetWeaponType(Weapon::Empty);
				}
			}
		}
	}

}
