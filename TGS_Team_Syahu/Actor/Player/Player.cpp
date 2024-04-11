#include "Player.h"
#include"../../Scene/GameMain/GameMainScene.h"

Player::Player()
{
	location = { 300.f,GROUND_LINE };
	area = { 100.f,100.f };
}

Player::~Player()
{

}

void Player::Update(GameMainScene* object)
{
	Movement();

	screenLocation = object->GetCamera()->ConvertScreenPosition(location);
}

void Player::Draw() const
{
	DrawBoxAA
	(
		screenLocation.x, screenLocation.y,
		screenLocation.x + area.width / 2, screenLocation.y + area.height / 2,
		0xffff00, FALSE
	);
}

void Player::Movement()
{
	//右へ移動
	if ((KeyInput::GetKeyDown(KEY_INPUT_D) || PadInput::GetLStickRationX() > NEED_STICK_RATIO))
	{
		if (vector.x < PLAYER_MAX_MOVE_SPEED)
		{
			vector.x += PLAYER_MOVE_SPEED;
		}
	}
	//左へ移動
	else if ((KeyInput::GetKeyDown(KEY_INPUT_A) || PadInput::GetLStickRationX() < -NEED_STICK_RATIO))
	{
		if (vector.x > -PLAYER_MAX_MOVE_SPEED)
		{
			vector.x += -PLAYER_MOVE_SPEED;
		}
	}
	//停止
	else
	{
		vector.x = 0.f;
	}

	//ジャンプ
	if ((KeyInput::GetKey(KEY_INPUT_SPACE) || KeyInput::GetKey(KEY_INPUT_W) || PadInput::OnButton(XINPUT_BUTTON_A)) && !isAir)
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
		location.x = WORLD_WIDTH - area.width / 2;
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
		location.y = GROUND_LINE - area.height / 2;
		vector.y = 0.f;
		isAir = false;
	}
}

void Player::Action()
{

}
