#pragma once
#include"../Model3D.h"

class MoveGimmick :public Model3D
{
public:
	MoveGimmick() {};
	virtual~MoveGimmick() {};

protected:
	bool m_bClear = false;
	float m_angle;

	//Math::Matrix m_mRot = Math::Matrix::Identity;

	Math::Vector3 m_moveVal = Math::Vector3::Zero;
	Math::Vector3 m_moveDir = Math::Vector3::Zero;
};