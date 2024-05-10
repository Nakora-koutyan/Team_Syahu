#include"LargeSword.h"
#include"../../Player/Player.h"
#include"../../../Camera/Camera.h"

LargeSword::LargeSword()
{
	directionVector.x = LARGRSWORD_LENGTH;
	directionVector.y = 0.f;

	direction = 0;

	framCount = 0;

	angle = 0.f;

	isShow = false;
}

LargeSword::~LargeSword()
{

}

void LargeSword::Update()
{
	screenLocation = Camera::ConvertScreenPosition(location);
}

void LargeSword::Draw() const
{
	if (isShow)DrawLineAA(screenLocation.x, screenLocation.y,
		screenLocation.x + directionVector.x, screenLocation.y + directionVector.y,
		0x000000, 1);
}

void LargeSword::Appearance(CharaBase* chara)
{
	if (isShow)
	{
		framCount++;
		directionVector.x = directionVector.x * cos(DEGREE_TO_RADIAN(angle)) - directionVector.y * sin(DEGREE_TO_RADIAN(angle));
		directionVector.y = directionVector.x * sin(DEGREE_TO_RADIAN(angle)) + directionVector.y * cos(DEGREE_TO_RADIAN(angle));
	}
	else
	{
		location = chara->GetCenterLocation();
	}

	//右に出す
	if (direction > 0)
	{
		location.x = chara->GetMaxLocation().x + WEAPON_DISTANCE;
	}
	//左に出す
	else
	{
		location.x = chara->GetMinLocation().x - WEAPON_DISTANCE;
	}

	//攻撃時間を超えたら
	if (framCount > LARGESWORD_ATTACK_TIME || chara->GetIsKnockBack())
	{
		framCount = 0;
		direction = 0;
		angle = 0.f;
		isShow = false;
		chara->SetIsAttack(false);
	}

	location.y = chara->GetCenterLocation().y;
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

void LargeSword::Hit(ObjectBase* object, const float damage)
{
	CharaBase* enemy = static_cast<CharaBase*>(object);

	if (isShow)
	{
		if (enemy->GetIsShow() && !enemy->GetIsHit())
		{
			enemy->SetHp(enemy->GetHp() - (damage + LARGESWORD_DAMAGE));
			enemy->SetIsHit(true);
		}
	}
}