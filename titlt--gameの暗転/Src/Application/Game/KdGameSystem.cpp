#include"KdGameSystem.h"
#include "GameObject/Character/Player/Player.h"// 前方宣言した後に実体を持たせる必要がある
#include"GameObject/GameCamera/GameCamera.h"
#include"GameObject/Environment/Terrain/Terrain.h"
#include"GameObject/Environment/MoveGimmick/Wall/Wall.h"
#include"GameObject/Environment/MoveGimmick/Lever/Lever.h"
#include"../Utility.h"
#include"GameSceen/SceenManager.h"
#include"GameObject/Environment/GoalObject/GoalObject.h"
#include"GameObject/Environment/MoveGimmick/Fan/Fan.h"
#include"GameObject/Environment/MoveGimmick/Wind/HitBoxWind.h"


#include"GameObject/UITexture/TitleUI/TitleUI.h"
#include"GameObject/UITexture/GameUI/GameUI.h"
#include"GameObject/UITexture/GameUI/GoalUI/GoalUI.h"


KdGameSystem::KdGameSystem()
{
}

KdGameSystem::~KdGameSystem()
{
	Release();
}

void KdGameSystem::Init()
{
	//m_pSceen = std::make_shared<SceenManager>();
	//if (m_pSceen)m_pSceen->Init();

	switch (nowSceen)
	{

	case Title:
		InitTitle();
		break;

	case Game:
		InitGame();
		break;

	default:
		break;
	}

	m_pBlackBackTex = nullptr;
	m_pBlackBackTex = std::make_unique<KdTexture>();
	m_pBlackBackTex->Load("Asset/Textures/Back/BlackBack.png");
	//m_pBlackBackTex->SetScale({ 300.0f ,300.0f});

}

void KdGameSystem::Update()
{

	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (!key)
		{
			m_bChange = true;
		}
	}
	else
	{
		key = false;
	}


	if (GetAsyncKeyState('X') & 0x8000)
	{
		if (!key)
		{
			InitGame();
		}
	}
	else
	{
		key = false;
	}


	//遷移時の暗転
	if (m_bChange)
	{
		if (m_backAlpha<1)
		{
			m_backAlpha += 0.05;
		}

		if (m_backAlpha >= 1)
		{
			if (nowSceen == Title)
			{
				key = true;
				nowSceen = Game;
				m_bChange = false;
				m_bChanged = true;
				InitGame();
				
			}
			else if (nowSceen == Game)
			{
				key = true;
				nowSceen = Title;
				m_bChange = false;
				m_bChanged = true;
				InitTitle();
				
			}
		}
	}
	if (m_bChanged)
	{
		if (m_backAlpha > 0)
		{
			m_backAlpha -= 0.05;
		}

		if (m_backAlpha <= 0)
		{
			m_bChanged = false;
		}
	}



	
	//if (m_pSceen)m_pSceen->Update();

	switch (nowSceen)
	{

	case Title:
		UpdateTitle();
		break;

	case Game:
		UpdateGame();
		break;

	default:
		break;
	}



}

void KdGameSystem::Draw()
{
	switch (nowSceen)
	{

	case Title:
		DrawTitle();
		break;

	case Game:
		DrawGame();
		break;

	default:
		break;
	}


	D3D.WorkShaderManager().m_HD2DShader.BeginLighting();
	{
		if (m_pBlackBackTex)
		{
			D3D.WorkShaderManager().m_spriteShader.DrawTex(m_pBlackBackTex.get(), 0, 0, nullptr, &Math::Color(1, 1, 1, m_backAlpha));
		}
	}
	D3D.WorkShaderManager().m_HD2DShader.EndLighting();


}

void KdGameSystem::InitTitle()
{
	m_pTitleUI = std::make_unique<TitleUI>();
	if (m_pTitleUI)m_pTitleUI->Init();


	//GameCamera
	m_pCamera = std::make_shared<GameCamera>();
	if (m_pCamera)m_pCamera->Init();


	//Terrain
	m_pTerrain = std::make_unique<Terrain>();
	if (m_pTerrain) m_pTerrain->SetAsset("Asset/Models/Stage/Stage/Stage1/Stage1.gltf");
	if (m_pTerrain)m_pTerrain->InitTitle(Math::Vector3(0, 0, -10));


	//Sky
	m_pSky = std::make_shared<KdModelData>();
	if (m_pSky)m_pSky->Load("Asset/Models/Sky/BlueSky.gltf");



}

void KdGameSystem::UpdateTitle()
{
	if (m_pCamera)m_pCamera->UpdateTitle();
	if (m_pTerrain)m_pTerrain->UpdateTitle();
	if (m_pTitleUI)m_pTitleUI->Update();


}

void KdGameSystem::DrawTitle()
{
	//if (m_pSceen)m_pSceen->Draw();

	if (m_pCamera)m_pCamera->Draw();

	D3D.WorkShaderManager().m_HD2DShader.BeginNoLighting();
	{
		D3D.WorkShaderManager().m_HD2DShader.DrawModel(*m_pSky);
	}
	D3D.WorkShaderManager().m_HD2DShader.EndNoLighting();


	D3D.WorkShaderManager().m_HD2DShader.BeginLighting();
	{
		if (m_pTerrain) m_pTerrain->DrawOpeque();

		if (m_pTitleUI)m_pTitleUI->Draw2D();

	}
	D3D.WorkShaderManager().m_HD2DShader.EndLighting();

}

void KdGameSystem::InitGame()
{


	//GameCamera
	m_pCamera = std::make_shared<GameCamera>();
	if (m_pCamera)m_pCamera->Init();


	//Sky
	m_pSky = std::make_shared<KdModelData>();
	if (m_pSky)m_pSky->Load("Asset/Models/Sky/BlueSky.gltf");



	// プレイヤーオブジェクトの実体化(インスタンス化)
	m_pPlayer = std::make_shared<Player>();
	m_pPlayer->Init();

	//ギミック壁
	if (!m_pMoveWall.size())m_pMoveWall.push_back(std::make_shared<MoveWall>(Math::Vector3(-4, 4.5, 4), 90));
	if (m_pMoveWall.size() == 1)m_pMoveWall.push_back(std::make_shared<MoveWall>(Math::Vector3(-2, 1.5, 3), 0));

	for (std::shared_ptr<MoveWall> pMoveWall : m_pMoveWall)
	{
		pMoveWall->SetAsset("Asset/Models/Stage/Wall/wall.gltf");
		pMoveWall->Init();
	}


	//Terrain
	m_pTerrain = std::make_unique<Terrain>();
	if (m_pTerrain) m_pTerrain->SetAsset("Asset/Models/Stage/Stage/ex/ex.gltf");
	if (m_pTerrain)m_pTerrain->Init();

	//ファン
	if (!m_pFan.size())m_pFan.push_back(std::make_shared<Fan>(Math::Vector3(-2.5, -0.3, 18.3)));
	if (m_pFan.size() == 1)m_pFan.push_back(std::make_shared<Fan>(Math::Vector3(-1, 3.8, 12.3)));

	for (std::shared_ptr<Fan> pFan : m_pFan)
	{
		pFan->SetAsset("Asset/Models/Stage/Fan/Fan.gltf");
		pFan->Init();

	}

	//風の判定
	if (!m_pWind.size())m_pWind.push_back(std::make_shared<HitBoxWind>());
	if (m_pWind.size() == 1)m_pWind.push_back(std::make_shared<HitBoxWind>());

	for (int i = 0; i < m_pWind.size(); ++i)
	{
		m_pWind[i]->SetAsset("Asset/Models/Stage/Wind/HitBoxWind.gltf");
		m_pWind[i]->Init(m_pFan[i]->GetPos());
	}


	//レバー
	if (!m_pLever.size())m_pLever.push_back(std::make_shared<Lever>(Math::Vector3(-4, 3.1, -3.5)));// = std::make_shared<Lever>();
	if (m_pLever.size() == 1)m_pLever.push_back(std::make_shared<Lever>(Math::Vector3(-4, 3, 1.5)));
	for (std::shared_ptr<Lever> p_lever : m_pLever)
	{
		p_lever->SetAsset("Asset/Models/Stage/Lever/lever.gltf");
		p_lever->Init();
	}

	m_pGoal = std::make_shared<GoalObject>();
	if (m_pGoal)m_pGoal->SetAsset("Asset/Models/Stage/Flag/flag.gltf");
	if (m_pGoal)m_pGoal->Init();

	//UI
	m_pGameUI = std::make_unique<GameUI>();
	m_pGameUI->Init();

	GimmickBit::InitBit();
}

void KdGameSystem::UpdateGame()
{
	if (m_pCamera)m_pCamera->Update();


	if (!m_pPlayer->IsAlive())
	{
		InitGame();
	}

	if (m_pPlayer) { m_pPlayer->Update(); }

	if (!m_pGoal->GetbGoal())
	{
		m_pPlayer->SetCanMove(true);
	}
	else
	{
		m_pPlayer->SetCanMove(false);
		if (m_pGoalUI == nullptr)
		{
			m_pGoalUI = std::make_unique<GoalUI>();
			m_pGoalUI->Init();
		}

		m_pGoalUI->Update();
	}





	if (m_pTerrain) { m_pTerrain->Update(); }

	for (std::shared_ptr<MoveWall> pMoveWall : m_pMoveWall)
	{
		pMoveWall->Update();
	}

	for (std::shared_ptr<Lever> p_lever : m_pLever)
	{
		p_lever->Update();
	}

	if (m_pGoal)m_pGoal->Update();

	if (m_pGameUI)m_pGameUI->Update();

	for (std::shared_ptr<Fan> pFan : m_pFan)
	{
		pFan->Update();
	}

	for (std::shared_ptr<HitBoxWind> pWind : m_pWind)
	{
		pWind->Update();
	}


	//ビットで動作元と動作先を紐づける(シフトですべてのフラグをチェックする)------------------------------------
	for (int i = 0; i < m_pLever.size(); i++)
	{
		if (m_pLever[i]->GetFlg())
		{
			if (!(GimmickBit::m_nowGimmickBit & GimmickBit::m_masc << i))
			{
				GimmickBit::m_nowGimmickBit += GimmickBit::m_masc << i;
			}
		}
	}

	GimmickBit::m_masc = 1;

	for (int i = 0; i < m_pMoveWall.size(); i++)
	{
		if (GimmickBit::m_nowGimmickBit & GimmickBit::m_masc << i)
		{
			if (!m_pMoveWall[i]->GetClear())
			{
				m_pMoveWall[i]->SetClear();
				if (m_pCamera->GetSavePos() == Math::Vector3{ 0,0,0 })
				{
					m_pCamera->SetSavePos(m_pCamera->GetPos(), m_pCamera->GetAngle(), m_pCamera->GetRange());
					m_pCamera->SetSpotCamera(m_pMoveWall[i]->GetPos(), m_pMoveWall[i]->GetAngle() + 90, -10);
					m_pCamera->SetSpot(true);
				}
			}
		}
	}
	//-----------------------------------------------------------------------------------

	//killされたら
	//for (int i = 0; i < m_pMoveWall.size(); i++)
	//{
	//	if (m_pMoveWall[i])
	//	{
	//		if (m_pMoveWall[i]->GetKilled())
	//		{
	//			//m_pMoveWall.erase(std::cbegin(m_pMoveWall)+i);
	//			//break;
	//		}
	//	}

	//}

	//-----------------------------------------------------------------------


}

void KdGameSystem::DrawGame()
{


	if (m_pCamera)m_pCamera->Draw();

	D3D.WorkShaderManager().m_HD2DShader.BeginNoLighting();
	{
		//D3D.WorkShaderManager().m_HD2DShader.DrawSquarePolygon(TreePoly);
		D3D.WorkShaderManager().m_HD2DShader.DrawModel(*m_pSky);
	}
	D3D.WorkShaderManager().m_HD2DShader.EndNoLighting();

	//陰影あり
	D3D.WorkShaderManager().m_HD2DShader.BeginLighting();
	{
		if (m_pTerrain) m_pTerrain->DrawOpeque();

		for (std::shared_ptr<MoveWall> pMoveWall : m_pMoveWall)
		{
			pMoveWall->Draw();
		}

		for (std::shared_ptr<Lever> p_lever : m_pLever)
		{
			p_lever->Draw();
		}

		if (m_pPlayer)
		{
			m_pPlayer->Draw();
		}

		if (m_pGoal)m_pGoal->Draw();

		for (std::shared_ptr<Fan> pFan : m_pFan)
		{
			pFan->Draw();
		}

		for (std::shared_ptr<HitBoxWind> pWind : m_pWind)
		{
			pWind->Draw();
		}

		if (m_pGameUI)m_pGameUI->Draw2D();
		if (m_pGoalUI)	m_pGoalUI->Draw2D();



	}
	D3D.WorkShaderManager().m_HD2DShader.EndLighting();

}

void KdGameSystem::Release()
{
	//KdSafeDelete(m_pPlayer);
}
