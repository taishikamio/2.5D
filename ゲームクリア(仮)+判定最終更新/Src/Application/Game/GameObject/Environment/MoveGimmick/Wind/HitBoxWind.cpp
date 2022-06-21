#include "HitBoxWind.h"
#include"Application/main.h"
#include"Application/Game/KdGameSystem.h"
#include"Application/Game/GameObject/Character/Player/Player.h"

HitBoxWind::HitBoxWind()
{
}

HitBoxWind::~HitBoxWind()
{
}

void HitBoxWind::Init(Math::Vector3 pos)
{
	Model3D::Init();

	m_pos = pos;

	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void HitBoxWind::Update()
{
	std::shared_ptr<Player>player = Application::Instance().GetObj()->GetPlayer();
	//player�̃X�t�B�A���̍쐬
	DirectX::BoundingSphere sphere;
	sphere.Center = player->GetPos();//���S���W
	sphere.Radius = 0.25f;//���a

	//���茋��
	std::list<KdCollider::CollisionResult>result;
	
	//����������result���X�g�ɏ������Ă���
	this->GetCollider()->Intersects(KdCollider::TypeBump, sphere, &result);

	if (result.size())
	{
		for (const KdCollider::CollisionResult& colRes : result)
		{
			player->SetBouyancy(0.004);//player�̕��͂��Z�b�g
		}
	}

	Math::Matrix scale = Math::Matrix::CreateScale(0.47);

	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = scale * trans;
}

void HitBoxWind::Draw()
{
	if (m_pModel)
	{
		Model3D::DrawBright();
	}
}
