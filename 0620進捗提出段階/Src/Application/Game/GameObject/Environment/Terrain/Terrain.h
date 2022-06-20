#pragma once
#include"../Model3D.h"

class Terrain :public Model3D
{
public:

	Terrain();
	virtual~Terrain();

	void InitTitle(Math::Vector3 pos);
	void UpdateTitle();
	void DrawTitle();

private:

	Math::Matrix m_mRot;
	Math::Matrix m_mTrans=Math::Matrix::Identity;
	
	float m_angle = 0;
};