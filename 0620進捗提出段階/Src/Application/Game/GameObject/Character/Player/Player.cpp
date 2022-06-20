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
	if (!m_pCamera->GetSpot())//スポット中は動けない
	{
		Move();
	}

	m_pos += m_moveDir * m_speed;
	m_pos.y += moveVal_y;


	UpdateCollision();

	//縦方向の移動量は 重力 と 浮力 (とジャンプ力)で管理する
	moveVal_y = moveVal_y - m_gravity + m_bouyancy;

	//ここで最大上昇量を調整
	if (moveVal_y > 0.11)
	{
		moveVal_y = 0.11;
	}


	CrateMatrix();

	//浮力と重力をリセット
	m_bouyancy = 0;
	m_gravity = 0.01;//ここで調整して


	//死亡判定
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

	//カメラ取得
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



	//キー入力
	Math::Vector3 moveDir = Math::Vector3::Zero;
	{
		if (!m_pCamera->GetRotate())//非回転時のみ
		{
			//if (GetAsyncKeyState(VK_DOWN) & 0x8000) { moveDir.z = -1.0f; anime.y = 2; }
			if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { moveDir.x = 1.0f; anime.y = 1; }
			if (GetAsyncKeyState(VK_LEFT) & 0x8000) { moveDir.x = -1.0f; anime.y = 3; }
		}



		//何も押されてないかの判定
		if (moveDir.LengthSquared() > 0)
		{
			m_moveDir = moveDir;
		}



		//カメラの方向に応じてベクトルを変換
		m_moveDir = m_moveDir.TransformNormal(moveDir, m_pCamera->GetMatrix());


		m_moveDir.Normalize();//方向情報のみ　大きさを1にする

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
	moveVal_y = 0.15;//ここで調整して
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
	//playerのレイの情報の作成
	KdCollider::RayInfo rayInfo;
	rayInfo.m_pos = m_pos;
	rayInfo.m_pos.y += 1.0f;

	rayInfo.m_dir = Math::Vector3::Down;
	rayInfo.m_range = 1.0f;



	//主な地形===============================================================
	const std::shared_ptr<Terrain> const Terrain = Application::Instance().GetObj()->GetTerrain();

	if (Terrain)
	{
		//判定結果
		std::list<KdCollider::CollisionResult>result;

		//地面判定------------------------------------------------------------------------------------------------
		if (Terrain->GetCollider()->Intersects(KdCollider::TypeGround, rayInfo, &result))//返り値bool
		{
			//当たり判定をもとに、地面の上に立つ処理

			//最近接点
			float dis = 0.0f;

			//最近接点の座標or最近接点のリザルト(こっちのがいい)
			const KdCollider::CollisionResult* pNearestRes = nullptr;

			for (const KdCollider::CollisionResult& colRes : result)
			{
				//最近接点と今見ているリザルトの比較
				if (colRes.m_overlapDistance > dis)
				{
					dis = colRes.m_overlapDistance;
					pNearestRes = &colRes;
				}
			}

			//最後に、求めた最近接点に立つ
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



		result.clear();//一旦前回の結果を削除

		//playerのスフィア情報の作成
		DirectX::BoundingSphere sphere;
		sphere.Center = m_pos;//中心座標
		sphere.Center.y += 0.4f;
		sphere.Radius = 0.25f;//半径

		//壁判定-----------------------------------------------------------------------------------------
			//当たったらresultリストに情報を入れていく
		Terrain->GetCollider()->Intersects(KdCollider::TypeBump, sphere, &result);

		if (result.size())
		{
			for (const KdCollider::CollisionResult& colRes : result)
			{
				m_pos += colRes.m_hitDir * colRes.m_overlapDistance;
			}
		}

	}


	//ギミック壁=================================================================
	const std::vector<std::shared_ptr<MoveWall>>& moveWall = Application::Instance().GetObj()->GetWall();

	if (moveWall.size())
	{
		//判定結果
		std::list<KdCollider::CollisionResult>result;

		result.clear();//一旦前回の結果を削除


		//地面判定-------------------------------------------------------------------------------------------
		for (std::shared_ptr<MoveWall>p_wall : moveWall)
		{
			//当たったらresultリストに情報を入れていく
			p_wall->GetCollider()->Intersects(KdCollider::TypeGround, rayInfo, &result);
		}

		//最近接点
		float dis = 0.0f;

		//最近接点の座標or最近接点のリザルト(こっちのがいい)
		const KdCollider::CollisionResult* pNearestRes = nullptr;

		if (result.size())
		{
			for (const KdCollider::CollisionResult& colRes : result)
			{
				//最近接点と今見ているリザルトの比較
				if (colRes.m_overlapDistance > dis)
				{
					dis = colRes.m_overlapDistance;
					pNearestRes = &colRes;
				}
			}
			//最後に、求めた最近接点に立つ
			if (pNearestRes)
			{
				m_pos = pNearestRes->m_hitPos;
			}


			m_gravity = 0.0f;
			m_bLanding = true;
		}

		result.clear();

		//playerのスフィア情報の作成
		DirectX::BoundingSphere sphere;
		sphere.Center = m_pos;//中心座標
		sphere.Center.y += 0.4f;
		sphere.Radius = 0.25f;//半径

		//壁判定-------------------------------------------------------------------------------------------------
		for (std::shared_ptr<MoveWall>p_wall : moveWall)
		{
			//当たったらresultリストに情報を入れていく
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
