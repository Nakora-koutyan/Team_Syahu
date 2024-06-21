#include"Dagger.h"
#include"../../Player/Player.h"
#include"../../../Camera/Camera.h"
#include"../../../../ResourceManager/ResourceManager.h"
#include"../../../../InputControl/Pad/PadInput.h"
#include"../../../../InputControl/Key/KeyInput.h"

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

	imageAngle = 0.f;

	isShow = false;
	isHit = false;
	isAirAttack = false;
	attackEndFlg = false;
}

Dagger::~Dagger()
{

}

void Dagger::Update(CharaBase* chara)
{
	if (!isShow)
	{
		location = chara->GetCenterLocation();
	}

	//攻撃時間を超えたら
	if (chara->GetIsKnockBack() ||
		screenLocation.x + directionVector.x < 0 || screenLocation.x > SCREEN_WIDTH ||
		screenLocation.y < 0 || location.y + directionVector.y > WORLD_HEIGHT)
	{
		move.x = 0.f;
		move.y = 0.f;
		framCount = 0;
		direction = 0;
		imageAngle = 0.f;
		isShow = false;
		isHit = false;
		chara->SetIsAttack(false);
	}

	if (attackEndFlg)
	{
		chara->SetIsAttack(false);
		attackEndFlg = false;
	}

	damage = chara->GetDamage() + DAGGER_DAMAGE;
	location.x += move.x;
	location.y += move.y;
	screenLocation = Camera::ConvertScreenPosition(location);
}

void Dagger::Draw() const
{
#ifdef DEBUG
	if (isShow)DrawLineAA(screenLocation.x, screenLocation.y,
		screenLocation.x + directionVector.x, screenLocation.y + directionVector.y,
		0x000000, 1);
#endif // DEBUG

	if (isShow)
	{
		if (!isAirAttack)
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
		else
		{
			if (direction > 0)
			{
				DrawRotaGraph2F(screenLocation.x, screenLocation.y, 0, 75,
					1, imageAngle, ResourceManager::GetImage("Weapon/dagger"), TRUE);
			}
			else
			{
				DrawRotaGraph2F(screenLocation.x - 5.f, screenLocation.y, 75, 75,
					1, imageAngle, ResourceManager::GetImage("Weapon/dagger"), TRUE, TRUE);
			}
		}
	}
}

void Dagger::Attack(const CharaBase* chara)
{
	ResourceManager::PlaySE("dagger", FALSE);

	isShow = true;

	//まだ方向が決まってないなら
	if (direction == 0)
	{
		//プレイヤーの方向情報を保持する
		direction = (short)chara->GetDirection().x;
	}

	//右に出す
	if (direction > 0 && !chara->GetIsAir())
	{
		location.x = chara->GetMaxLocation().x + WEAPON_DISTANCE;
		directionVector.x = DAGGER_LENGTH;
		directionVector.y = 0.f;
		move.x = DAGGER_SPEED;
		imageAngle += DEGREE_TO_RADIAN(45.f);
	}
	//左に出す
	else if (direction < 0 && !chara->GetIsAir())
	{
		location.x = chara->GetMinLocation().x - WEAPON_DISTANCE;
		directionVector.x = -DAGGER_LENGTH;
		directionVector.y = 0.f;
		move.x = -DAGGER_SPEED;
		imageAngle += DEGREE_TO_RADIAN(-45.f);
	}
	//空中なら
	else if (chara->GetIsAir())
	{
		isAirAttack = true;
		directionVector.y = DAGGER_LENGTH;
		//下入力をしたら
		if (PadInput::GetLStick().y < -0.2 || KeyInput::GetKeyDown(KEY_INPUT_S))
		{
			//斜めに出す
			move.y = DAGGER_SPEED * sin(DEGREE_TO_RADIAN(150.f));
			if (direction > 0)
			{
				imageAngle += DEGREE_TO_RADIAN(90.f);
				move.x = -10.f * cos(DEGREE_TO_RADIAN(-150.f));
			}
			else if (direction < 0)
			{
				imageAngle += DEGREE_TO_RADIAN(-90.f);
				move.x = 10.f * cos(DEGREE_TO_RADIAN(-150.f));
			}
		}
		//下入力をしてないなら
		else
		{
			//横に出す
			if (direction > 0)
			{
				imageAngle += DEGREE_TO_RADIAN(45.f);
				directionVector.x = DAGGER_LENGTH;
				directionVector.y = 0.f;
				move.x = DAGGER_SPEED;
			}
			else if (direction < 0)
			{
				imageAngle += DEGREE_TO_RADIAN(-45.f);
				directionVector.x = -DAGGER_LENGTH;
				directionVector.y = 0.f;
				move.x = -DAGGER_SPEED;
			}
		}

		//右に出す
		if (direction > 0)
		{
			location.x = chara->GetMaxLocation().x + WEAPON_DISTANCE;
			directionVector.x = DAGGER_LENGTH;
		}
		//左に出す
		else
		{
			location.x = chara->GetMinLocation().x - WEAPON_DISTANCE;
			directionVector.x = -DAGGER_LENGTH;
		}
	}
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
	imageAngle = 0.f;
	isShow = false;
	isHit = false;
	attackEndFlg = true;
}
