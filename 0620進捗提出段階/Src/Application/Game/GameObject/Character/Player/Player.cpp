#include"Player.h"
#include"../../GameCamera/GameCamera.h"
#include"Application/Utility.h"
#include"Application/main.h"
#include"Application/Game/KdGameSystem.h"
#include"Application/Game/GameObject/Environment/Terrain/Terrain.h"
#include"../../Environment/MoveGimmick/Wall/Wall.h"


Player::Player()
{
	
}

void Player::Draw()
{
	D3D.WorkShaderManager().m_HD2DShader.DrawSquarePolygon(*poly, m_mWorld);
	//if (m_pBullet)m_pBullet->Draw();
}

void Player::Update()
{
	if (!m_pCamera->GetSpot())//�X�|�b�g���͓����Ȃ�
	{
		Move();
	}

	m_pos += m_moveDir * m_speed;
	m_pos.y += moveVal_y;


	UpdateCollision();

	//�c�����̈ړ��ʂ� �d�� �� ���� (�ƃW�����v��)�ŊǗ�����
	moveVal_y = moveVal_y - m_gravity + m_bouyancy;

	//�����ōő�㏸�ʂ𒲐�
	if (moveVal_y > 0.11)
	{
		moveVal_y = 0.11;
	}


	CrateMatrix();

	//���͂Əd�͂����Z�b�g
	m_bouyancy = 0;
	m_gravity = 0.01;//�����Œ�������


	//���S����
	CheckIsAlive();
}

void Player::Init()
{

	poly = new KdSquarePolygon();
	poly->SetMaterial("Asset/Textures/Character/Player/Player.png");
	poly->SetSplit(9, 4);
	poly->SetScale({ 0.5f, 0.5f });
	poly->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);

	m_pCamera = std::make_unique<GameCamera>();

	m_pos = Math::Vector3(2.5, 0, 3);
	m_mWorld = Math::Matrix::CreateTranslation(m_pos);

	m_moveDir = Math::Vector3::Zero;

	//�J�����擾
	m_pCamera = Application::Instance().GetObj()->GetCamera();

	m_isAlive = true;
}

inline void Player::Move()
{




	static Math::Vector2 anime = { 0,0 };
	anime.x += 0.1;
	poly->SetUVRect(Math::Rectangle(32 * (int)(anime.x), 32 * anime.y, 32, 32));
	if (anime.x >= 4)
	{
		anime.x = 0;
	}



	//�L�[����
	Math::Vector3 moveDir = Math::Vector3::Zero;
	{
		if (!m_pCamera->GetRotate())//���]���̂�
		{
			//if (GetAsyncKeyState(VK_DOWN) & 0x8000) { moveDir.z = -1.0f; anime.y = 2; }
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { moveDir.x = 1.0f; anime.y = 1; }
			if (GetAsyncKeyState(VK_LEFT) & 0x8000) { moveDir.x = -1.0f; anime.y = 3; }
		}



		//����������ĂȂ����̔���
		if (moveDir.LengthSquared() > 0)
		{
			m_moveDir = moveDir;
		}



		//�J�����̕����ɉ����ăx�N�g����ϊ�
		m_moveDir = m_moveDir.TransformNormal(moveDir, m_pCamera->GetMatrix());


		m_moveDir.Normalize();//�������̂݁@�傫����1�ɂ���

		if (m_bLanding)
		{
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				Jump();
			}
		}
	}

}

void Player::Jump()
{
	moveVal_y = 0.15;//�����Œ�������
}

void Player::CrateMatrix()
{
	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos);

	m_mRot = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_pCamera->GetAngle()));

	m_mWorld = m_mRot * trans;
}

void Player::CheckIsAlive()
{

	if (m_pos.y < -5)
	{
		m_isAlive = false;
	}

}

void Player::UpdateCollision()
{
	//player�̃��C�̏��̍쐬
	KdCollider::RayInfo rayInfo;
	rayInfo.m_pos = m_pos;
	rayInfo.m_pos.y += 1.0f;

	rayInfo.m_dir = Math::Vector3::Down;
	rayInfo.m_range = 1.0f;



	//��Ȓn�`===============================================================
	const std::shared_ptr<Terrain> const Terrain = Application::Instance().GetObj()->GetTerrain();

	if (Terrain)
	{
		//���茋��
		std::list<KdCollider::CollisionResult>result;

		//�n�ʔ���------------------------------------------------------------------------------------------------
		if (Terrain->GetCollider()->Intersects(KdCollider::TypeGround, rayInfo, &result))//�Ԃ�lbool
		{
			//�����蔻������ƂɁA�n�ʂ̏�ɗ�����

			//�ŋߐړ_
			float dis = 0.0f;

			//�ŋߐړ_�̍��Wor�ŋߐړ_�̃��U���g(�������̂�����)
			const KdCollider::CollisionResult* pNearestRes = nullptr;

			for (const KdCollider::CollisionResult& colRes : result)
			{
				//�ŋߐړ_�ƍ����Ă��郊�U���g�̔�r
				if (colRes.m_overlapDistance > dis)
				{
					dis = colRes.m_overlapDistance;
					pNearestRes = &colRes;
				}
			}

			//�Ō�ɁA���߂��ŋߐړ_�ɗ���
			if (pNearestRes)
			{
				m_pos = pNearestRes->m_hitPos;
			}


			m_gravity = 0.0f;
			m_bLanding = true;
		}
		else
		{
			m_bLanding = false;
		}



		result.clear();//��U�O��̌��ʂ��폜

		//player�̃X�t�B�A���̍쐬
		DirectX::BoundingSphere sphere;
		sphere.Center = m_pos;//���S���W
		sphere.Center.y += 0.4f;
		sphere.Radius = 0.25f;//���a

		//�ǔ���-----------------------------------------------------------------------------------------
			//����������result���X�g�ɏ������Ă���
		Terrain->GetCollider()->Intersects(KdCollider::TypeBump, sphere, &result);

		if (result.size())
		{
			for (const KdCollider::CollisionResult& colRes : result)
			{
				m_pos += colRes.m_hitDir * colRes.m_overlapDistance;
			}
		}

	}


	//�M�~�b�N��=================================================================
	const std::vector<std::shared_ptr<MoveWall>>& moveWall = Application::Instance().GetObj()->GetWall();

	if (moveWall.size())
	{
		//���茋��
		std::list<KdCollider::CollisionResult>result;

		result.clear();//��U�O��̌��ʂ��폜


		//�n�ʔ���-------------------------------------------------------------------------------------------
		for (std::shared_ptr<MoveWall>p_wall : moveWall)
		{
			//����������result���X�g�ɏ������Ă���
			p_wall->GetCollider()->Intersects(KdCollider::TypeGround, rayInfo, &result);
		}

		//�ŋߐړ_
		float dis = 0.0f;

		//�ŋߐړ_�̍��Wor�ŋߐړ_�̃��U���g(�������̂�����)
		const KdCollider::CollisionResult* pNearestRes = nullptr;

		if (result.size())
		{
			for (const KdCollider::CollisionResult& colRes : result)
			{
				//�ŋߐړ_�ƍ����Ă��郊�U���g�̔�r
				if (colRes.m_overlapDistance > dis)
				{
					dis = colRes.m_overlapDistance;
					pNearestRes = &colRes;
				}
			}
			//�Ō�ɁA���߂��ŋߐړ_�ɗ���
			if (pNearestRes)
			{
				m_pos = pNearestRes->m_hitPos;
			}


			m_gravity = 0.0f;
			m_bLanding = true;
		}

		result.clear();

		//player�̃X�t�B�A���̍쐬
		DirectX::BoundingSphere sphere;
		sphere.Center = m_pos;//���S���W
		sphere.Center.y += 0.4f;
		sphere.Radius = 0.25f;//���a

		//�ǔ���-------------------------------------------------------------------------------------------------
		for (std::shared_ptr<MoveWall>p_wall : moveWall)
		{
			//����������result���X�g�ɏ������Ă���
			p_wall->GetCollider()->Intersects(KdCollider::TypeBump, sphere, &result);
		}

		if (result.size())
		{
			for (const KdCollider::CollisionResult& colRes : result)
			{
				m_pos += colRes.m_hitDir * colRes.m_overlapDistance;
			}
		}

	}

}



void Player::Release()
{
	KdSafeDelete(poly);
}
