#pragma once
#include "../CollisionBase.h"

class SphereCollision :public CollisionBase
{
protected:
    float radius;           //���a

public:
    //�R���X�g���N�^
    SphereCollision();

    //�f�X�g���N�^
    ~SphereCollision();

public:
    //���a�̎擾
    float GetRadius()const { return radius; }

    //���a�̐ݒ�
    void SetRadius(const float radius) { this->radius = radius; }

private:
    //�~�Ƃ̓����蔻��
    bool HitSphere(const SphereCollision* collision)const override;

    //�l�p�Ƃ̓����蔻��
    bool HitBox(const BoxCollision* collision)const override;

};

