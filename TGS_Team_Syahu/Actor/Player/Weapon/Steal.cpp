#include "Steal.h"
#include"../../../Scene/GameMain/GameMainScene.h"
#include"../../../Actor/Player/Player.h"

Steal::Steal()
{
	location = { 300.f,GROUND_LINE + radius };
	radius = 50.f;

	keepType = Ability::Empty;

	direction = 0;

	framCount = 0;

	isShow = false;

}

Steal::~Steal()
{

}

void Steal::Update(GameMainScene* object)
{
	if (isShow)
	{
		framCount++;

		Hit(object);
	}
	else
	{
		location = object->GetPlayer()->GetCenterLocation();
		screenLocation = object->GetCamera()->ConvertScreenPosition(location);
	}

	//攻撃時間を超えたら
	if (framCount > STEAL_ATTACK_TIME)
	{
		framCount = 0;
		direction = 0;
		isShow = false;
		object->GetPlayer()->SetIsAttack(false);
		object->GetPlayer()->SetIsSteal(false);
	}

	screenLocation = object->GetCamera()->ConvertScreenPosition(location);
}

void Steal::Draw() const
{
	if (isShow)DrawCircleAA(screenLocation.x, screenLocation.y, radius, 90, 0x00ff00, TRUE);
}

void Steal::Attack(const Player* player)
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
		//プレイヤーの方向情報を保持する
		direction = (short)player->GetDirection().x;
	}

}

void Steal::Hit(GameMainScene* object)
{
	if (isShow)
	{
		if (object->GetNormalEnemy() != nullptr &&
			HitCheck(object->GetNormalEnemy()) && object->GetNormalEnemy()->GetIsShow() &&
			!object->GetNormalEnemy()->GetIsHit())
		{
			StealAttack(object->GetNormalEnemy(), object->GetPlayer());

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