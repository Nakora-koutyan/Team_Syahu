#pragma once
#include"DxLib.h"

class SceneBase 
{
public:
	//デストラクタ
	virtual ~SceneBase() {};

	//初期化処理
	virtual void Initialize() = 0;

	//終了処理
	virtual void Finalize() = 0;

	//更新
	virtual SceneBase* Update() = 0;

	//描画
	virtual void Draw()const = 0;

};