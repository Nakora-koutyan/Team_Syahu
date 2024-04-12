#pragma once
#include "../CollisionBase.h"
#include"../../Utility/common.h"

class BoxCollision :public CollisionBase
{
protected:
    Area area;          //�̈�

public:
    //�R���X�g���N�^
    BoxCollision();

    //�f�X�g���N�^
    ~BoxCollision();

public:
    //�̈�̎擾
    Area GetArea()const { return area; }

    //�̈�̐ݒ�
    void SetArea(const Area area) { this->area = area; }

    //����̃��[���h���W��擾
    Vector2D GetMinLocation()const { return Vector2D{ location.x ,location.y }; }

    //���S�̃��[���h���W��擾
    Vector2D GetCenterLocation()const { return Vector2D{ location.x + area.width / 2,location.y + area.width / 2 }; }

    //�E���̃��[���h���W��擾
    Vector2D GetMaxLocation()const { return Vector2D{ location.x + area.width,location.y + area.height }; }

    //����̃X�N���[�����W��擾
    Vector2D GetMinScreenLocation()const { return Vector2D{ screenLocation.x ,screenLocation.y }; }

    //���S�̃X�N���[�����W��擾
    Vector2D GetCenterScreenLocation()const { return Vector2D{ screenLocation.x + area.width / 2,screenLocation.y + area.width / 2 }; }

    //�E���̃X�N���[�����W��擾
    Vector2D GetMaxScreenLocation()const { return Vector2D{ screenLocation.x + area.width,screenLocation.y + area.height }; }

private:
    //�l�p�Ƃ̓����蔻��
    bool HitBox(const BoxCollision* collision)const override;

    //�~�Ƃ̓����蔻��
    bool HitSphere(const SphereCollision* collision)const override;
};
