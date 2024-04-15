#include "Player.h"
#include"../../Scene/GameMain/GameMainScene.h"

#define DEBUG

Player::Player()
{
	location = { 300.f,GROUND_LINE + area.height };
	area = { 100.f,100.f };
	direction = { 1.f,0.f };
	damage = 10.f;

	normalWeapon = new NormalWeapon();
	steal = new Steal();

	guardCount = 0;

	framCount = 0;
	damageFramCount = 0;
	parryFram = 0;

	guardCoolTime = 0.f;
	normalWeaponCoolTime = 0.f;
	stealCoolTime = 0.f;

	isGuard = false;
	isSteal = false;
	guardCoolTimeFlg = false;
	parryFlg = false;
}

Player::~Player()
{
	delete normalWeapon;
	delete steal;
}

void Player::Update(GameMainScene* object)
{
	if (parryFlg)
	{
		parryFram++;
		//PLAYER_PARRY_TIME後に再度パリィ可能
		if (parryFram > PLAYER_PARRY_TIME)
		{
			parryFlg = false;
			parryFram = 0;
		}
	}

	Movement();

	Attack();

	Guard();

	normalWeapon->Update(object);

	steal->Update(object);

	Hit(object);

	screenLocation = object->GetCamera()->ConvertScreenPosition(location);
}

void Player::Draw() const
{
#ifdef DEBUG

	DrawBoxAA
	(
		GetMinScreenLocation().x, GetMinScreenLocation().y,
		GetMaxScreenLocation().x, GetMaxScreenLocation().y,
		isGuard ? parryFlg ? 0x00ff00 : 0x0000ff : isHit ? 0xff0000 : 0xffff00, FALSE
	);

	DrawFormatString(0, 0, 0xff0000, "hp :%f", hp);
	DrawFormatString(0, 15, 0xff0000, "parryFlg :%s", parryFlg ? "true" : "false");
	DrawFormatString(0, 30, 0xff0000, "direction x:%f y:%f", direction.x,direction.y);

#endif // DEBUG

	if (normalWeapon->GetIsShow())
	{
		normalWeapon->Draw();
	}

	if (steal->GetIsShow())
	{
		steal->Draw();
	}
}

void Player::Hit(GameMainScene* object)
{
	DamageInterval(PLAYER_DAMAGE_INTERVAL);

	if (isKnockBack)
	{
		knockBackCount++;
		location.x += vector.x;
		if (knockBackCount > PLAYER_KNOCKBACK_TIME)
		{
			isKnockBack = false;
			knockBackCount = 0;
		}
	}

	//雑魚的に当たったら
	if (object->GetNormalEnemy() != nullptr && HitCheck(object->GetNormalEnemy()))
	{
		//すでに当たってないなら
		if (!isHit)
		{
			Damage(object);
		}
	}
}

void Player::Movement()
{
	//右へ移動
	if ((KeyInput::GetKeyDown(KEY_INPUT_D) || PadInput::GetLStickRationX() > NEED_STICK_RATIO) &&
		!isGuard && !isSteal && !isHit)
	{
		//最高速度は超えない
		if (vector.x < PLAYER_MAX_MOVE_SPEED)
		{
			if (isAir)
			{
				vector.x += 0.5f;
			}
			else
			{
				vector.x += PLAYER_MOVE_SPEED;
			}

			direction.x = 1.f;
		}
		else
		{
			vector.x = PLAYER_MAX_MOVE_SPEED;
		}
	}
	//左へ移動
	else if ((KeyInput::GetKeyDown(KEY_INPUT_A) || PadInput::GetLStickRationX() < -NEED_STICK_RATIO) &&
		!isGuard && !isSteal && !isHit)
	{
		//最高速度は超えない
		if (vector.x > -PLAYER_MAX_MOVE_SPEED)
		{
			if (isAir)
			{
				vector.x += -0.5f;
			}
			else
			{
				vector.x += -PLAYER_MOVE_SPEED;
			}

			direction.x = -1.f;
		}
		else
		{
			vector.x = -PLAYER_MAX_MOVE_SPEED;
		}
	}
	//停止
	else
	{
		if (!isKnockBack)vector.x = 0.f;
	}

	//ジャンプ
	if ((KeyInput::GetKey(KEY_INPUT_SPACE) ||
		KeyInput::GetKey(KEY_INPUT_W) ||
		PadInput::OnButton(XINPUT_BUTTON_A)) && !isAir && !isGuard && !isHit)
	{
		vector.y = -JUMP_POWER;
		isAir = true;
		direction.y = -1.f;
	}

	//下に落ちているなら
	if (vector.y > 0)
	{
		direction.y = 1.f;
	}

	//重力
	vector.y += GRAVITY;

	//座標に加算
	location.x += vector.x;
	location.y += vector.y;

	//左端を超えない
	if (GetMinLocation().x < 0.f)
	{
		location.x = 0.f;
		vector.x = 0.f;
	}
	//右端を超えない
	else if (GetMaxLocation().x > WORLD_WIDTH)
	{
		location.x = WORLD_WIDTH - area.width;
		vector.x = 0.f;
	}

	//天井を超えない
	if (GetMinLocation().y < 0.f)
	{
		location.y = 0.f;
		vector.y = 0.f;
	}

	//地面を超えない
	if (GetMaxLocation().y > GROUND_LINE)
	{
		location.y = GROUND_LINE - area.height;
		vector.y = 0.f;
		isAir = false;
		direction = { direction.x,0.f };
	}
}

void Player::Attack()
{
	//通常攻撃をしているなら
	if ((KeyInput::GetButton(MOUSE_INPUT_LEFT) ||
		PadInput::OnPressed(XINPUT_BUTTON_B)) && normalWeaponCoolTime <= 0.f)
	{
		isAttack = true;
		//能力を持っていないなら
		if (abilityType == Ability::Empty)
		{
			normalWeaponCoolTime = PLAYER_NORMALWEAPON_COOLTIME;
			normalWeapon->Attack(this);
			isAttack = false;
		}
	}

	normalWeaponCoolTime--;

	//奪う攻撃をしているなら
	if ((KeyInput::GetButton(MOUSE_INPUT_RIGHT) || PadInput::OnPressed(XINPUT_BUTTON_Y)) && 
		stealCoolTime <= 0.f)
	{
		isAttack = true;
		isSteal = true;
		stealCoolTime = PLAYER_STEAL_COOLTIME;
		steal->Attack(this);
		isAttack = false;
	}

	if (!steal->GetIsShow())
	{
		isSteal = false;
	}

	stealCoolTime--;
}

void Player::Guard()
{
	//ガードしているなら
	if ((KeyInput::GetKeyDown(KEY_INPUT_LSHIFT) ||
		PadInput::OnPressed(XINPUT_BUTTON_LEFT_SHOULDER) ||
		PadInput::OnPressed(XINPUT_BUTTON_RIGHT_SHOULDER)) && guardCoolTime <= 0.f)
	{
		isGuard = true;
		guardCount = 1;
	}
	//ガードしていないなら
	else
	{
		isGuard = false;
	}

	guardCoolTime--;

	//ガードはしていないが以前にガードしていたら
	if (guardCount && !isGuard)
	{
		//クールタイム発生
		if (guardCoolTime < 0 && !guardCoolTimeFlg)
		{
			guardCoolTime = PLAYER_GUARD_COOLTIME;
			guardCoolTimeFlg = true;
		}

		//クールタイム終了
		if (guardCoolTime < 0)
		{
			guardCount = 0;
			guardCoolTimeFlg = false;
		}
	}
}

void Player::Damage(GameMainScene* object)
{
	//ダメージ用のカウントを計測する
	damageFramCount++;

	//PLAYER_PARRY_FLAME以内にガードできたらかつパリィしていないなら
	if (damageFramCount <= PLAYER_PARRY_FLAME &&
		(KeyInput::GetKey(KEY_INPUT_LSHIFT) ||
			PadInput::OnButton(XINPUT_BUTTON_LEFT_SHOULDER) ||
			PadInput::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER)) &&
		!parryFlg)
	{
		parryFlg = true;
	}

	//パリィできなかったら
	if (damageFramCount > PLAYER_PARRY_FLAME && !parryFlg)
	{
		isHit = true;

		//ガードしていないなら
		if (!isGuard)
		{
			hp -= object->GetNormalEnemy()->GetDamage();
			isKnockBack = true;
			if (GetCenterLocation().x < object->GetNormalEnemy()->GetCenterLocation().x)
			{
				vector.x = -PLAYER_KNOCKBACK;
			}
			else
			{
				vector.x = PLAYER_KNOCKBACK;
			}
		}
		//ガードしているなら
		else
		{
			hp -= object->GetNormalEnemy()->GetDamage() * PLAYER_DAMAGE_CUT;
		}
		//0にする
		damageFramCount = 0;
	}
}
