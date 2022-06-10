#pragma once
#include"../MoveGimmick.h"

class Lever :public MoveGimmick
{
public:
	Lever(Math::Vector3 pos) ;
	virtual ~Lever(){};

	void Init();
	void Update();
	void Draw();

	void SetPos(const Math::Vector3& pos) { m_mTrans.Translation(pos); }

	bool GetFlg() { return Lever::m_bClear; }
	bool GetUIFlg() { return m_bUI; }
private:

	bool CheckAction();//ìÆçÏä÷êî

	Math::Matrix m_mScale;
	Math::Matrix m_mRot;
	float m_angle = 0;

	Math::Matrix m_mTrans;

	bool m_bUI=false;
};