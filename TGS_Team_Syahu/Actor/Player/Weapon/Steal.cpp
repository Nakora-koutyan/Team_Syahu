#include "Steal.h"
#include"../../../Scene/GameMain/GameMainScene.h"
#include"../../../Actor/Player/Player.h"
#include"../../../Utility/common.h"

Steal::Steal()
{	
	keepType = Ability::Empty;

	direction = 0;

	framCount = 0;

	isShow = false;
}

Steal::~Steal()
{

}

void Steal::Update(Player* player)
{
	if (isShow)
	{
		framCount++;
	}
	else
	{
		location = player->GetCenterLocation();
	}

	//攻撃時間を超えたら
	if (framCount > STEAL_ATTACK_TIME || player->GetIsHit())
	{
		framCount = 0;
		direction = 0;
		isShow = false;
		player->SetIsAttack(false);
	}

	screenLocation = Camera::ConvertScreenPosition(location);
}

void Steal::Draw() const
{
	if (isShow)DrawLineAA(screenLocation.x, screenLocation.y,
		screenLocation.x + directionVector.x, screenLocation.y + directionVector.y,
		0x00ff00, 1);

}

void Steal::Attack(const Player* player, const float distance, const float direX, const float direY, const float locY)
{
	//出現させる
	isShow = true;

	//右に出す
	if (player->GetDirection().x > 0)
	{
		location.x = player->GetMaxLocation().x + distance;

		directionVector.x = direX;
	}
	//左に出す
	else
	{
		location.x = player->GetMinLocation().x - distance;
	
		directionVector.x = -direX;
	}		

	location.y = player->GetCenterLocation().y + locY;
	directionVector.y = -direY;

	//まだ方向が決まってないなら
	if (direction == 0)
	{
		//プレイヤーの方向情報を保持する
		direction = (short)player->GetDirection().x;
	}
}

void Steal::Hit(CharaBase* enemy, Player* player)
{
	if (isShow)
	{
		if (enemy->GetIsShow() && !enemy->GetIsHit())
		{
			StealAttack(enemy, player);

			framCount = 0;
			direction = 0;
		}
	}
}

void Steal::StealAttack(CharaBase* enemy, Player* player)
{
	enemy->SetHp(enemy->GetHp() - player->GetDamage());
	enemy->SetIsHit(true);

	//能力の種類が空ではないなら
	if (enemy->GetAbilityType() != Ability::Empty)
	{
		//敵の能力を奪う
		keepType = enemy->GetAbilityType();
		//敵は無能力になる
		enemy->SetAbilityType(Ability::Empty);
		
		player->SetStealFlg(true);
	}
}