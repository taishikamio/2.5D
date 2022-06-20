#include"GoalObject.h"
#include"../../../../main.h"
#include"../../../KdGameSystem.h"
#include"../../Character/Player/Player.h"


GoalObject::GoalObject()
{
}

GoalObject::~GoalObject()
{
}

void GoalObject::Draw()
{
	if (m_pModel)
	{
		Model3D::DrawOpeque();
	}
}

void GoalObject::Init()
{
	if (m_pModel)
	{
		Model3D::Init();

		m_mWorld = Math::Matrix::Identity;

		m_mTrans = Math::Matrix::CreateTranslation(5.4,7.3,12.2);
	}
}

void GoalObject::Update()
{
	if (m_pModel)
	{
		const std::shared_ptr<Player> const player = Application::Instance().GetObj()->GetPlayer();

		Math::Vector3 pos = player->GetPos();
		Math::Vector3 selfPos = m_mWorld.Translation();

		Math::Vector3 between = pos - selfPos;
		float distanceSqr = between.LengthSquared();

		float dist = 2;

		if (distanceSqr < dist)
		{
			m_angle+=60;
			if (m_angle >= 360)
			{
				m_angle = 0;
			}
		}

		m_mRot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
		//m_mTrans*= Math::Matrix::CreateTranslation(-4, 1, 4);


		m_mWorld = m_mRot* m_mTrans;

	}
}
