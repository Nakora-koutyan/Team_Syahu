#include"LargeSword.h"
#include"../../Player/Player.h"
#include"../../../Camera/Camera.h"
#include"../../../../ResourceManager/ResourceManager.h"

LargeSword::LargeSword()
{
	objectType = ObjectType::Weapon;

	directionVector.x = LARGRSWORD_LENGTH;
	directionVector.y = 0.f;

	airAttackEffectLocation.x = 0.f;
	airAttackEffectLocation.y = 0.f;

	direction = 0;
	effectAnim = 3;
	effectAnimcount = 0;
	airAttackEffectAnim = 3;
	airAttackEffectAnimcount = 0;

	framCount = 0;

	angle = 0.f;
	imageAngle = 0.f;

	isShow = false;
	isHit = false;
	isAirAttack = false;
	airAttackAnimFlg = false;
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
		effectAnimcount++;
		directionVector.x = directionVector.x * cos(DEGREE_TO_RADIAN(angle)) - directionVector.y * sin(DEGREE_TO_RADIAN(angle));
		directionVector.y = directionVector.x * sin(DEGREE_TO_RADIAN(angle)) + directionVector.y * cos(DEGREE_TO_RADIAN(angle));
		imageAngle += DEGREE_TO_RADIAN(angle);

		if (effectAnimcount % 3 == 0)
		{
			if (effectAnim < 6)
			{
				effectAnim++;
			}
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
		location.y = chara->GetCenterLocation().y;
	}
	//空中攻撃なら
	else if (isAirAttack)
	{
		chara->SetMove({ chara->GetMove().x , chara->GetMove().y / 2 + LARGESWORD_FALL_SPEED });
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

	//落下攻撃のエフェクト
	if (airAttackAnimFlg)
	{
		airAttackEffectAnimcount++;
		if (airAttackEffectAnimcount % 5 == 0)
		{
			if (airAttackEffectAnim < 6)
			{
				if (airAttackEffectLocation.x == 0.f)
				{
					airAttackEffectLocation.x = location.x + directionVector.x;
					airAttackEffectLocation.y = chara->GetMaxLocation().y;
				}
				airAttackEffectAnim++;
			}
			else
			{
				airAttackAnimFlg = false;
				airAttackEffectLocation = { 0.f,0.f };
				airAttackEffectAnim = 3;
			}
		}
	}


	//攻撃時間を超えたら
	if ((framCount > LARGESWORD_ATTACK_TIME || chara->GetIsKnockBack()) && !isAirAttack)
	{
		framCount = 0;
		direction = 0;
		effectAnimcount = 0;
		effectAnim = 3;
		angle = 0.f;
		imageAngle = 0.f;
		isShow = false;
		isHit = false;
		chara->SetIsAttack(false);
	}
	//空中攻撃が地面に着地したら
	else if (isAirAttack && !chara->GetIsAir())
	{
		ResourceManager::PlaySE("fallAttack", FALSE);
		framCount = 0;
		direction = 0;
		angle = 0.f;
		imageAngle = 0.f;
		isShow = false;
		isHit = false;
		isAirAttack = false;
		airAttackAnimFlg = true;
		chara->SetIsAttack(false);
		chara->SetInvincibleFlg(false);
	}

	screenLocation = Camera::ConvertScreenPosition(location);
}

void LargeSword::Draw() const
{
#ifdef DEBUG
	if (isShow)DrawLineAA(screenLocation.x, screenLocation.y,
		screenLocation.x + directionVector.x, screenLocation.y + directionVector.y,
		0x000000, 1);
#endif // DEBUG

	if (isShow)
	{
		const float effectImageShift = 30.f;
		if (direction > 0)
		{
			if (!isAirAttack)
				DrawRotaGraphF(screenLocation.x + effectImageShift, screenLocation.y, 1, DEGREE_TO_RADIAN(-12.f),
					ResourceManager::GetDivImage("Effect/slashEffect", effectAnim),
					TRUE);

			DrawRotaGraph2F(screenLocation.x, screenLocation.y, 0, 100,
				1, imageAngle, ResourceManager::GetImage("Weapon/largeSword"),
				TRUE);
		}
		else
		{
			if (!isAirAttack)
				DrawRotaGraphF(screenLocation.x - effectImageShift, screenLocation.y, 1, DEGREE_TO_RADIAN(12.f),
					ResourceManager::GetDivImage("Effect/slashEffect", effectAnim),
					TRUE, TRUE);

			DrawRotaGraph2F(screenLocation.x, screenLocation.y, 100, 100,
				1, imageAngle, ResourceManager::GetImage("Weapon/largeSword"),
				TRUE, TRUE);
		}
	}

	const float airAttackEffectImageShift = 100.f;

	if (direction > 0)
	{
		if (airAttackAnimFlg)
			DrawRotaGraphF(Camera::ConvertScreenPosition(airAttackEffectLocation).x,
				Camera::ConvertScreenPosition(airAttackEffectLocation).y - airAttackEffectImageShift, 1, 0,
				ResourceManager::GetDivImage("Effect/fallAttackEffect",
					airAttackEffectAnim), TRUE);
	}
	else
	{
		if (airAttackAnimFlg)
			DrawRotaGraphF(Camera::ConvertScreenPosition(airAttackEffectLocation).x,
				Camera::ConvertScreenPosition(airAttackEffectLocation).y - airAttackEffectImageShift, 1, 0,
				ResourceManager::GetDivImage("Effect/fallAttackEffect",
					airAttackEffectAnim), TRUE);
	}
}

void LargeSword::Attack(CharaBase* chara)
{
	ResourceManager::PlaySE("largeSword", FALSE);

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
		chara->SetMove({ chara->GetMove().x,0 });
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