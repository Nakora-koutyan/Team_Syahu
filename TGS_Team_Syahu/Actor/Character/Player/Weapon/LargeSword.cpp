#include"LargeSword.h"
#include"../../Player/Player.h"
#include"../../../Camera/Camera.h"
#include"../../../../ResourceManager/ResourceManager.h"

LargeSword::LargeSword()
{
	objectType = ObjectType::Weapon;

	directionVector.x = LARGRSWORD_LENGTH;
	directionVector.y = 0.f;


	direction = 0;

	framCount = 0;

	angle = 0.f;
	imageAngle = 0.f;

	isShow = false;
	isHit = false;
	isAirAttack = false;
}

LargeSword::~LargeSword()
{

}

void LargeSword::Update(CharaBase* chara)
{
	//地上での攻撃なら
	if (isShow && !isAirAttack)
	{
		framCount++;
		directionVector.x = directionVector.x * cos(DEGREE_TO_RADIAN(angle)) - directionVector.y * sin(DEGREE_TO_RADIAN(angle));
		directionVector.y = directionVector.x * sin(DEGREE_TO_RADIAN(angle)) + directionVector.y * cos(DEGREE_TO_RADIAN(angle));
		imageAngle += DEGREE_TO_RADIAN(angle);

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
		location.y = chara->GetCenterLocation().y;
	}
	//空中攻撃なら
	else if (isAirAttack)
	{
		chara->SetMove({ chara->GetMove().x , LARGESWORD_FALL_SPEED });
		chara->SetInvincibleFlg(true);
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
		directionVector.y = 0.f;
		location.y = chara->GetCenterLocation().y + 20.f;
	}
	else
	{
		location = chara->GetCenterLocation();
	}


	//攻撃時間を超えたら
	if ((framCount > LARGESWORD_ATTACK_TIME || chara->GetIsKnockBack()) && !isAirAttack)
	{
		framCount = 0;
		direction = 0;
		angle = 0.f;
		imageAngle = 0.f;
		isShow = false;
		isHit = false;
		chara->SetIsAttack(false);
	}
	else if (isAirAttack && !chara->GetIsAir())
	{
		framCount = 0;
		direction = 0;
		angle = 0.f;
		imageAngle = 0.f;
		isShow = false;
		isHit = false;
		isAirAttack = false;
		chara->SetIsAttack(false);
		chara->SetInvincibleFlg(false);
	}

	screenLocation = Camera::ConvertScreenPosition(location);
}

void LargeSword::Draw() const
{
	if (isShow)DrawLineAA(screenLocation.x, screenLocation.y,
		screenLocation.x + directionVector.x, screenLocation.y + directionVector.y,
		0x000000, 1);
	if (isShow)
	{
		if (direction > 0)
		{
			DrawRotaGraph2F(screenLocation.x, screenLocation.y, 0, 100,
				1, imageAngle, ResourceManager::GetImage("Weapon/largeSword"), TRUE);
		}
		else
		{
			DrawRotaGraph2F(screenLocation.x, screenLocation.y, 100, 100,
				1, imageAngle, ResourceManager::GetImage("Weapon/largeSword"), TRUE, TRUE);
		}
	}
}

void LargeSword::Attack(const CharaBase* chara)
{
	isShow = true;

	//まだ方向が決まってないなら
	if (direction == 0)
	{
		//プレイヤーの方向情報を保持する
		direction = (short)chara->GetDirection().x;
	}

	if (chara->GetIsAir())
	{
		isAirAttack = true;
		//右に出す
		if (direction > 0)
		{
			directionVector.x = LARGRSWORD_LENGTH;
			imageAngle = DEGREE_TO_RADIAN(45.f);
		}
		//左に出す
		else
		{
			directionVector.x = -LARGRSWORD_LENGTH;
			imageAngle = DEGREE_TO_RADIAN(-45.f);
		}
		directionVector.y = 0.f;
	}
	else
	{
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
}

void LargeSword::Hit(ObjectBase* target, const float damage)
{
	CharaBase* enemy = static_cast<CharaBase*>(target);

	if (isShow)
	{
		if (enemy->GetIsShow() && !enemy->GetIsHit())
		{
			enemy->SetHp(enemy->GetHp() - (damage + LARGESWORD_DAMAGE));
			enemy->SetKnockBackMove(LARGESWORD_KNOCKBACK);
			isHit = true;
		}
	}
}