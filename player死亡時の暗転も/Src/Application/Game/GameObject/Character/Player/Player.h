#pragma once
#include"Application/Game/GameObject/Character/CharacterBase.h"
class GameCamera;

class Player :public CharacterBase
{
public:
	Player(){};
	~Player() { Release(); }

	void Draw();
	void Update();
	void Init();

	const Math::Matrix GetMat() { return m_mWorld; }
	const Math::Vector3 GetPos() { return m_pos; }


	//•‚—Í(ã¸—Í)
	void SetBouyancy(float val) { m_bouyancy = val; m_gravity = 0; }

	void SetCanMove(const bool& flg) { m_bCanMove = flg; }

private:
	//Õ“Ë‚É‚¨‚¯‚éÀ•W‚ÌXV	
	void UpdateCollision();

	void Move();
	void Jump();

	void CrateMatrix();

	void CheckIsAlive();




	std::shared_ptr<GameCamera>m_pCamera = nullptr;

	bool m_bLanding = false;

	//ˆÚ“®Œn
	Math::Vector3 m_moveDir;
	float m_speed = 0.1;

	Math::Matrix m_mRot;
	Math::Matrix local = Math::Matrix::Identity;

	//c•ûŒü‚ÌˆÚ“®¬•ª
	float m_gravity = 0.1f;
	float m_bouyancy = 0;
	float moveVal_y = 0;


	Math::Vector3 m_pos;

	bool m_bCanMove = true;

	void Release();


};
