#include"Camera.h"
#include"../../Scene/GameMain/GameMainScene.h"
#include"../InputControl/Key/KeyInput.h"

Vector2D Camera::cameraPosition;
Vector2D Camera::screenPosition;
bool Camera::debugModeFlg = false;

Camera::Camera()
{	
	objectType = ObjectType::Camera;

	cameraPosition.x = WORLD_WIDTH / 2.f;
	cameraPosition.y = WORLD_HEIGHT / 2.f;
	screenPosition.x = SCREEN_WIDTH / 2.f;
	screenPosition.y = SCREEN_HEIGHT / 2.f;
}

Camera::~Camera()
{

}

void Camera::Initialize()
{

}

void Camera::Finalize()
{

}

void Camera::Update()
{
	//世界の左端を超えない
	if (cameraPosition.x - SCREEN_WIDTH / 2.f <= 0.f)
	{
		cameraPosition.x = SCREEN_WIDTH / 2.f;
	}
	//世界の右端を超えない
	else if (cameraPosition.x + SCREEN_WIDTH / 2.f >= WORLD_WIDTH)
	{
		cameraPosition.x = WORLD_WIDTH - SCREEN_WIDTH / 2.f;
	}

	//世界の天井を超えない
	if (cameraPosition.y - SCREEN_HEIGHT / 2.f <= 0.f)
	{
		cameraPosition.y = SCREEN_HEIGHT / 2.f;
	}
	//世界の地面を超えない
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
	//カメラの座標をスクリーンの座標に変換
	Vector2D screenOriginPosition = {};
	screenOriginPosition.x = cameraPosition.x - SCREEN_WIDTH / 2.f;
	screenOriginPosition.y = cameraPosition.y - SCREEN_HEIGHT / 2.f;

	//ワールドの座標をスクリーンの座標に変換
	Vector2D screenPosition = {};
	screenPosition.x = location.x - screenOriginPosition.x;
	screenPosition.y = location.y - screenOriginPosition.y;


	return screenPosition;
}

void Camera::SetTarget(const Vector2D location, const bool debugFlg)
{
	if (!debugFlg && !debugModeFlg)
	{
		//対象を追尾
		cameraPosition = location;
	}
	else
	{
		DebugCamera();
	}
}

void Camera::DebugCamera()
{
	if (KeyInput::GetKeyDown(KEY_INPUT_W))
	{
		cameraPosition.y -= 10;
	}
	else if (KeyInput::GetKeyDown(KEY_INPUT_S))
	{
		cameraPosition.y += 10;
	}

	if (KeyInput::GetKeyDown(KEY_INPUT_A))
	{
		cameraPosition.x -= 10;
	}
	else if (KeyInput::GetKeyDown(KEY_INPUT_D))
	{
		cameraPosition.x += 10;
	}

	//マウスでカメラ移動
	cameraPosition.x += (float)KeyInput::GetMouseVecX();
	cameraPosition.y += (float)KeyInput::GetMouseVecY();

}
