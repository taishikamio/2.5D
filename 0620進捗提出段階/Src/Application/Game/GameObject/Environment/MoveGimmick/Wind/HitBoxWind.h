#pragma once
#include"../MoveGimmick.h"

//�t�@������̕��̔���
class HitBoxWind :public MoveGimmick
{
public:
	HitBoxWind();
	virtual~HitBoxWind();

	//�t�@���̈ʒu��ݒ肷��
	void Init(Math::Vector3 pos);
	void Update();
	void Draw();
private:

	Math::Vector3 m_pos;
};