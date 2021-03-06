#pragma once
#include"../MoveGimmick.h"

class Fan :public MoveGimmick
{
public:
	Fan(Math::Vector3 pos);
	virtual~Fan();

	const Math::Vector3 GetPos() { return m_mWorld.Translation(); }

	//初期化で座標設定
	void Init();
	void Update();
	void Draw();
private:
	Math::Vector3 m_pos;
	
	Math::Vector3 defaultPos;
};