#pragma once
#include"../CharaBase.h"

class NormalEnemy :public CharaBase
{
private:

public:
	//�R���X�g���N�^
	NormalEnemy();

	//�f�X�g���N�^
	~NormalEnemy();

	//�X�V
	void Update(GameMainScene* object)override;

	//�`��
	void Draw()const override;

};

