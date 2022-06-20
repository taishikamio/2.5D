#include"Bullet.h"
#include"Application/Game/GameObject/Character/Enemy/Enemy.h"
void Bullet::Draw()
{
	if(m_Alive)D3D.WorkShaderManager().m_HD2DShader.DrawSquarePolygon(*poly, m_mWorld);
}

void Bullet::Update()
{
	if (!m_Alive)return;
	moveDir.Normalize();
	m_mWorld *= Math::Matrix::CreateTranslation(moveDir * moveSpeed);

	if (m_pEnemy)
	{
		SphereInfo sphereInfo(m_mWorld.Translation(), 0.25);
		BumpResult bumpResult;
		if (m_pEnemy->CheckCollisionBump(sphereInfo, bumpResult))
		{
			m_Alive = false;
		}
	}
}

void Bullet::Init()
{
	poly = new KdSquarePolygon();
	poly->SetMaterial("Asset/Textures/Bullet/Bullet01.png");
	poly->SetScale({ 0.2,0.2 }, KdSquarePolygon::PivotType::Center_Bottom);

	m_mWorld.Translation() = {0,0,0};
	m_Alive = true;
}

void Bullet::Release()
{
	KdSafeDelete(poly);
}
