#include"LargeSword.h"
#include"../../Player/Player.h"
#include"../../Camera/Camera.h"

LargeSword::LargeSword()
{
	directionVector.x = 100.f;
	directionVector.y = 0.f;

	direction = 0;

	framCount = 0;

	isShow = false;
}

LargeSword::~LargeSword()
{

}

void LargeSword::Update(Player* player)
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
	if (framCount > STEAL_ATTACK_TIME)
	{
		framCount = 0;
		direction = 0;
		isShow = false;
		player->SetIsAttack(false);
	}

	screenLocation = Camera::ConvertScreenPosition(location);
}

void LargeSword::Draw() const
{
	if (isShow)DrawLineAA(screenLocation.x, screenLocation.y,
		screenLocation.x + directionVector.x, screenLocation.y + directionVector.y,
		0x00ffff, 1);
}

void LargeSword::Attack(const Player* player)
{
	isShow = true;

	//右に出す
	if (player->GetDirection().x > 0)
	{
		location.x = player->GetMaxLocation().x + LARGESWORD_DISTANCE;
	}
	//左に出す
	else
	{
		location.x = player->GetMinLocation().x - directionVector.x - LARGESWORD_DISTANCE;
	}

	location.y = player->GetCenterLocation().y;

	//まだ方向が決まってないなら
	if (direction == 0)
	{
		//プレイヤーの方向情報を保持する
		direction = (short)player->GetDirection().x;
	}
}

void LargeSword::Hit(CharaBase* enemy, Player* player)
{
	if (isShow)
	{
		if (enemy->GetIsShow() && !enemy->GetIsHit())
		{
			enemy->SetHp(enemy->GetHp() - player->GetDamage());
			enemy->SetIsHit(true);

			framCount = 0;
			direction = 0;
			isShow = false;
		}
	}
}
