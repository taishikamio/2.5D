#pragma once
#include"../Model3D.h"

class GoalObject :public Model3D
{
public:
	GoalObject();
	virtual ~GoalObject();

	void Draw();
	void Init();
	void Update();

private:

	Math::Matrix m_mTrans;
	Math::Matrix m_mScale;
	Math::Matrix m_mRot;

	float m_angle = 0;

};