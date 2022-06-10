#pragma once
#include"../MoveGimmick.h"

class Fan :public MoveGimmick
{
public:
	Fan();
	virtual~Fan();

	Math::Vector3 GetPos() { return m_mWorld.Translation(); }

	//‰Šú‰»‚ÅÀ•Wİ’è
	void Init(Math::Vector3 pos);
	void Update();
	void Draw();
private:
	Math::Vector3 m_pos;
	
};