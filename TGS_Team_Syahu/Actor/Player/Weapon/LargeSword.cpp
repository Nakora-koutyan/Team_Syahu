#include"LargeSword.h"
#include"../../Player/Player.h"
#include"../../Camera/Camera.h"

LargeSword::LargeSword()
{
	directionVector.x = LARGRSWORD_LENGTH;
	directionVector.y = -50.f;

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
	}
	else
	{
		location = player->GetCenterLocation();
	}

	//攻撃時間を超えたら
	if (framCount > LARGESWORD_ATTACK_TIME)
	{
		framCount = 0;
		direction = 0;
		angle = 0.f;
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
		directionVector.x = LARGRSWORD_LENGTH;
		angle = LARGESWORD_ANGLE;
	}
	//左に出す
	else
	{
		location.x = player->GetMinLocation().x - LARGESWORD_DISTANCE;
		directionVector.x = -LARGRSWORD_LENGTH;
		angle = -LARGESWORD_ANGLE;
	}

	location.y = player->GetCenterLocation().y;
	directionVector.y = -50.f;

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
