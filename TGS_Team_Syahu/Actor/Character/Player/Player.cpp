#include"Player.h"
#include"../../Camera/Camera.h"

#define DEBUG

Player::Player():normalWeapon(nullptr),steal(nullptr),largeSword(nullptr),dagger(nullptr),rapier(nullptr)
{
	objectType = ObjectType::Player;

	location.x = 300.f;
	location.y = GROUND_LINE;
	area.width = 56.f;
	area.height = 84.f;
	direction.x = 1.f;
	direction.y = 0.f;
	hp = PLAYER_MAX_HP;
	damage = 10.f;

	for (int i = 0; i < PLAYER_MAX_STOCK; i++)
	{
		stock[i] = Weapon::None;
		weaponFramCount[i] = PLAYER_WEAPON_TIME;
	}

	stockCount = 0;
	actionState = Action::None;

	framCount = 0;
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
	blinkingFlg = false;
}

Player::~Player()
{

}

void Player::Initialize()
{
	normalWeapon = new NormalWeapon();
	steal = new Steal();
	largeSword = new LargeSword();
	dagger = new Dagger();
	rapier = new Rapier();

	weapon.push_back(normalWeapon);
	weapon.push_back(steal);
	weapon.push_back(largeSword);
	weapon.push_back(dagger);
	weapon.push_back(rapier);
}

void Player::Finalize()
{
	delete normalWeapon;
	delete steal;
	delete largeSword;
	delete dagger;
	delete rapier;
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
#endif // DEBUG

	if (isEquipment && isAttack && stock[stockCount] != Weapon::None &&
		(largeSword->GetIsHit() || dagger->GetIsHit() || rapier->GetIsHit()))
	{
		if (actionState == Action::Equipment)
		{
			actionState = Action::None;
		}
		largeSword->SetIsHit(false);
		dagger->SetIsHit(false);
		rapier->SetIsHit(false);
		weaponFramCount[stockCount] = weaponFramCount[stockCount] - (PLAYER_WEAPON_TIME / 2);
	}

	if (!isAttack && weaponFramCount[stockCount] <= 0)
	{
		weaponType = Weapon::None;
		weaponFramCount[stockCount] = PLAYER_WEAPON_TIME;
		stock[stockCount] = Weapon::None;
		isEquipment = false;
	}

	DamageInterval(int(PLAYER_DAMAGE_INTERVAL));

	KnockBack(this, PLAYER_KNOCKBACK_TIME, PLAYER_KNOCKBACK);

	Movement();

	Attack();

	StockSelect();

	Animation();

	normalWeapon->Update(this);
	steal->Update(this);
	largeSword->Update(this);
	dagger->Update(this);
	rapier->Update(this);

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
	DrawFormatString(0, 90, 0x000000, "animCount :%d", playerAnim);
	DrawFormatString(0, 105, 0x000000, "landingFlg :%s", landingAnimFlg ? "true" : "false");
	if (weaponType == Weapon::None)
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

	//画像反転フラグ
	if (imageInversionFlg)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaBlend);
		DrawRotaGraphF
		(GetMinScreenLocation().x + PLAYER_IMAGE_ALIGN_THE_ORIGIN_X - 6.f,
			GetMinScreenLocation().y + PLAYER_IMAGE_ALIGN_THE_ORIGIN_Y - 12.f,
			1, 0, playerImage[playerAnim], TRUE, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaBlend);
		DrawRotaGraphF
		(GetMinScreenLocation().x + PLAYER_IMAGE_ALIGN_THE_ORIGIN_X,
			GetMinScreenLocation().y + PLAYER_IMAGE_ALIGN_THE_ORIGIN_Y - 12.f,
			1, 0, playerImage[playerAnim], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	normalWeapon->Draw();

	steal->Draw();

	largeSword->Draw();

	dagger->Draw();

	rapier->Draw();
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
		if (playerAnim == 27 && !isMove && !isHit)
		{
			landingAnimFlg = true;
		}
		direction = { direction.x,0.f };
	}

	if (direction.y != 0.f)
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
				move.x += PLAYER_AIR_MOVE_SPEED;
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
				move.x += -PLAYER_AIR_MOVE_SPEED;
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
		//空中で動きながら攻撃しているなら移動量を少しずつ減らす
		if (isAir && isAttack && move.x != 0)
		{
			if (direction.x < 0)
			{
				move.x += 0.05f;
			}
			else
			{
				move.x += -0.05f;
			}
		}
		//レイピアの攻撃は例外で動けるようにするためにこの条件式を設ける
		else if ((stock[stockCount] == Weapon::Rapier && isEquipment && isAttack))
		{
			//アイドル状態にしないための条件式なので何も書かなくても問題ない
		}
		//ノックバックしていないならアイドル状態
		else if (!isKnockBack)
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
	if (!isAttack)
	{
		actionState = Action::None;
	}

	//投げるまたは武器攻撃
	if ((KeyInput::GetButton(MOUSE_INPUT_RIGHT) ||
		PadInput::OnButton(XINPUT_BUTTON_X)) && attackCoolTime <= 0.f && !isKnockBack && actionState == Action::None)
	{
		//武器を持っているないなら投げる
		if (stock[stockCount] != Weapon::None && !isEquipment)
		{		
			isAttack = true;
			actionState = Action::Throw;
			attackCoolTime = PLAYER_NORMALWEAPON_COOLTIME;
			normalWeapon->Attack(this, GetWeaponWeight(stock[stockCount]), GetWeaponDamage(stock[stockCount]));
			stock[stockCount] = Weapon::None;
			weaponFramCount[stockCount] = PLAYER_WEAPON_TIME;
		}

		//武器攻撃
		if (weaponType != Weapon::None)
		{
			actionState = Action::WeaponAttack;
			isAttack = true;
			if (stock[stockCount] == Weapon::LargeSword)
			{
				attackCoolTime = PLAYER_LARGESWORD_COOLTIME;
				largeSword->Attack(this);
			}
			else if (stock[stockCount] == Weapon::Dagger)
			{
				attackCoolTime = PLAYER_DAGGER_COOLTIME;
				dagger->Attack(this);
			}
			else if (stock[stockCount] == Weapon::Rapier)
			{
				isInvincible = true;
				attackCoolTime = PLAYER_RAPIER_COOLTIME;
				rapier->Attack(this);
			}
		}
	}

	if (attackCoolTime > 0)attackCoolTime--;

	//奪う
	if ((KeyInput::GetButton(MOUSE_INPUT_LEFT) || PadInput::OnButton(XINPUT_BUTTON_B)) &&
		stealCoolTime <= 0.f && !isKnockBack && actionState == Action::None)
	{
		isAttack = true;
		actionState = Action::Steal;
		stealCoolTime = PLAYER_STEAL_COOLTIME;
		steal->Attack(this);
	}

	if(steal->GetKeepType()!=Weapon::None)
	{
		for (int j = 0; j < PLAYER_MAX_STOCK; j++)
		{
			//ストックに空きがある
			if (stock[j] == Weapon::None)
			{
				stock[j] = steal->GetKeepType();
				steal->SetKeepType(Weapon::None);
				weaponType = stock[stockCount];
				isEquipment = true;
				actionState = Action::Equipment;
				break;
			}
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
		weaponType = Weapon::None;
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
		weaponType = Weapon::None;
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
		
		if (playerAnimFramCount % 14 == 0)
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
		landingAnimFlg = false;
		if (playerAnim <= 21 || playerAnim >= 27)
		{
			if (isJump)
			{
				playerAnim = 23;
				isJump = false;
			}
			else
			{
				playerAnim = 27;
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

	bool once = false;

	//攻撃
	if (isAttack && !isKnockBack)
	{
		if (playerAnim <= 41)
		{
			once = true;
			//奪う、ダガーは振っている画像から
			if (actionState == Action::Steal || (actionState == Action::WeaponAttack && stock[stockCount] == Weapon::Dagger))
			{
				playerAnim = 46;
			}
			//投げる、大剣は振り始めの画像から
			if (actionState == Action::Throw || (actionState == Action::WeaponAttack && stock[stockCount] == Weapon::LargeSword))
			{
				playerAnim = 45;
			}
			if (actionState == Action::WeaponAttack && stock[stockCount] == Weapon::Rapier)
			{
				playerAnim = 44;
			}
		}


		if (playerAnimFramCount % 5 == 0 && !once)
		{
			if (playerAnim < 49)
			{
				playerAnim++;
			}
			else
			{
				//攻撃アニメーションが終わったらisAttackをfalseにする
				isAttack = false;
			}
		}

		//かり
		if (actionState == Action::WeaponAttack && stock[stockCount] == Weapon::Rapier)
		{
			playerAnim = 44;
		}
	}

	//ノックバック
	if (isKnockBack)
	{
		playerAnim = 3;
	}

	//点滅
	if (isHit)
	{
		//攻撃を受けたら着地アニメーションはしない
		landingAnimFlg = false;
		if (playerAnimFramCount % 8 == 0)
		{

			blinkingFlg = !blinkingFlg;
			blinkingFlg ? alphaBlend = 124 : alphaBlend = 255;
		}
	}
	else
	{
		alphaBlend = 255;
	}
}

float Player::GetWeaponWeight(const Weapon type)
{
	Weapon checkType = type;
	float weight = 0.f;

	switch (checkType)
	{
	case Weapon::None:
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
	case Weapon::None:
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
