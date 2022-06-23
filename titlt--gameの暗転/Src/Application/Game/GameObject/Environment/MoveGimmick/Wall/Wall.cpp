#include"Wall.h"

MoveWall::MoveWall(Math::Vector3 pos, float angle)
{
	m_defaultPos = pos;
	m_angle = angle;
}

MoveWall::~MoveWall()
{
}

void MoveWall::Draw()
{
	if (m_pModel)
	{
		Model3D::DrawOpeque();
	}
}

void MoveWall::Init()
{
	Model3D::Init();

	m_bClear = false;

	transMat = Math::Matrix::CreateTranslation(m_defaultPos);
}

void MoveWall::Update()
{
	if (m_pModel)
	{

		if (MoveWall::m_bClear)
		{
			static int frame = 0;


			m_moveDir = Math::Vector3::Up;
			m_moveVal.y = 0.07f;

			frame++;

				if (frame > 300)
				{
					m_bKilled = true;
				}
		}
		else
		{
			m_moveDir = Math::Vector3::Zero;
			m_moveVal = Math::Vector3::Zero;
		}

		m_mRot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));


	
		transMat *= Math::Matrix::CreateTranslation(m_moveDir * m_moveVal);

		m_mWorld = m_mRot * transMat;
	}
}
