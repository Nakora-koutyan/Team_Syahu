#include"Player.h"
#include"../Camera/Camera.h"

#define DEBUG

Player::Player()
{
	location.x = 300.f;
	location.y = GROUND_LINE;
	area.width = 56.f;
	area.height = 84.f;
	direction.x = 1.f;
	direction.y = 0.f;
	damage = 10.f;

	for (int i = 0; i < PLAYER_MAX_STOCK; i++)
	{
		stock[i] = Weapon::Empty;
		weaponFramCount[i] = PLAYER_WEAPON_TIME;
	}
	normalWeapon = new NormalWeapon();
	for (int i = 0; i < STEAL_VALUE; i++)
	{
		steal[i] = new Steal();
	}
	largeSword = new LargeSword();

	stockCount = 0;
	actionCount = 0;

	framCount = 0;
	damageFramCount = 0;
	playerAnimFramCount = 0;
	playerAnim = 0;
	int playerImageOld[72];		
	LoadDivGraph("Resource/Images/Player/AnimationSheet_Character_resize.png", 72, 8, 9, 96, 96, playerImageOld);
	for (int i = 0; i < 72; i++)
	{
		//画像がない部分は読みこまない
		if ((i >= 2 && i <= 7) ||
			(i >= 10 && i <= 15) ||
			(i >= 20 && i <= 23) ||
			(i >= 38 && i <= 39) ||
			(i >= 52 && i <= 55))
		{
			continue;
		}
		playerImage[playerAnim] = playerImageOld[i];
		playerAnim++;
	}
	playerAnim = 0;

	attackCoolTime = 0.f;
	stealCoolTime = 0.f;

	isEquipment = false;
	landingAnimFlg = false;
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
	if (KeyInput::GetKey(KEY_INPUT_1))
	{
		stock[stockCount] = Weapon::LargeSword;
	}
	if (KeyInput::GetKey(KEY_INPUT_2))
	{ 
		stock[stockCount] = Weapon::Dagger;
	}
	if (KeyInput::GetKey(KEY_INPUT_3)) 
	{ 
		stock[stockCount] = Weapon::Rapier;
	}
	if (KeyInput::GetKey(KEY_INPUT_4))
	{
		stock[stockCount] = Weapon::LargeSword;
	}
	if (KeyInput::GetKey(KEY_INPUT_P))
	{
		playerAnim++;
		if (playerAnim > 49)playerAnim = 0;
	}
#endif // DEBUG

	if (isEquipment && stock[stockCount] != Weapon::Empty)
	{
		if (actionCount == 4)
		{
			actionCount = 0;
		}
		weaponFramCount[stockCount]--;
		if (weaponFramCount[stockCount] < 0)
		{
			weaponType = Weapon::Empty;
			weaponFramCount[stockCount] = PLAYER_WEAPON_TIME;
			stock[stockCount] = Weapon::Empty;
			isEquipment = false;
		}
	}

	DamageInterval(int(PLAYER_DAMAGE_INTERVAL));

	KnockBack(PLAYER_KNOCKBACK_TIME);

	Movement();

	Attack();

	StockSelect();

	Animation();

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
		isHit ? 0xff0000 : 0xffff00, FALSE
	);

	DrawFormatString(0, 0, 0x000000, "hp :%f", hp);
	DrawFormatString(0, 15, 0x000000, "attackCoolTime :%f", attackCoolTime);
	DrawFormatString(0, 30, 0x000000, "stealCoolTime :%f", stealCoolTime);
	DrawFormatString(250, 45, 0x000000, "1:LargeSword 2:Dagger 3:Rapier");
	DrawFormatString(0, 60, 0x000000, "weaponCount[%d] :%d", stockCount, weaponFramCount[stockCount]);
	DrawFormatString(0, 75, 0x000000, "stock :%d %d %d %d %d", stock[0], stock[1], stock[2], stock[3], stock[4]);
	DrawFormatString(0, 90, 0x000000, "attackCount :%d", actionCount);
	if (weaponType == Weapon::Empty)
	{
		DrawFormatString(0, 45, 0x000000, "WeaponType:None");
	}
	else
	{
		if (weaponType == Weapon::LargeSword)
		{
			DrawFormatString(0, 45, 0x000000, "WeaponType:LargeSword");
		}
		if (weaponType == Weapon::Dagger)
		{
			DrawFormatString(0, 45, 0x000000, "WeaponType:Dagger");
		}
		if (weaponType == Weapon::Rapier)
		{
			DrawFormatString(0, 45, 0x000000, "WeaponType:Rapier");
		}
	}

#endif // DEBUG

	imageInversionFlg ?
		DrawRotaGraphF
		(GetMinScreenLocation().x + PLAYER_IMAGE_ALIGN_THE_ORIGIN_X - 6.f,
			GetMinScreenLocation().y + PLAYER_IMAGE_ALIGN_THE_ORIGIN_Y - 12.f,
			1, 0, playerImage[playerAnim], TRUE, TRUE) :
		DrawRotaGraphF
		(GetMinScreenLocation().x + PLAYER_IMAGE_ALIGN_THE_ORIGIN_X,
			GetMinScreenLocation().y + PLAYER_IMAGE_ALIGN_THE_ORIGIN_Y - 12.f,
			1, 0, playerImage[playerAnim], TRUE);

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
		//ダメージ用のカウントを計測する
		damageFramCount++;

		isHit = true;

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

		//0にする
		damageFramCount = 0;
	}
}

void Player::Landing(const float height)
{
	//地面を超えない
	if (GetMaxLocation().y > height)
	{
		location.y = height - area.height;
		move.y = 0.f;
		isAir = false;
		//空中の画像かつ動いていないなら
		if (playerAnim == 27 && !isMove)
		{
			landingAnimFlg = true;
		}
		direction = { direction.x,0.f };
	}
	else
	{
		isAir = true;
	}

	//移動しているなら
	if (isMove)
	{
		landingAnimFlg = false;
	}
}

void Player::Movement()
{
	//右へ移動
	if ((KeyInput::GetKeyDown(KEY_INPUT_D) || PadInput::GetLStickRationX() > NEED_STICK_RATIO) &&
		!isKnockBack && !isAttack)
	{
		isMove = true;
		direction.x = 1.f;
		imageInversionFlg = false;
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
		}
		else
		{
			move.x = PLAYER_MAX_MOVE_SPEED;
		}
	}
	//左へ移動
	else
	if ((KeyInput::GetKeyDown(KEY_INPUT_A) || PadInput::GetLStickRationX() < -NEED_STICK_RATIO) &&
		!isKnockBack && !isAttack)
	{
		isMove = true;
		direction.x = -1.f;
		imageInversionFlg = true;
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
		}
		else
		{
			move.x = -PLAYER_MAX_MOVE_SPEED;
		}
	}
	//停止
	else
	{
		if (!isKnockBack)
		{
			move.x = 0.f;
			isMove = false;
		}
	}

	//ジャンプ
	if ((KeyInput::GetKey(KEY_INPUT_SPACE) ||
		KeyInput::GetKey(KEY_INPUT_W) ||
		PadInput::OnButton(XINPUT_BUTTON_A)) && !isAir && !isKnockBack && !isAttack)
	{
		move.y = -JUMP_POWER;
		isAir = true;
		isJump = true;
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

	Landing(GROUND_LINE);
}

void Player::Attack()
{
	//投げるまたは武器攻撃
	if ((KeyInput::GetButton(MOUSE_INPUT_RIGHT) ||
		PadInput::OnButton(XINPUT_BUTTON_X)) && attackCoolTime <= 0.f && !isKnockBack && actionCount == 0)
	{
		//武器を持っているないなら投げる
		if (stock[stockCount] != Weapon::Empty && !isEquipment)
		{		
			isAttack = true;
			actionCount = 3;
			attackCoolTime = PLAYER_NORMALWEAPON_COOLTIME;
			normalWeapon->Attack(this, GetWeaponWeight(stock[stockCount]), GetWeaponDamage(stock[stockCount]));
			stock[stockCount] = Weapon::Empty;
			weaponFramCount[stockCount] = PLAYER_WEAPON_TIME;
		}

		//武器攻撃
		if (weaponType != Weapon::Empty)
		{
			actionCount = 2;
			if (stock[stockCount] == Weapon::LargeSword)
			{
				isAttack = true;
				attackCoolTime = PLAYER_LARGESWORD_COOLTIME;
				largeSword->Attack(this);
			}
		}
	}

	if (attackCoolTime > 0)attackCoolTime--;

	//装備
	if (!isKnockBack && stock[stockCount] != Weapon::Empty && weaponType == Weapon::Empty && actionCount == 0 &&
		(KeyInput::GetButton(MOUSE_INPUT_LEFT) || PadInput::OnButton(XINPUT_BUTTON_B)))
	{
			weaponType = stock[stockCount];
			isEquipment = true;
			actionCount = 4;
	}

	//奪う
	if ((KeyInput::GetButton(MOUSE_INPUT_LEFT) || PadInput::OnButton(XINPUT_BUTTON_B)) &&
		stealCoolTime <= 0.f && !isKnockBack && actionCount == 0)
	{
		isAttack = true;
		actionCount = 1;
		stealCoolTime = PLAYER_STEAL_COOLTIME;
		//真ん中
		steal[0]->Attack(this, STEAL_DISTANCE - 20.f, 100.f, 100.f, 30.f);
		//上
		steal[1]->Attack(this, STEAL_DISTANCE - 10.f, 60.f, 60.f, 0.f);
		//下
		steal[2]->Attack(this, STEAL_DISTANCE + 10.f, 70.f, 70.f, 30.f);
	}

	//一回だけ
	bool once = false;

	for (int i = 0; i < STEAL_VALUE; i++)
	{
		//鉤爪のいずれかが能力を奪えている
		if (steal[i]->GetKeepType() != Weapon::Empty)
		{
			//1度武器をストックしたら他の爪に武器があってもストックしない
			if (!once)
			{
				for (int j = 0; j < PLAYER_MAX_STOCK; j++)
				{
					//ストックに空きがある
					if (stock[j] == Weapon::Empty)
					{
						stock[j] = steal[i]->GetKeepType();
						once = true;
						break;
					}
				}
			}
			steal[i]->SetKeepType(Weapon::Empty);
		}
	}

	if (stealCoolTime > 0)stealCoolTime--;
}

void Player::StockSelect()
{
	//stockカウントを減らす
	if ((KeyInput::GetKey(KEY_INPUT_Q)) || PadInput::OnButton(XINPUT_BUTTON_LEFT_SHOULDER))
	{
		isEquipment = false;
		stockCount--;
		weaponType = Weapon::Empty;
		if (stockCount < 0)
		{
			stockCount = PLAYER_MAX_STOCK - 1;
		}
	}

	//stockカウントを増やす
	if ((KeyInput::GetKey(KEY_INPUT_E)) || PadInput::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		isEquipment = false;
		stockCount++;
		weaponType = Weapon::Empty;
		if (stockCount >= PLAYER_MAX_STOCK)
		{
			stockCount = 0;
		}
	}
}

void Player::Animation()
{
	playerAnimFramCount++;

	//待機
	if (!isMove && !isAir && !isKnockBack && !landingAnimFlg && !isAttack)
	{
		if (playerAnim >= 4)
		{
			playerAnim = 0;
		}
		
		if (playerAnimFramCount % 16 == 0)
		{
			playerAnim++;
			if (playerAnim >= 4)
			{
				playerAnim = 0;
			}
		}
	}

	//移動
	if (isMove && !isAir && !isKnockBack)
	{
		if (playerAnim <= 7 || playerAnim >= 16)
		{
			playerAnim = 8;
		}

		if (playerAnimFramCount % 8 == 0)
		{
			playerAnim++;
			if (playerAnim >= 16)
			{
				playerAnim = 8;
			}
		}
	}

	//空中
	if (isAir && !isKnockBack && !isAttack)
	{
		if (playerAnim <= 21 || playerAnim >= 30)
		{
			if (isJump)
			{
				playerAnim = 22;
				isJump = false;
			}
			else
			{
				playerAnim = 26;
			}
		}

		if (playerAnimFramCount % 8 == 0)
		{
			if (playerAnim < 27)
			{
				playerAnim++;
			}
		}
	}
	//着地
	if (landingAnimFlg && !isAir)
	{
		if (playerAnimFramCount % 8 == 0)
		{
			if (playerAnim < 30)
			{
				playerAnim++;
			}
		}
		//着地のアニメーションが終わったら
		if (playerAnim >= 30)
		{
			landingAnimFlg = false;
		}
	}

	//攻撃
	if (isAttack && !isKnockBack)
	{
		if (playerAnim <= 41)
		{
			playerAnim = 44;
			//奪う、ダガーは振っている画像から
			if (actionCount == 1 || stock[stockCount] == Weapon::Dagger)
			{
				playerAnim = 46;
			}
			//投げるは振り始めの画像から
			if (actionCount == 3)
			{
				playerAnim = 45;
			}
		}


		if (playerAnimFramCount % 5 == 0)
		{
			if (playerAnim < 49)
			{
				playerAnim++;
			}
		}
	}

	//ノックバック
	if (isKnockBack)
	{
		playerAnim = 3;
	}
}

float Player::GetWeaponWeight(const Weapon type)
{
	Weapon checkType = type;
	float weight = 0.f;

	switch (checkType)
	{
	case Weapon::Empty:
		weight = 0.f;
		break;

	case Weapon::LargeSword:
		weight = LARGESWORD_WEIGHT;
		break;

	case Weapon::Dagger:
		weight = DAGGER_WEIGHT;
		break;

	case Weapon::Rapier:
		weight = RAPIER_WEIGHT;
		break;

	default:
		weight = 0.f;
		break;
	}

	return weight;
}

float Player::GetWeaponDamage(const Weapon type)
{
	Weapon checkType = type;
	float damage = 0.f;

	switch (checkType)
	{
	case Weapon::Empty:
		damage = 0.f;
		break;

	case Weapon::LargeSword:
		damage = LARGESWORD_DAMAGE;
		break;

	case Weapon::Dagger:
		damage = DAGGER_DAMAGE;
		break;

	case Weapon::Rapier:
		damage = RAPIER_DAMAGE;
		break;

	default:
		damage = 0.f;
		break;
	}

	return damage;
}
