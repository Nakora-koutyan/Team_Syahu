#pragma once
#include "../../../ObjectBase.h"

class CharaBase;

class WeaponBase : public ObjectBase
{
private:
	short direction;		//方向

	int framCount;			//フレームカウント

	float angle;			//角度

	bool isShow;			//表示させる？

public:
	//コンストラクタ
	WeaponBase();

	//デストラクタ
	~WeaponBase();

	//更新
	virtual void Update(CharaBase* chara);

	//描画
	void Draw()const override {};

	//攻撃
	void Attack(const CharaBase* chara);

	//ヒット処理
	void Hit(ObjectBase* object, const float damage)override {};

};

