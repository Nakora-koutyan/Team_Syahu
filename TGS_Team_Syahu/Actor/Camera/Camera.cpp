#include"Camera.h"
#include"../../Scene/GameMain/GameMainScene.h"

Camera::Camera()
{	
	cameraPosition = { WORLD_WIDTH / 2.f,WORLD_HEIGHT / 2.f };
	screenPosition = { SCREEN_WIDTH / 2.f,SCREEN_HEIGHT / 2.f };
}

Camera::~Camera()
{

}

void Camera::Update(GameMainScene* object)
{
	//プレイヤーの座標を追尾する
	cameraPosition = object->GetPlayer()->GetLocation();

	//画面左端を超えない
	if (cameraPosition.x - SCREEN_WIDTH / 2.f <= 0.f)
	{
		cameraPosition.x = SCREEN_WIDTH / 2.f;
	}
	//画面右端を超えない
	else if (cameraPosition.x + SCREEN_WIDTH / 2.f >= WORLD_WIDTH)
	{
		cameraPosition.x = WORLD_WIDTH - SCREEN_WIDTH / 2.f;
	}

	//画面上を超えない
	if (cameraPosition.y - SCREEN_HEIGHT / 2.f <= 0.f)
	{
		cameraPosition.y = SCREEN_HEIGHT / 2.f;
	}
	//画面下を超えない
	else if (cameraPosition.y + SCREEN_HEIGHT / 2.f >= WORLD_HEIGHT)
	{
		cameraPosition.y = WORLD_HEIGHT - SCREEN_HEIGHT / 2.f;
	}
}

void Camera::Draw() const
{

}

Vector2D Camera::ConvertScreenPosition(const Vector2D location)
{
	//カメラの座標からスクリーンの座標の原点へ
	Vector2D screenOriginPosition =
	{
		cameraPosition.x - SCREEN_WIDTH / 2.f,
		cameraPosition.y - SCREEN_HEIGHT / 2.f
	};

	//ワールドの座標からスクリーンの座標へ
	Vector2D screenPosition = { location.x - screenOriginPosition.x, location.y - screenOriginPosition.y };

	return screenPosition;
}
