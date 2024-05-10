#pragma once
#include"../../Actor/ObjectBase.h"
#include"../../Utility/common.h"

class BoxCollision :public ObjectBase
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

    //ワールド座標の左上を取得
    Vector2D GetMinLocation()const { return Vector2D{ location.x ,location.y }; }

    //ワールド座標の中心を取得
    Vector2D GetCenterLocation()const { return Vector2D{ location.x + area.width / 2,location.y + area.width / 2 }; }

    //ワールド座標の右下を取得
    Vector2D GetMaxLocation()const { return Vector2D{ location.x + area.width,location.y + area.height }; }

    //スクリーン座標の左上を取得
    Vector2D GetMinScreenLocation()const { return Vector2D{ screenLocation.x ,screenLocation.y }; }

    //スクリーン座標の中心を取得
    Vector2D GetCenterScreenLocation()const { return Vector2D{ screenLocation.x + area.width / 2,screenLocation.y + area.width / 2 }; }

    //スクリーン座標の右下を取得
    Vector2D GetMaxScreenLocation()const { return Vector2D{ screenLocation.x + area.width,screenLocation.y + area.height }; }

public:
    //四角の当たり判定
    bool HitBox(const ObjectBase* object)const override;

    //円の当たり判定
    bool HitSphere(const ObjectBase* object)const override;

    //線の当たり判定
    bool HitLine(const ObjectBase* object)const override;
};
