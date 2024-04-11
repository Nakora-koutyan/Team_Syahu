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
		//PLAYER_DAMAGE_INTERVAL��Ƀq�b�g�t���O��false�ɂ���
		if (framCount % PLAYER_DAMAGE_INTERVAL == 0)
		{
			isHit = false;
		}
	}

	//�G���G�Ƃ̓����蔻��
	if (HitCheck(object->GetNormalEnemy()))
	{
		//�܂��_���[�W���󂯂Ă��Ȃ��Ȃ�
		if (!isHit)
		{
			damageFramCount++;

			//PLAYER_PARRY_FLAME�ȓ��ɃK�[�h���Ă���Ȃ�
			if (damageFramCount <= PLAYER_PARRY_FLAME && isGuard)
			{

			}

			//�p���B�ł��Ȃ�������
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
	//�E�ֈړ�
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
	//���ֈړ�
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
	//��~
	else
	{
		vector.x = 0.f;
	}

	//�W�����v
	if ((KeyInput::GetKey(KEY_INPUT_SPACE) || KeyInput::GetKey(KEY_INPUT_W) || PadInput::OnButton(XINPUT_BUTTON_A)) && !isAir && !isGuard)
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
		location.x = WORLD_WIDTH - area.width;
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
		location.y = GROUND_LINE - area.height;
		vector.y = 0.f;
		isAir = false;
	}
}

void Player::Action()
{
	//�K�[�h�{�^���������Ă���Ȃ�
	if ((KeyInput::GetKeyDown(KEY_INPUT_LSHIFT) || PadInput::OnPressed(XINPUT_BUTTON_LEFT_SHOULDER)|| PadInput::OnPressed(XINPUT_BUTTON_RIGHT_SHOULDER)))
	{
		isGuard = true;
	}
	//�K�[�h�{�^���𗣂�����
	else if((KeyInput::GetKeyUp(KEY_INPUT_LSHIFT) || PadInput::OnRelease(XINPUT_BUTTON_LEFT_SHOULDER) || PadInput::OnRelease(XINPUT_BUTTON_RIGHT_SHOULDER)))
	{
		isGuard = false;
	}

	if ((KeyInput::GetKeyDown(KEY_INPUT_E) || PadInput::OnPressed(XINPUT_BUTTON_Y)))
	{

	}

}
