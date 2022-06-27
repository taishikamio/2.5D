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
	//playerのスフィア情報の作成
	DirectX::BoundingSphere sphere;
	sphere.Center = player->GetPos();//中心座標
	sphere.Radius = 0.25f;//半径

	//判定結果
	std::list<KdCollider::CollisionResult>result;
	
	//当たったらresultリストに情報を入れていく
	this->GetCollider()->Intersects(KdCollider::TypeBump, sphere, &result);

	if (result.size())
	{
		for (const KdCollider::CollisionResult& colRes : result)
		{
			player->SetBouyancy(0.004);//playerの浮力をセット
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
