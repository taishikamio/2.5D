#pragma once
#include"../MoveGimmick.h"

//ファンからの風の判定
class HitBoxWind :public MoveGimmick
{
public:
	HitBoxWind();
	virtual~HitBoxWind();

	//ファンの位置を設定する
	void Init(Math::Vector3 pos);
	void Update();
	void Draw();
private:

	Math::Vector3 m_pos;
};