#pragma once
#include "../ObjectBase.h"

class SphereCollision :public ObjectBase
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
    bool HitSphere(const ObjectBase* object)const override;

    //四角の当たり判定
    bool HitBox(const ObjectBase* object)const override;

    //線の当たり判定
    bool HitLine(const ObjectBase* object)const override;

};

