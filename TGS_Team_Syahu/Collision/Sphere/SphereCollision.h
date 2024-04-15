#pragma once
#include "../CollisionBase.h"

class SphereCollision :public CollisionBase
{
protected:
    float radius;           //半径

public:
    //コンストラクタ
    SphereCollision();

    //デストラクタ
    ~SphereCollision();

public:
    //半径を取得
    float GetRadius()const { return radius; }

    //半径を設定
    void SetRadius(const float radius) { this->radius = radius; }

public:
    //円の当たり判定
    bool HitSphere(const SphereCollision* collision)const override;

    //四角の当たり判定
    bool HitBox(const BoxCollision* collision)const override;

    //線の当たり判定
    bool HitLine(const LineCollision* collision)const override;

};

