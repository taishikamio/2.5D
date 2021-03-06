#pragma once
#include"../MoveGimmick.h"

class Fan :public MoveGimmick
{
public:
	Fan();
	virtual~Fan();

	Math::Vector3 GetPos() { return m_mWorld.Translation(); }

	//初期化で座標設定
	void Init(Math::Vector3 pos);
	void Update();
	void Draw();
private:
	Math::Vector3 m_pos;
	
};