#pragma once
#include"Application/Game/GameObject/Character/CharacterBase.h"

class Player;

//���̂̓����蔻����
struct SphereInfo
{
	SphereInfo() = default;

	SphereInfo(const Math::Vector3& pos, float radius) :
		m_pos(pos),
		m_radius(radius) {}

	Math::Vector3 m_pos;
	float m_radius = 1.0f;
};
struct BumpResult
{
	bool m_IsHit = false;
	Math::Vector3 m_PushVec;
};
class Enemy :public CharacterBase
{
public:
	Enemy() {}
	~Enemy() { Release(); }

	void Draw();
	void Update();
	void Init();

	const Math::Vector3 GetPos() { return m_mWorld.Translation(); }
	const Math::Matrix GetMat() { return m_mWorld; }

	void SetPlayer(Player* player) { m_pPlayer = player; };
	void SetPos(const Math::Vector3 pos){}
	//���Ή����̓����蔻��
	//info:����̏��
	//result:�����������ǂ�������сA�����Ԃ��x�N�g��
	//�߂�l:�����������ǂ���
	bool CheckCollisionBump(const SphereInfo& info, BumpResult& result);
private:
	void Release();

	Player* m_pPlayer = nullptr;

	const int EnemyRadius = 16;//���a
	const int EnemyDiameter = 32;//���a
	float enemyAnime = 0;

	Math::Vector3 moveDir;
	float moveSpeed = 0.02;

	Math::Matrix m_mWorld;
};