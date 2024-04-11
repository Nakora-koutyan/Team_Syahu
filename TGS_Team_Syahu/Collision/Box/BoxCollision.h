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

    //����̃��[���h���W���擾
    Vector2D GetMinLocation()const { return Vector2D{ location.x ,location.y }; }

    //�E���̃��[���h���W���擾
    Vector2D GetMaxLocation()const { return Vector2D{ location.x + area.width / 2,location.y + area.height / 2 }; }

private:
    //�{�b�N�X�Ƃ̓����蔻��
    bool HitBox(const BoxCollision* collision)const override;
};

