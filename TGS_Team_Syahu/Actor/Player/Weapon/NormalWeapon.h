#pragma once
#include"../../../Collision/Sphere/SphereCollision.h"

#define NORMAL_WEAPON_ATTACK_TIME	FPS * 0.5f		//�U������

class GameMainScene;
class Player;

class NormalWeapon :public SphereCollision
{
private:
	int framCount;			//�t���[���J�E���g

public:
	//�R���X�g���N�^
	NormalWeapon();

	//�f�X�g���N�^
	~NormalWeapon();

	//�X�V
	void Update(GameMainScene* object);

	//�`��
	void Draw()const;

	//�U��
	void Attack(const Player* player);
};

