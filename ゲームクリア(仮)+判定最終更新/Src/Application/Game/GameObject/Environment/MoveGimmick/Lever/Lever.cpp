#include"Lever.h"
#include"../Wall/Wall.h"
#include"../../../../../main.h"
#include"../../../../KdGameSystem.h"
#include"../../../../GameObject/Character/Player/Player.h"
#include"../../../../../Utility.h"

Lever::Lever(Math::Vector3 pos)
{
	m_mTrans = Math::Matrix::CreateTranslation(pos);
}

void Lever::Init()
{
	Model3D::Init();

	m_bClear = false;

	m_mWorld = Math::Matrix::Identity;
	//m_mTrans = Math::Matrix::CreateTranslation(4, 2, -3);
	m_angle = 0;
}

void Lever::Update()
{
	if (m_pModel)
	{
		if (!Lever::m_bClear)
		{
			if (CheckAction())
			{
				if (GetAsyncKeyState('G') & 0x8000)
				{
					Lever::m_bClear = true;

					m_angle += 180;

				}
				m_bUI = true;
			}
			else
			{
				m_bUI = false;
			}
		}
		else
		{
			m_bUI = false;
		}

		m_mScale = Math::Matrix::CreateScale(0.1);
		m_mRot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));

		m_mWorld = m_mRot * m_mScale * m_mTrans;
	}

}

void Lever::Draw()
{
	if (m_pModel)
	{
		DrawOpeque();
	}
}

bool Lever::CheckAction()
{
	const std::shared_ptr<Player> const player = Application::Instance().GetObj()->GetPlayer();

	Math::Vector3 pos = player->GetPos();
	Math::Vector3 selfPos = m_mWorld.Translation();

	Math::Vector3 between = pos - selfPos;
	float distanceSqr = between.LengthSquared();

	float dist = 2;

	return distanceSqr < dist;
}
