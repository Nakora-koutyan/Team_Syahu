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
    //半径の取得
    float GetRadius()const { return radius; }

    //半径の設定
    void SetRadius(const float radius) { this->radius = radius; }

private:
    //円との当たり判定
    bool HitSphere(const SphereCollision* collision)const override;

    //四角との当たり判定
    bool HitBox(const BoxCollision* collision)const override;

};

