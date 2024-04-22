#include "Player.h"
#include"../Camera/Camera.h"

#define DEBUG

Player::Player()
{
	location.x = 300.f;
	location.y = GROUND_LINE;
	area.width = 100.f;
	area.height = 100.f;
	direction.x = 1.f;
	direction.y = 0.f;
	damage = 10.f;
	abilityType = Ability::LargeSword;

	normalWeapon = new NormalWeapon();
	for (int i = 0; i < STEAL_VALUE; i++)
	{
		steal[i] = new Steal();
	}
	largeSword = new LargeSword();

	guardCount = 0;

	framCount = 0;
	damageFramCount = 0;
	parryFram = 0;
	abilityFramCount = 0;

	guardCoolTime = 0.f;
	attackCoolTime = 0.f;
	stealCoolTime = 0.f;

	isGuard = false;
	stealFlg = false;
	isEquipment = false;
	guardCoolTimeFlg = false;
	parryFlg = false;
}

Player::~Player()
{
	delete normalWeapon;
	for (int i = 0; i < STEAL_VALUE; i++)
	{
		delete steal[i];
	}
	delete largeSword;
}

void Player::Update()
{
#ifdef DEBUG
	if (KeyInput::GetKey(KEY_INPUT_1))abilityType = Ability::LargeSword;
	if (KeyInput::GetKey(KEY_INPUT_2))abilityType = Ability::Dagger;
	if (KeyInput::GetKey(KEY_INPUT_3))abilityType = Ability::Rapier;
	if (abilityType != Ability::Empty)isEquipment = true;
#endif // DEBUG

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

	if (isEquipment)
	{
		abilityFramCount--;
		if (abilityFramCount < 0)
		{
			abilityType = Ability::Empty;
			abilityFramCount = PLAYER_ABILITY_TIME;
			isEquipment = false;
		}
	}

	DamageInterval(int(PLAYER_DAMAGE_INTERVAL));

	KnockBack(PLAYER_KNOCKBACK_TIME);

	Movement();

	Attack();

	Guard();

	normalWeapon->Update(this);
	
	for (int i = 0; i < STEAL_VALUE; i++)
	{
		steal[i]->Update(this);
	}

	largeSword->Update(this);

	screenLocation = Camera::ConvertScreenPosition(location);
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

	DrawFormatString(0, 0, 0x000000, "hp :%f", hp);
	DrawFormatString(0, 15, 0x000000, "attackCoolTime :%f", attackCoolTime);
	DrawFormatString(0, 30, 0x000000, "stealCoolTime :%f", stealCoolTime);
	DrawFormatString(250, 45, 0x000000, "1:LargeSword 2:Dagger 3:Rapier");
	DrawFormatString(0, 60, 0x000000, "%d", abilityFramCount);
	if (abilityType == Ability::Empty)
	{
		DrawFormatString(0, 45, 0x000000, "WeaponType:None");
	}
	else
	{
		if (abilityType == Ability::LargeSword)
		{
			DrawFormatString(0, 45, 0x000000, "WeaponType:LargeSword");
		}
		if (abilityType == Ability::Dagger)
		{
			DrawFormatString(0, 45, 0x000000, "WeaponType:Dagger");
		}
		if (abilityType == Ability::Rapier)
		{
			DrawFormatString(0, 45, 0x000000, "WeaponType:Rapier");
		}
	}

#endif // DEBUG

	normalWeapon->Draw();

	for (int i = 0; i < STEAL_VALUE; i++)
	{
		steal[i]->Draw();
	}

	largeSword->Draw();

}

void Player::Hit(CharaBase* chara)
{
	//すでに当たってないなら
	if (!isHit)
	{
		Damage(chara);
	}
}

void Player::Movement()
{
	//右へ移動
	if ((KeyInput::GetKeyDown(KEY_INPUT_D) || PadInput::GetLStickRationX() > NEED_STICK_RATIO) &&
		!isGuard && !isHit && !isAttack)
	{
		//最高速度は超えない
		if (move.x < PLAYER_MAX_MOVE_SPEED)
		{
			if (isAir)
			{
				move.x += 0.5f;
			}
			else
			{
				move.x += PLAYER_MOVE_SPEED;
			}

			direction.x = 1.f;
		}
		else
		{
			move.x = PLAYER_MAX_MOVE_SPEED;
		}
	}
	//左へ移動
	else if ((KeyInput::GetKeyDown(KEY_INPUT_A) || PadInput::GetLStickRationX() < -NEED_STICK_RATIO) &&
		!isGuard && !isHit && !isAttack)
	{
		//最高速度は超えない
		if (move.x > -PLAYER_MAX_MOVE_SPEED)
		{
			if (isAir)
			{
				move.x += -0.5f;
			}
			else
			{
				move.x += -PLAYER_MOVE_SPEED;
			}

			direction.x = -1.f;
		}
		else
		{
			move.x = -PLAYER_MAX_MOVE_SPEED;
		}
	}
	//停止
	else
	{
		if (!isKnockBack)move.x = 0.f;
	}

	//ジャンプ
	if ((KeyInput::GetKey(KEY_INPUT_SPACE) ||
		KeyInput::GetKey(KEY_INPUT_W) ||
		PadInput::OnButton(XINPUT_BUTTON_A)) && !isAir && !isGuard && !isHit && !isAttack)
	{
		move.y = -JUMP_POWER;
		isAir = true;
		direction.y = -1.f;
	}

	//下に落ちているなら
	if (move.y > 0)
	{
		direction.y = 1.f;
	}

	//重力
	move.y += GRAVITY;

	//座標に加算
	location.x += move.x;
	location.y += move.y;

	//左端を超えない
	if (GetMinLocation().x < 0.f)
	{
		location.x = 0.f;
		move.x = 0.f;
	}
	//右端を超えない
	else if (GetMaxLocation().x > WORLD_WIDTH)
	{
		location.x = WORLD_WIDTH - area.width;
		move.x = 0.f;
	}

	//天井を超えない
	if (GetMinLocation().y < 0.f)
	{
		location.y = 0.f;
		move.y = 0.f;
	}

	//地面を超えない
	if (GetMaxLocation().y > GROUND_LINE)
	{
		location.y = GROUND_LINE - area.height;
		move.y = 0.f;
		isAir = false;
		direction = { direction.x,0.f };
	}
}

void Player::Attack()
{
	//投げるまたは武器攻撃
	if ((KeyInput::GetButton(MOUSE_INPUT_RIGHT) ||
		PadInput::OnPressed(XINPUT_BUTTON_X)) && attackCoolTime <= 0.f && !isHit)
	{
		//能力を持っているないなら投げる
		if (stealFlg && abilityType == Ability::Empty)
		{		
			attackCoolTime = PLAYER_NORMALWEAPON_COOLTIME;
			normalWeapon->Attack(this);
			stealFlg = false;
		}

		//武器攻撃
		if (abilityType != Ability::Empty)
		{
			if (abilityType == Ability::LargeSword)
			{
				isAttack = true;
				attackCoolTime = PLAYER_LARGESWORD_COOLTIME;
				largeSword->Attack(this);
			}
		}
	}

	if (attackCoolTime > 0)attackCoolTime--;

	//装備
	if (stealFlg && !isHit &&
		(KeyInput::GetKeyDown(KEY_INPUT_E) || PadInput::OnPressed(XINPUT_BUTTON_Y)))
	{
		for (int i = 0; i < STEAL_VALUE; i++)
		{
			if (steal[i]->GetKeepType() != Ability::Empty)
			{
				abilityType = steal[i]->GetKeepType();
				steal[i]->SetKeepType(Ability::Empty);
				isEquipment = true;
			}
		}
		stealFlg = false;
	}

	//奪う
	if ((KeyInput::GetButton(MOUSE_INPUT_LEFT) || PadInput::OnPressed(XINPUT_BUTTON_B)) &&
		stealCoolTime <= 0.f && !isHit)
	{
		isAttack = true;
		stealCoolTime = PLAYER_STEAL_COOLTIME;
		//真ん中
		steal[0]->Attack(this, STEAL_DISTANCE - 20.f, 100.f, 100.f, 30.f);
		//上
		steal[1]->Attack(this, STEAL_DISTANCE - 10.f, 60.f, 60.f, 0.f);
		//下
		steal[2]->Attack(this, STEAL_DISTANCE + 10.f, 70.f, 70.f, 30.f);
	}

	if (stealCoolTime > 0)stealCoolTime--;
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

void Player::Damage(CharaBase* chara)
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
			hp -= chara->GetDamage();
			isKnockBack = true;
			if (GetCenterLocation().x < chara->GetCenterLocation().x)
			{
				move.x = -PLAYER_KNOCKBACK;
			}
			else
			{
				move.x = PLAYER_KNOCKBACK;
			}
		}
		//ガードしているなら
		else
		{
			hp -= chara->GetDamage() * PLAYER_DAMAGE_CUT;
		}
		//0にする
		damageFramCount = 0;
	}
}
