#include "Player.h"
#include"../../Scene/GameMain/GameMainScene.h"

Player::Player()
{
	location = { 300.f,GROUND_LINE + area.height };
	area = { 100.f,100.f };

	framCount = 0;
	damageFramCount = 0;

	damageInterval = PLAYER_DAMAGE_INTERVAL;

	isGuard = false;
}

Player::~Player()
{

}

void Player::Update(GameMainScene* object)
{
	Movement();

	Action();

	Hit(object);

	screenLocation = object->GetCamera()->ConvertScreenPosition(location);
}

void Player::Draw() const
{
	DrawBoxAA
	(
		screenLocation.x, screenLocation.y,
		screenLocation.x + area.width, screenLocation.y + area.height,
		isGuard ? 0x0000ff : 0xffff00, FALSE
	);
}

void Player::Hit(GameMainScene* object)
{
	if (isHit)
	{
		//PLAYER_DAMAGE_INTERVAL後にヒットフラグをfalseにする
		if (framCount % PLAYER_DAMAGE_INTERVAL == 0)
		{
			isHit = false;
		}
	}

	//雑魚敵との当たり判定
	if (HitCheck(object->GetNormalEnemy()))
	{
		//まだダメージを受けていないなら
		if (!isHit)
		{
			damageFramCount++;

			//PLAYER_PARRY_FLAME以内にガードしているなら
			if (damageFramCount <= PLAYER_PARRY_FLAME && isGuard)
			{

			}

			//パリィできなかったら
			if (damageFramCount > PLAYER_PARRY_FLAME)
			{
				if (!isGuard)
				{
					hp -= object->GetNormalEnemy()->GetDamage();
				}
				else
				{
					hp -= object->GetNormalEnemy()->GetDamage() * PLAYER_DAMAGE_CUT;
				}

				damageFramCount = 0;
			}
		}
	}
}

void Player::Movement()
{
	//右へ移動
	if ((KeyInput::GetKeyDown(KEY_INPUT_D) || PadInput::GetLStickRationX() > NEED_STICK_RATIO) && !isGuard)
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
		}
	}
	//左へ移動
	else if ((KeyInput::GetKeyDown(KEY_INPUT_A) || PadInput::GetLStickRationX() < -NEED_STICK_RATIO) && !isGuard)
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
		}
	}
	//停止
	else
	{
		vector.x = 0.f;
	}

	//ジャンプ
	if ((KeyInput::GetKey(KEY_INPUT_SPACE) || KeyInput::GetKey(KEY_INPUT_W) || PadInput::OnButton(XINPUT_BUTTON_A)) && !isAir && !isGuard)
	{
		vector.y = -JUMP_POWER;
		isAir = true;
	}

	//重力
	vector.y += GRAVITY;

	//移動量を座標に加算
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
	}
}

void Player::Action()
{
	//ガードボタンを押しているなら
	if ((KeyInput::GetKeyDown(KEY_INPUT_LSHIFT) || PadInput::OnPressed(XINPUT_BUTTON_LEFT_SHOULDER)|| PadInput::OnPressed(XINPUT_BUTTON_RIGHT_SHOULDER)))
	{
		isGuard = true;
	}
	//ガードボタンを離したら
	else if((KeyInput::GetKeyUp(KEY_INPUT_LSHIFT) || PadInput::OnRelease(XINPUT_BUTTON_LEFT_SHOULDER) || PadInput::OnRelease(XINPUT_BUTTON_RIGHT_SHOULDER)))
	{
		isGuard = false;
	}

	if ((KeyInput::GetKeyDown(KEY_INPUT_E) || PadInput::OnPressed(XINPUT_BUTTON_Y)))
	{

	}

}
