#include"Player.h"
#include"../../Camera/Camera.h"
#include"../../../ResourceManager/ResourceManager.h"
#include"../Enemy/EnemyBase.h"

Player::Player() :steal(nullptr), largeSword(nullptr), rapier(nullptr)
{
	objectType = ObjectType::Player;

	area.width = 56.f;
	area.height = 84.f;
	location.x = 300.f;
	location.y = GROUND_LINE - area.height;
	direction.x = 1.f;
	direction.y = 0.f;
	hp = PLAYER_MAX_HP;
	damage = PLAYER_DAMAGE;

	for (int i = 0; i < PLAYER_MAX_STOCK; i++)
	{
		stock[i] = Weapon::None;
		weaponDurability[i] = PLAYER_WEAPON_DURABILITY;
	}

	for (int i = 0; i < PLAYER_MAX_DAGGER; i++)
	{
		dagger[i] = nullptr;
	}

	jumpEffectLocation.x = 0.f;
	jumpEffectLocation.y = 0.f;

	stockCount = 0;
	actionState = Action::None;

	framCount = 0;
	playerAnimFramCount = 0;
	playerAnim = 0;
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
		playerImage[playerAnim] = ResourceManager::GetDivImage("Player/player", i);
		playerAnim++;
	}
	playerAnim = 0;
	for (int i = 0; i < 5; i++)
	{
		daggerCount[i] = PLAYER_MAX_DAGGER - 1;
	}
	jumpEffectAnimCount = 0;
	jumpEffectAnim = 0;
	equipmentEffectAnimCount = 0;
	equipmentEffectAnim = 0;

	attackCoolTime = 0.f;
	stealCoolTime = 0.f;

	isEquipment = false;
	isBackStep = false;
	landingAnimFlg = false;
	blinkingFlg = false;
	jumpEffectInversionFlg = false;
	equipmentAnimFlg = false;
	equipmentEffectFlg = false;
}

Player::~Player()
{

}

void Player::Initialize()
{
	steal = new Steal();
	largeSword = new LargeSword();
	rapier = new Rapier();

	for (int i = 0; i < PLAYER_MAX_DAGGER; i++)
	{
		dagger[i] = new Dagger();
		weapon.push_back(dagger[i]);
	}

	weapon.push_back(largeSword);
	weapon.push_back(rapier);
}

void Player::Finalize()
{
	delete steal;
	delete largeSword;
	for (int i = 0; i < PLAYER_MAX_DAGGER; i++)
	{
		delete dagger[i];
	}
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
		((largeSword->GetIsHit() && !largeSword->GetIsAirAttack()) || rapier->GetIsHit()))
	{
		if (actionState == Action::Equipment)
		{
			actionState = Action::None;
		}
		//当たっている間耐久値が減るのを防ぐため
		largeSword->SetIsHit(false);
		rapier->SetIsHit(false);
		weaponDurability[stockCount] -= GetDurability(stock[stockCount], true);
	}

	//攻撃終了後に耐久値が0以下なら
	if (!isAttack && weaponDurability[stockCount] <= 0)
	{
		weaponType = Weapon::None;
		weaponDurability[stockCount] = PLAYER_WEAPON_DURABILITY;
		stock[stockCount] = Weapon::None;
		isEquipment = false;
	}
	//短剣の残り本数が0以下なら
	else if (daggerCount[stockCount] < 0)
	{
		daggerCount[stockCount] = PLAYER_MAX_DAGGER - 1;
		weaponType = Weapon::None;
		weaponDurability[stockCount] = PLAYER_WEAPON_DURABILITY;
		stock[stockCount] = Weapon::None;
		isEquipment = false;
	}
	//捨てる
	else if ((KeyInput::GetKey(KEY_INPUT_R)) || PadInput::OnButton(XINPUT_BUTTON_Y))
	{
		weaponType = Weapon::None;
		weaponDurability[stockCount] = PLAYER_WEAPON_DURABILITY;
		stock[stockCount] = Weapon::None;
		isEquipment = false;
	}

	DamageInterval(int(PLAYER_DAMAGE_INTERVAL));

	KnockBack(this, PLAYER_KNOCKBACK_TIME, knockBackMove);

	BackStep(30.f, 15.f, 0.f);

	if (!equipmentAnimFlg)
	{
		Movement();

		Attack();

		StockSelect();
	}

	Animation();

	steal->Update(this);
	largeSword->Update(this);
	for (int i = 0; i < PLAYER_MAX_DAGGER; i++)
	{
		dagger[i]->Update(this);
	}
	rapier->Update(this, PLAYER_MAX_MOVE_SPEED);

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

	DrawFormatString(600, 0, 0x000000, "hp :%f", hp);
	DrawFormatString(600, 15, 0x000000, "attackCoolTime :%f", attackCoolTime);
	DrawFormatString(600, 30, 0x000000, "stealCoolTime :%f", stealCoolTime);
	DrawFormatString(850, 45, 0x000000, "1:LargeSword 2:Dagger 3:Rapier");
	DrawFormatString(600, 60, 0x000000, "weaponCount[%d] :%d", stockCount, weaponDurability[stockCount]);
	DrawFormatString(600, 75, 0x000000, "stock :%d %d %d %d %d", stock[0], stock[1], stock[2], stock[3], stock[4]);
	DrawFormatString(600, 90, 0x000000, "daggerCount :%d %d %d %d %d", daggerCount[0], daggerCount[1], daggerCount[2], daggerCount[3], daggerCount[4]);
	DrawFormatString(600, 105, 0x000000, "animCount :%d", playerAnim);
	DrawFormatString(600, 120, 0x000000, "landingFlg :%s", landingAnimFlg ? "true" : "false");
	DrawFormatString(600, 135, 0x000000, "location x:%f location y:%f", location.x, location.y);
	DrawFormatString(600, 150, 0x000000, "jumpEffectAnim:%d", jumpEffectAnim);
	DrawFormatString(600, 165, 0x000000, "isAttack :%s", isAttack ? "true" : "false");
	if (weaponType == Weapon::None)
	{
		DrawFormatString(600, 45, 0x000000, "WeaponType:None");
	}
	else
	{
		if (weaponType == Weapon::LargeSword)
		{
			DrawFormatString(600, 45, 0x000000, "WeaponType:LargeSword");
		}
		if (weaponType == Weapon::Dagger)
		{
			DrawFormatString(600, 45, 0x000000, "WeaponType:Dagger");
		}
		if (weaponType == Weapon::Rapier)
		{
			DrawFormatString(600, 45, 0x000000, "WeaponType:Rapier");
		}
	}

#endif // DEBUG

	//画像反転フラグ
	if (imageInversionFlg)
	{
		if (equipmentEffectFlg)
		{
			DrawRotaGraphF
			(GetCenterScreenLocation().x, GetCenterScreenLocation().y, 1, 0,
				ResourceManager::GetDivImage("Effect/transformEffect", 
					equipmentEffectAnim), TRUE, TRUE);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaBlend);
		DrawRotaGraphF
		(GetMinScreenLocation().x + PLAYER_IMAGE_ALIGN_THE_ORIGIN_X - 6.f,
			GetMinScreenLocation().y + PLAYER_IMAGE_ALIGN_THE_ORIGIN_Y - 12.f,
			1, 0, playerImage[playerAnim], TRUE, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		if (equipmentEffectFlg)
		{
			DrawRotaGraphF
			(GetCenterScreenLocation().x, GetCenterScreenLocation().y, 1, 0,
				ResourceManager::GetDivImage("Effect/transformEffect",
					equipmentEffectAnim), TRUE);
		}
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaBlend);
		DrawRotaGraphF
		(GetMinScreenLocation().x + PLAYER_IMAGE_ALIGN_THE_ORIGIN_X,
			GetMinScreenLocation().y + PLAYER_IMAGE_ALIGN_THE_ORIGIN_Y - 12.f,
			1, 0, playerImage[playerAnim], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	if (isJump)
	{
		if (jumpEffectInversionFlg)
		{
			DrawRotaGraphF
			(Camera::ConvertScreenPosition(jumpEffectLocation).x + 10.f, 
				Camera::ConvertScreenPosition(jumpEffectLocation).y - 15.f,
				1, 0,
				ResourceManager::GetDivImage("Effect/jumpEffect", jumpEffectAnim),
				TRUE, TRUE);
		}
		else
		{
			DrawRotaGraphF
			(Camera::ConvertScreenPosition(jumpEffectLocation).x - 10.f, 
				Camera::ConvertScreenPosition(jumpEffectLocation).y - 15.f,
				1, 0,
				ResourceManager::GetDivImage("Effect/jumpEffect", jumpEffectAnim),
				TRUE);
		}
	}

	steal->Draw();

	largeSword->Draw();

	for (int i = 0; i < PLAYER_MAX_DAGGER; i++)
	{
		dagger[i]->Draw();
	}

	rapier->Draw();
}

void Player::Hit(ObjectBase* object, const float damage)
{
	EnemyBase* chara = static_cast<EnemyBase*>(object);

	if (!isKnockBack && !isHit && hp > 0 && !invincibleFlg)
	{
		isKnockBack = true;
		if (GetCenterLocation().x < chara->GetCenterLocation().x)
		{
			knockBackDirection = -1;
		}
		else
		{
			knockBackDirection = 1;
		}
		if (knockBackMove == 0)knockBackMove = PLAYER_KNOCKBACK;
	}

	//すでに当たってないならかつ同じオブジェクトじゃないなら
	if (!isHit && objectType != chara->GetObjectType() && hp > 0 && !invincibleFlg)
	{
		ResourceManager::PlaySE("damage", FALSE);

		isHit = true;

		if (hp > 0)hp -= damage;
	}

	if (hp < 0)
	{
		hp = 0;
	}

	if (location.x <= 0 || location.x + area.width >= WORLD_WIDTH)
	{
		if (CollisionCheck(chara))
		{
			chara->Hit(this, 0);
		}
	}

	//中心の距離
	float disX = chara->GetCenterLocation().x - GetCenterLocation().x;

	//2点間の長さ
	float length = (GetArea().width / 2) + (chara->GetArea().width / 2);

	if (isAttack && isEquipment && stock[stockCount] == Weapon::Rapier)
	{
		length += RAPIER_LENGTH;
	}

	if (abs(disX) < length && !invincibleFlg)
	{
		float dif = length - abs(disX);

		//左
		if (GetCenterLocation().x < chara->GetCenterLocation().x)
		{
			SetLocationX(location.x - dif);
		}
		//右
		else
		{
			SetLocationX(location.x + dif);
		}
	}
}

void Player::Landing(const float height)
{
	//地面を超えない
	if (GetMaxLocation().y > height)
	{
		location.y = height - area.height;
		jumpEffectLocation.y = height;
		move.y = 0.f;
		isAir = false;
		//空中の画像かつ動いていないなら
		if (playerAnim == 27 && !isMove && !isHit && !isKnockBack)
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
		!isKnockBack && !isAttack && !isBackStep && hp > 0)
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
			!isKnockBack && !isAttack && !isBackStep && hp > 0)
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
		if (isAir && isAttack && move.x != 0 && hp > 0)
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
		else if (stock[stockCount] == Weapon::Rapier && rapier->GetChargeTime() > RAPIER_CHARGE_TIME &&
			isEquipment && isAttack && hp > 0)
		{
			//アイドル状態にしないための条件式なので何も書かなくても問題ない
		}
		//ノックバックしていないならアイドル状態
		else if (!isKnockBack && !isBackStep && hp > 0)
		{
			move.x = 0.f;
			isMove = false;
		}
	}

#ifdef DEBUG
	//ジャンプ
	if ((KeyInput::GetKey(KEY_INPUT_SPACE) ||
		KeyInput::GetKey(KEY_INPUT_W) ||
		PadInput::OnButton(XINPUT_BUTTON_A)) && /*!isAir &&*/ !isKnockBack && !isAttack && !isBackStep && hp > 0)
#else
	//ジャンプ
	if ((KeyInput::GetKey(KEY_INPUT_SPACE) ||
		KeyInput::GetKey(KEY_INPUT_W) ||
		PadInput::OnButton(XINPUT_BUTTON_A)) && !isAir && !isKnockBack && !isAttack && !isBackStep && hp > 0)
#endif // DEBUG
	{
		ResourceManager::PlaySE("jump", FALSE);
		move.y = -JUMP_POWER;
		isAir = true;
		isJump = true;
		direction.y = -1.f;
		if (direction.x < 0)
		{
			jumpEffectLocation.x = location.x + area.width;
			jumpEffectInversionFlg = true;
		}
		else
		{
			jumpEffectLocation.x = location.x;
			jumpEffectInversionFlg = false;
		}
	}

	//下に落ちているなら
	if (move.y > 0)
	{
		direction.y = 1.f;
	}

	//重力
	Gravity();

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

	Landing(WORLD_HEIGHT);
}

void Player::Attack()
{
	if (!isAttack)
	{
		actionState = Action::None;
	}

	//武器攻撃
	if ((KeyInput::GetButton(MOUSE_INPUT_RIGHT) || PadInput::OnButton(XINPUT_BUTTON_X)) &&
		attackCoolTime <= 0.f && !isKnockBack && actionState == Action::None && hp > 0)
	{
		//武器攻撃
		if (weaponType != Weapon::None)
		{
			actionState = Action::WeaponAttack;
			isAttack = true;
			//大剣
			if (stock[stockCount] == Weapon::LargeSword)
			{
				attackCoolTime = PLAYER_LARGESWORD_COOLTIME;
				largeSword->Attack(this);
				if (largeSword->GetIsAirAttack())
				{
					weaponDurability[stockCount] -= GetDurability(stock[stockCount], true);
				}
			}
			//短剣
			else if (stock[stockCount] == Weapon::Dagger)
			{
				attackCoolTime = PLAYER_DAGGER_COOLTIME;
				dagger[daggerCount[stockCount]]->Attack(this);
				daggerCount[stockCount]--;
			}
			//レイピア
			else if (stock[stockCount] == Weapon::Rapier)
			{
				attackCoolTime = PLAYER_RAPIER_COOLTIME;
				rapier->Attack(this);
			}
		}
	}

	if (attackCoolTime > 0)attackCoolTime--;

	//装備
	if (!isKnockBack && stock[stockCount] != Weapon::None && weaponType == Weapon::None &&
		actionState == Action::None && hp > 0 &&
		(KeyInput::GetButton(MOUSE_INPUT_LEFT) || PadInput::OnButton(XINPUT_BUTTON_B)))
	{
		weaponType = stock[stockCount];
		isEquipment = true;
		actionState = Action::Equipment;
		invincibleFlg = true;
		equipmentAnimFlg = true;
	}


	//奪う
	if ((KeyInput::GetButton(MOUSE_INPUT_LEFT) || PadInput::OnButton(XINPUT_BUTTON_B)) &&
		stealCoolTime <= 0.f && !isKnockBack && actionState == Action::None && hp > 0)
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
				weaponDurability[stockCount] = GetDurability(stock[stockCount]);
				if (!isEquipment)
				{
					stockCount = j;
					isEquipment = true;
					actionState = Action::Equipment;
					invincibleFlg = true;
					equipmentAnimFlg = true;
				}
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
		ResourceManager::PlaySE("stockSelect", FALSE);
		stockCount--;
		if (stockCount < 0)
		{
			stockCount = PLAYER_MAX_STOCK - 1;
		}	
		if (stock[stockCount] == Weapon::None)
		{
			isEquipment = false;
			weaponType = Weapon::None;
		}
		else if (stock[stockCount] != Weapon::None && isEquipment)
		{
			weaponType = stock[stockCount];
		}

	}

	//stockカウントを増やす
	if ((KeyInput::GetKey(KEY_INPUT_E)) || PadInput::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER))
	{
		ResourceManager::PlaySE("stockSelect", FALSE);
		stockCount++;
		if (stockCount >= PLAYER_MAX_STOCK)
		{
			stockCount = 0;
		}
		if (stock[stockCount] == Weapon::None)
		{
			isEquipment = false;
			weaponType = Weapon::None;
		}
		else if (stock[stockCount] != Weapon::None && isEquipment)
		{
			weaponType = stock[stockCount];
		}
	}
}

void Player::Animation()
{
	playerAnimFramCount++;

	//待機
	if (!isMove && !isAir && !isKnockBack && !landingAnimFlg && !isAttack && hp > 0 && !equipmentAnimFlg)
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
	if (isMove && !isAir && !isKnockBack && hp > 0 && !equipmentAnimFlg)
	{
		if (playerAnim <= 7 || playerAnim >= 16)
		{
			playerAnim = 8;
		}

		if (playerAnimFramCount % 8 == 0)
		{
			playerAnim++;
			if (playerAnim == 9 || playerAnim == 11 || playerAnim == 15)
			{
				ResourceManager::PlaySE("walk", FALSE);
			}
			if (playerAnim >= 16)
			{
				playerAnim = 8;
			}
		}
	}

	//空中
	if (isAir && !isKnockBack && !isAttack && hp > 0 && !equipmentAnimFlg)
	{
		landingAnimFlg = false;
		if (playerAnim <= 21 || playerAnim >= 27)
		{
			//ジャンプ
			if (isJump)
			{
				playerAnim = 23;
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
	if (landingAnimFlg && !isAir && hp > 0 && !isKnockBack && !equipmentAnimFlg)
	{
		if (playerAnimFramCount % 8 == 0)
		{
			if (playerAnim == 27)
			{
				ResourceManager::PlaySE("walk", FALSE);
			}
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

	//装備
	if (isEquipment && equipmentAnimFlg && !isAttack)
	{
		if (playerAnim <= 16 || playerAnim >= 22)
		{
			ResourceManager::PlaySE("equipment", FALSE);

			playerAnim = 17;
		}
		if (playerAnimFramCount % 8 == 0)
		{
			if (playerAnim < 22)
			{
				playerAnim++;
				if (playerAnim == 19)
				{
					equipmentEffectFlg = true;
				}
			}
		}
		//装備のアニメーションが終わったら
		if (playerAnim >= 22)
		{
			equipmentAnimFlg = false;
			invincibleFlg = false;
		}
	}

	//装備のエフェクト
	if (equipmentEffectFlg)
	{
		equipmentEffectAnimCount++;
		if (equipmentEffectAnimCount % 5 == 0)
		{
			if (equipmentEffectAnim < 8)
			{
				equipmentEffectAnim++;
			}
			else
			{
				equipmentEffectFlg = false;
				equipmentEffectAnim = 0;
				equipmentEffectAnimCount = 0;
			}
		}
	}

	bool once = false;

	//攻撃
	if (isAttack && !isKnockBack && hp > 0 && !equipmentAnimFlg)
	{
		if (playerAnim <= 41)
		{
			once = true;
			playerAnim = 46;
		}


		if (playerAnimFramCount % 5 == 0 && !once)
		{
			if (playerAnim < 49)
			{
				if (largeSword->GetIsAirAttack())
				{
					if (playerAnim < 46)
					{
						playerAnim++;
					}
				}
				else
				{
					playerAnim++;
				}
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
	if (isHit && hp > 0 && !isKnockBack)
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

	//死亡
	if (hp <= 0 && !isKnockBack)
	{
		if (playerAnim <= 34 || playerAnim >= 42)
		{
			playerAnim = 35;
		}
		if (playerAnimFramCount % 8 == 0)
		{
			if (playerAnim < 41)
			{
				playerAnim++;
			}
			else
			{
				deathFlg = true;
			}
		}
	}

	//ジャンプのエフェクト
	if (!isKnockBack && isJump)
	{
		if (jumpEffectAnimCount % 15 == 0)
		{
			if (jumpEffectAnim < 13)
			{
				jumpEffectAnim++;
			}
			else
			{
				isJump = false;
				jumpEffectAnim = 0;
			}
		}
	}
}

void Player::BackStep(const float angle, const float speed, const float gravityVelocity)
{
	//ダメージを受けたら強制解除
	if (isHit)
	{
		isBackStep = false;
		rapier->SetStepFlg(false);
	}

	if (rapier->GetStepFlg() && !isKnockBack && !isAir)
	{
		isBackStep = true;
		if (direction.x < 0)
		{
			move.x = speed * cos(DEGREE_TO_RADIAN(angle));
		}
		else
		{
			move.x = -speed * cos(DEGREE_TO_RADIAN(angle));
		}

		move.y = -speed * sin(DEGREE_TO_RADIAN(angle));

		rapier->SetStepFlg(false);
	}

	if (isBackStep && !isKnockBack)
	{
		move.y += gravityVelocity;
		invincibleFlg = true;
		if (isAir)
		{
			isBackStep = false;
			invincibleFlg = false;
		}
	}
}

int Player::GetDurability(const Weapon type, const bool useFlg)
{
	Weapon checkType = type;
	bool flg = useFlg;
	int durability = 0;

	switch (checkType) 
	{
	case Weapon::None:
		durability = 0;
		break;

	case Weapon::LargeSword:
		durability = PLAYER_WEAPON_DURABILITY;
		if (flg)durability /= 2;
		break;

	case Weapon::Dagger:
		durability = PLAYER_WEAPON_DURABILITY;
		if (flg)durability = 0;
		break;

	case Weapon::Rapier:
		durability = PLAYER_WEAPON_DURABILITY;
		if (flg)durability /= 4;
		break;

	default:
		durability = 0;
		break;
	}

	return durability;
}