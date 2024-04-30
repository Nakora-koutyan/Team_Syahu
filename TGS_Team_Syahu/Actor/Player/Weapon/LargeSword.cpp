#include"LargeSword.h"
#include"../../Player/Player.h"
#include"../../Camera/Camera.h"

LargeSword::LargeSword()
{
	directionVector.x = LARGRSWORD_LENGTH;
	directionVector.y = -100.f;

	direction = 0;

	framCount = 0;

	angle = 0.f;

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
		directionVector.x = directionVector.x * cos(DEGREE_TO_RADIAN(angle)) - directionVector.y * sin(DEGREE_TO_RADIAN(angle));
		directionVector.y = directionVector.x * sin(DEGREE_TO_RADIAN(angle)) + directionVector.y * cos(DEGREE_TO_RADIAN(angle));
	
		//右に出す
		if (direction > 0)
		{
			location.x = player->GetMaxLocation().x + LARGESWORD_DISTANCE;
		}
		//左に出す
		else
		{
			location.x = player->GetMinLocation().x - LARGESWORD_DISTANCE;
		}
	}
	else
	{
		location = player->GetCenterLocation();
	}

	//攻撃時間を超えたら
	if (framCount > LARGESWORD_ATTACK_TIME || player->GetIsKnockBack())
	{
		framCount = 0;
		direction = 0;
		angle = 0.f;
		isShow = false;
		player->SetIsAttack(false);
		player->SetActionCount(0);
	}

	location.y = player->GetCenterLocation().y;
	screenLocation = Camera::ConvertScreenPosition(location);
}

void LargeSword::Draw() const
{
	if (isShow)DrawLineAA(screenLocation.x, screenLocation.y,
		screenLocation.x + directionVector.x, screenLocation.y + directionVector.y,
		0x000000, 1);
}

void LargeSword::Attack(const Player* player)
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
		directionVector.x = LARGRSWORD_LENGTH;
		angle = LARGESWORD_ANGLE;
	}
	//左に出す
	else
	{
		directionVector.x = -LARGRSWORD_LENGTH;
		angle = -LARGESWORD_ANGLE;
	}

	directionVector.y = -100.f;
}

void LargeSword::Hit(CharaBase* enemy, Player* player)
{
	if (isShow)
	{
		if (enemy->GetIsShow() && !enemy->GetIsHit())
		{
			enemy->SetHp(enemy->GetHp() - (player->GetDamage() + LARGESWORD_DAMAGE));
			enemy->SetIsHit(true);
		}
	}
}
