#include "Enemy.h"
#include"Application/Game/GameObject/Character/Player/Player.h"
#include"Application/Utility.h"
void Enemy::Draw()
{
	D3D.WorkShaderManager().m_HD2DShader.DrawSquarePolygon(*poly, m_mWorld);
}

void Enemy::Update()
{
	enemyAnime += 0.5f;
	poly->SetUVRect(Math::Rectangle(EnemyDiameter * (int)(enemyAnime), EnemyDiameter * 2, EnemyDiameter, EnemyDiameter));

	//enemy��player�Ɍ������x�N�g��
//moveDir = FollowDir(m_pPlayer->GetPos(), m_mWorld.Translation());
	moveDir = FollowDir(m_pPlayer->GetMat(), m_mWorld);

	moveDir.Normalize();
	//if (moveDir.LengthSquared() > (2 * 2))
	{
		m_mWorld *= Math::Matrix::CreateTranslation(moveDir * moveSpeed);
	}
}

void Enemy::Init()
{
	poly = new KdSquarePolygon();
	poly->SetMaterial("Asset/Textures/Character/Enemy/Enemy.png");
	poly->SetSplit(4, 4);
	poly->SetScale({ 0.5f, 0.5f }, KdSquarePolygon::PivotType::Center_Bottom);

	m_pPlayer = new Player();
	m_mWorld.Translation(Math::Vector3(5, 0, 0));

}

bool Enemy::CheckCollisionBump(const SphereInfo& info, BumpResult& result)
{
	Math::Vector3 selfPos = GetPos();

	//����̍��W�Ǝ����̍��W���v�Z
	//�������瑊��Ɍ������x�N�g��
	Math::Vector3 betweenVec = info.m_pos - selfPos;

	//�Q�̃L�����̊Ԃ̋���
	float distanceSqr = betweenVec.LengthSquared();

	//�Q�̃L�����̓����蔻�苅�̔��a�̍��v
	float hitRadius = 0.25 + info.m_radius;

	//2�̃L�����̊Ԃ̋��������Q�̃L�����̓����蔻�苅�̔��a�̍��v
	result.m_IsHit = (distanceSqr <= (hitRadius * hitRadius));

	//�������Ă���
	if (result.m_IsHit)
	{
		//�����߂��̂ɓs���̂����x�N�g��
		result.m_PushVec = betweenVec;
		result.m_PushVec.Normalize();

		//�ǂ̒��x�����߂����H
		float distance = std::sqrtf(distanceSqr);
		result.m_PushVec *= hitRadius - distance;
	}
	return result.m_IsHit;
}

void Enemy::Release()
{
	KdSafeDelete(poly);
}
