#pragma once
#include"../../Utility/Vector2D.h"
#include"../ObjectBase.h"

class GameMainScene;

class Camera :public ObjectBase
{
private:
	static Vector2D cameraPosition;		//カメラの座標
	static Vector2D screenPosition;		//スクリーンの座標

	static bool debugModeFlg;			//デバッグ状態のフラグ

public:
	//コンストラクタ
	Camera();

	//デストラクタ
	~Camera();

	//初期化処理
	void Initialize()override;

	//終了処理
	void Finalize()override;

	//更新
	void Update()override;

	//描画
	void Draw()const override;

public:
	//スクリーンの座標に変換
	static Vector2D ConvertScreenPosition(const Vector2D location);

	//対象を設定する
	static void SetTarget(const Vector2D location, const bool debugFlg = false);

	//カメラを動かす
	static void DebugCamera();

public:
	//デバッグ状態の設定
	void SetDebugModeFlg(const bool flg) { debugModeFlg = flg; }
};