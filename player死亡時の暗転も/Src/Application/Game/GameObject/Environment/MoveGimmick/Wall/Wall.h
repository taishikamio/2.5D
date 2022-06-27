#pragma once
#include"../MoveGimmick.h"

class MoveWall :public MoveGimmick
{
public:
	MoveWall(Math::Vector3 pos,float angle);
	virtual~MoveWall();

	void Draw();
	void Init();
	void Update();


	void SetClear() { MoveWall::m_bClear = true; }
	const bool GetClear() { return MoveWall::m_bClear; }

	const float GetAngle() { return m_angle; }

	const bool GetKilled() { return m_bKilled; }



private:

	bool m_bKilled=false;

	Math::Matrix m_mRot;
	Math::Matrix transMat;
	
	Math::Vector3 m_defaultPos;

};