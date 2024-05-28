#include"Dagger.h"
#include"../../Player/Player.h"
#include"../../../Camera/Camera.h"
#include"../../../../ResourceManager/ResourceManager.h"

Dagger::Dagger()
{ 
	objectType = ObjectType::Weapon;

	directionVector.x = DAGGER_LENGTH;
	directionVector.y = 0.f;

	damage = 0.f;

	move.x = 0.f;
	move.y = 0.f;

	direction = 0;

	framCount = 0;

	angle = 0.f;
	imageAngle = 0.f;

	isShow = false;
	isHit = false;
}

Dagger::~Dagger()
{

}

void Dagger::Update(CharaBase* chara)
{
	if (isShow)
	{
		//framCount++;
		//directionVector.x = directionVector.x * cos(DEGREE_TO_RADIAN(angle)) - directionVector.y * sin(DEGREE_TO_RADIAN(angle));
		//directionVector.y = directionVector.x * sin(DEGREE_TO_RADIAN(angle)) + directionVector.y * cos(DEGREE_TO_RADIAN(angle));
		
		//if (direction > 0)
		//{
		//	imageAngle += DEGREE_TO_RADIAN(angle) + DEGREE_TO_RADIAN(5.f);
		//}
		//else
		//{
		//	imageAngle += DEGREE_TO_RADIAN(angle) + DEGREE_TO_RADIAN(-5.f);
		//}
	}
	else
	{
		location = chara->GetCenterLocation();
	}

	//攻撃時間を超えたら
	if (chara->GetIsKnockBack() || screenLocation.x + directionVector.x < 0 || screenLocation.x > SCREEN_WIDTH)
	{
		move.x = 0.f;
		move.y = 0.f;
		framCount = 0;
		direction = 0;
		angle = 0.f;
		imageAngle = 0.f;
		isShow = false;
		isHit = false;
		chara->SetIsAttack(false);
	}

	damage = chara->GetDamage() + DAGGER_DAMAGE;
	location.x += move.x;
	location.y += move.y;
	screenLocation = Camera::ConvertScreenPosition(location);
}

void Dagger::Draw() const
{
	if (isShow)DrawLineAA(screenLocation.x, screenLocation.y,
		screenLocation.x + directionVector.x, screenLocation.y + directionVector.y,
		0x000000, 1);
	if (isShow)
	{
		if (direction > 0)
		{
			DrawRotaGraph2F(screenLocation.x - 10.f, screenLocation.y, 0, 75,
				1, imageAngle, ResourceManager::GetImage("Weapon/dagger"), TRUE);
		}
		else
		{
			DrawRotaGraph2F(screenLocation.x + 10.f, screenLocation.y, 75, 75,
				1, imageAngle, ResourceManager::GetImage("Weapon/dagger"), TRUE, TRUE);
		}
	}
}

void Dagger::Attack(const CharaBase* chara)
{
	isShow = true;

	//まだ方向が決まってないなら
	if (direction == 0)
	{
		//プレイヤーの方向情報を保持する
		direction = (short)chara->GetDirection().x;
	}

	//右に出す
	if (direction > 0)
	{
		directionVector.x = DAGGER_LENGTH;
		move.x = DAGGER_SPEED;
		angle = DAGGER_ANGLE;
		imageAngle += DEGREE_TO_RADIAN(45.f);
	}
	//左に出す
	else
	{
		directionVector.x = -DAGGER_LENGTH;
		move.x = -DAGGER_SPEED;
		angle = -DAGGER_ANGLE;
		imageAngle += DEGREE_TO_RADIAN(-45.f);
	}

	directionVector.y = 0.f;
}

void Dagger::Hit(ObjectBase* target, const float damage)
{
	CharaBase* enemy = static_cast<CharaBase*>(target);

	if (isShow)
	{
		if (enemy->GetIsShow() && !enemy->GetIsHit())
		{
			enemy->SetHp(enemy->GetHp() - (damage + DAGGER_DAMAGE));
			enemy->SetKnockBackMove(DAGGER_KNOCKBACK);
			Init();
		}
	}
}

void Dagger::Init()
{
	move.x = 0.f;
	move.y = 0.f;
	framCount = 0;
	direction = 0;
	angle = 0.f;
	imageAngle = 0.f;
	isShow = false;
}
