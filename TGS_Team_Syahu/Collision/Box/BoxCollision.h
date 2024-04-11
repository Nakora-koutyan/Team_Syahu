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

    //領域の設定
    void SetArea(const Area area) { this->area = area; }

    //左上のワールド座標を取得
    Vector2D GetMinLocation()const { return Vector2D{ location.x ,location.y }; }

    //中心のワールド座標を取得
    Vector2D GetCenterLocation()const { return Vector2D{ location.x + area.width / 2,location.y + area.width / 2 }; }

    //右下のワールド座標を取得
    Vector2D GetMaxLocation()const { return Vector2D{ location.x + area.width,location.y + area.height }; }

    //左上のスクリーン座標を取得
    Vector2D GetMinScreenLocation()const { return Vector2D{ screenLocation.x ,screenLocation.y }; }

    //中心のスクリーン座標を取得
    Vector2D GetCenterScreenLocation()const { return Vector2D{ screenLocation.x + area.width / 2,screenLocation.y + area.width / 2 }; }

    //右下のスクリーン座標を取得
    Vector2D GetMaxScreenLocation()const { return Vector2D{ screenLocation.x + area.width,screenLocation.y + area.height }; }

private:
    //四角との当たり判定
    bool HitBox(const BoxCollision* collision)const override;

    //円との当たり判定
    bool HitSphere(const SphereCollision* collision)const override;
};
