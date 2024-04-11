#include"Camera.h"
#include"../../Scene/GameMain/GameMainScene.h"

Camera::Camera()
{	
	cameraPosition = { WORLD_WIDTH / 2.f,WORLD_HEIGHT / 2.f };
	screenPosition = { SCREEN_WIDTH / 2.f,SCREEN_HEIGHT / 2.f };
}

Camera::~Camera()
{

}

void Camera::Update(GameMainScene* object)
{
	//�v���C���[�̍��W��ǔ�����
	cameraPosition = object->GetPlayer()->GetLocation();

	//��ʍ��[�𒴂��Ȃ�
	if (cameraPosition.x - SCREEN_WIDTH / 2.f <= 0.f)
	{
		cameraPosition.x = SCREEN_WIDTH / 2.f;
	}
	//��ʉE�[�𒴂��Ȃ�
	else if (cameraPosition.x + SCREEN_WIDTH / 2.f >= WORLD_WIDTH)
	{
		cameraPosition.x = WORLD_WIDTH - SCREEN_WIDTH / 2.f;
	}

	//��ʏ�𒴂��Ȃ�
	if (cameraPosition.y - SCREEN_HEIGHT / 2.f <= 0.f)
	{
		cameraPosition.y = SCREEN_HEIGHT / 2.f;
	}
	//��ʉ��𒴂��Ȃ�
	else if (cameraPosition.y + SCREEN_HEIGHT / 2.f >= WORLD_HEIGHT)
	{
		cameraPosition.y = WORLD_HEIGHT - SCREEN_HEIGHT / 2.f;
	}
}

void Camera::Draw() const
{

}

Vector2D Camera::ConvertScreenPosition(const Vector2D location)
{
	//�J�����̍��W����X�N���[���̍��W�̌��_��
	Vector2D screenOriginPosition =
	{
		cameraPosition.x - SCREEN_WIDTH / 2.f,
		cameraPosition.y - SCREEN_HEIGHT / 2.f
	};

	//���[���h�̍��W����X�N���[���̍��W��
	Vector2D screenPosition = { location.x - screenOriginPosition.x, location.y - screenOriginPosition.y };

	return screenPosition;
}
