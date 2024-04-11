#pragma once
#include "../CollisionBase.h"
#include"../../Utility/common.h"

class BoxCollision :public CollisionBase
{
protected:
    Area area;          //領域

public:
    //コンストラクタ
    BoxCollision();

    //デストラクタ
    ~BoxCollision();

public:
    //領域の取得
    Area GetArea()const { return area; }

    //左上のワールド座標を取得
    Vector2D GetMinLocation()const { return Vector2D{ location.x ,location.y }; }

    //右下のワールド座標を取得
    Vector2D GetMaxLocation()const { return Vector2D{ location.x + area.width / 2,location.y + area.height / 2 }; }

private:
    //ボックスとの当たり判定
    bool HitBox(const BoxCollision* collision)const override;
};

