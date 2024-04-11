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
	//�E�ֈړ�
	if ((KeyInput::GetKeyDown(KEY_INPUT_D) || PadInput::GetLStickRationX() > NEED_STICK_RATIO))
	{
		if (vector.x < PLAYER_MAX_MOVE_SPEED)
		{
			vector.x += PLAYER_MOVE_SPEED;
		}
	}
	//���ֈړ�
	else if ((KeyInput::GetKeyDown(KEY_INPUT_A) || PadInput::GetLStickRationX() < -NEED_STICK_RATIO))
	{
		if (vector.x > -PLAYER_MAX_MOVE_SPEED)
		{
			vector.x += -PLAYER_MOVE_SPEED;
		}
	}
	//��~
	else
	{
		vector.x = 0.f;
	}

	//�W�����v
	if ((KeyInput::GetKey(KEY_INPUT_SPACE) || KeyInput::GetKey(KEY_INPUT_W) || PadInput::OnButton(XINPUT_BUTTON_A)) && !isAir)
	{
		vector.y = -JUMP_POWER;
		isAir = true;
	}

	//�d��
	vector.y += GRAVITY;

	//�ړ��ʂ����W�ɉ��Z
	location.x += vector.x;
	location.y += vector.y;

	//���[�𒴂��Ȃ�
	if (GetMinLocation().x < 0.f)
	{
		location.x = 0.f;
		vector.x = 0.f;
	}
	//�E�[�𒴂��Ȃ�
	else if (GetMaxLocation().x > WORLD_WIDTH)
	{
		location.x = WORLD_WIDTH - area.width / 2;
		vector.x = 0.f;
	}

	//�V��𒴂��Ȃ�
	if (GetMinLocation().y < 0.f)
	{
		location.y = 0.f;
		vector.y = 0.f;
	}

	//�n�ʂ𒴂��Ȃ�
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
