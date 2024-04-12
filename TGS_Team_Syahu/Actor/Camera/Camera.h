#pragma once
#include"../../Utility/Vector2D.h"

class GameMainScene;

class Camera
{
private:
	Vector2D cameraPosition;		//カメラの座標
	Vector2D screenPosition;		//スクリーンの座標

public:
	//コンストラクタ
	Camera();

	//デストラクタ
	~Camera();

	//更新
	void Update(GameMainScene* object);

	//描画
	void Draw()const;

	//スクリーンの座標に変換
	Vector2D ConvertScreenPosition(const Vector2D location);

};