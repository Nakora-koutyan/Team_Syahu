#include "Player.h"
#include"../../Scene/GameMain/GameMainScene.h"

#define DEBUG

Player::Player()
{
	location = { 300.f,GROUND_LINE + area.height };
	area = { 100.f,100.f };

	weaponSlot = Ability::Empty;
	normalWeapon = new NormalWeapon();

	guardCount = 0;

	framCount = 0;
	damageFramCount = 0;
	parryFram = 0;

	guardCoolTime = 0.f;

	isGuard = false;
	guardCoolTimeFlg = false;
	parryFlg = false;
}

Player::~Player()
{
	delete normalWeapon;
}

void Player::Update(GameMainScene* object)
{
	framCount++;

	if (parryFlg)
	{
		parryFram++;
		//2秒後に再度パリィ可能
		if (parryFram > FPS * 2)
		{
			parryFlg = false;
			parryFram = 0;
		}
	}

	Movement();

	Action();

	normalWeapon->Update(object);

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
		isGuard ? parryFlg ? 0x00ff00 : 0x0000ff : 0xffff00, FALSE
	);

	DrawFormatString(0, 0, 0xff0000, "%f", hp);
	DrawFormatString(0, 40, 0xff0000, "%f", guardCoolTime);
	DrawFormatString(0, 10, 0xff0000, "%s", parryFlg ? "true" : "false");
	DrawFormatString(0, 20, 0xff0000, "direction x:%f y:%f", direction.x,direction.y);

#endif // DEBUG

	if (isAttack)
	{
		normalWeapon->Draw();
	}
}

void Player::Hit(GameMainScene* object)
{
	if (isHit)
	{
		//PLAYER_DAMAGE_INTERVALの時間無敵
		if (framCount % PLAYER_DAMAGE_INTERVAL == 0)
		{
			isHit = false;
		}
	}

	//雑魚的に当たったら
	if (HitCheck(object->GetNormalEnemy()))
	{
		//すでに当たってないなら
		if (!isHit)
		{
			//ダメージ用のカウントを計測する
			damageFramCount++;

			//PLAYER_PARRY_FLAME以内にガードできたらかつパリィしていないなら
			if (damageFramCount <= PLAYER_PARRY_FLAME && 
				(KeyInput::GetKey(KEY_INPUT_LSHIFT) || PadInput::OnPressed(XINPUT_BUTTON_LEFT_SHOULDER) || PadInput::OnPressed(XINPUT_BUTTON_RIGHT_SHOULDER)) && 
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
	}
}

void Player::Movement()
{
	//右へ移動
	if ((KeyInput::GetKeyDown(KEY_INPUT_D) || PadInput::GetLStickRationX() > NEED_STICK_RATIO) && !isGuard && !isAttack)
	{
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
	}
	//左へ移動
	else if ((KeyInput::GetKeyDown(KEY_INPUT_A) || PadInput::GetLStickRationX() < -NEED_STICK_RATIO) && !isGuard && !isAttack)
	{
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
	}
	//停止
	else
	{
		vector.x = 0.f;
	}

	//ジャンプ
	if ((KeyInput::GetKey(KEY_INPUT_SPACE) || KeyInput::GetKey(KEY_INPUT_W) || PadInput::OnButton(XINPUT_BUTTON_A)) && !isAir && !isGuard && !isAttack)
	{
		vector.y = -JUMP_POWER;
		isAir = true;
		direction.y = -1.f;
	}

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

void Player::Action()
{
	//ガードしているなら
	if ((KeyInput::GetKeyDown(KEY_INPUT_LSHIFT) || PadInput::OnPressed(XINPUT_BUTTON_LEFT_SHOULDER) || PadInput::OnPressed(XINPUT_BUTTON_RIGHT_SHOULDER)) && guardCoolTime <= 0.f)
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

	//攻撃しているなら
	if ((KeyInput::GetButton(MOUSE_INPUT_LEFT) || PadInput::OnPressed(XINPUT_BUTTON_B)))
	{
		isAttack = true;
		if (abilityType == Ability::Empty)
		{
			normalWeapon->Attack(this);
		}
	}
	//攻撃していないなら
	else
	{
		//isAttack = false;
	}

	//奪う攻撃をしているなら
	if ((KeyInput::GetKeyDown(KEY_INPUT_E) || PadInput::OnPressed(XINPUT_BUTTON_Y)))
	{

	}
	//奪う攻撃をしていないなら
	else
	{

	}

}
