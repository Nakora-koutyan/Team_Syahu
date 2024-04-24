#pragma once
#include"../../Utility/Vector2D.h"

class GameMainScene;

class Camera
{
private:
	static Vector2D cameraPosition;		//カメラの座標
	static Vector2D screenPosition;		//スクリーンの座標

public:
	//コンストラクタ
	Camera();

	//デストラクタ
	~Camera();

	//更新
	void Update(Vector2D location, const bool debugFlg = false);

	//描画
	void Draw()const;

	//スクリーンの座標に変換
	static Vector2D ConvertScreenPosition(const Vector2D location);

};