#include "Player.h"
#include"../../Scene/GameMain/GameMainScene.h"

#define DEBUG

Player::Player()
{
	location = { 300.f,GROUND_LINE + area.height };
	area = { 100.f,100.f };

	weaponSlot1 = Ability::Empty;
	weaponSlot2 = Ability::Empty;
	normalWeapon = new NormalWeapon();

	framCount = 0;
	damageFramCount = 0;
	parryFram = 0;

	damageInterval = PLAYER_DAMAGE_INTERVAL;

	isGuard = false;
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
		if (parryFram > 120)
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
			//�_���[�W���󂯂���v������
			damageFramCount++;

			//PLAYER_PARRY_FLAME�ȓ��ɃK�[�h���Ă���Ȃ�
			if (damageFramCount <= PLAYER_PARRY_FLAME && KeyInput::GetKey(KEY_INPUT_LSHIFT))
			{
				parryFlg = true;
			}

			//�p���B�ł��Ȃ�������
			if (damageFramCount > PLAYER_PARRY_FLAME && !parryFlg)
			{
				isHit = true;

				//�K�[�h���Ă��Ȃ��Ȃ�
				if (!isGuard)
				{
					hp -= object->GetNormalEnemy()->GetDamage();
				}
				//�K�[�h���Ă���Ȃ�
				else
				{
					hp -= object->GetNormalEnemy()->GetDamage() * PLAYER_DAMAGE_CUT;
				}
				//0�ɂ���
				damageFramCount = 0;
			}
		}
	}
}

void Player::Movement()
{
	//�E�ֈړ�
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
	//���ֈړ�
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
	//��~
	else
	{
		vector.x = 0.f;
	}

	//�W�����v
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
		direction = { direction.x,0.f };
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
	else
	{
		isGuard = false;
	}

	//�ʏ�U���{�^���������Ă���Ȃ�
	if ((KeyInput::GetButton(MOUSE_INPUT_LEFT) || PadInput::OnPressed(XINPUT_BUTTON_B)))
	{
		isAttack = true;
		if (abilityType == Ability::Empty)
		{
			normalWeapon->Attack(this);
		}
	}
	//�ʏ�U���{�^���𗣂�����
	else
	{
		/*isAttack = false;*/
	}

	//�z���{�^���������Ă���Ȃ�
	if ((KeyInput::GetKeyDown(KEY_INPUT_E) || PadInput::OnPressed(XINPUT_BUTTON_Y)))
	{

	}
	//�z���{�^���𗣂�����
	else
	{

	}

}
