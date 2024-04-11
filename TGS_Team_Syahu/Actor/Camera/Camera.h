#pragma once
#include"../../Utility/Vector2D.h"

class GameMainScene;

class Camera
{
private:
	Vector2D cameraPosition;		//�J�����̍��W
	Vector2D screenPosition;		//�X�N���[���̍��W

public:
	//�R���X�g���N�^
	Camera();

	//�f�X�g���N�^
	~Camera();

	//�X�V
	void Update(GameMainScene* object);

	//�`��
	void Draw()const;

	//�X�N���[���̍��W�ɕϊ�
	Vector2D ConvertScreenPosition(const Vector2D location);

};