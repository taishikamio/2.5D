#include "TitleUI.h"
#include"Application/main.h"
#include"Application/Game/KdGameSystem.h"
#include"../../GameCamera/GameCamera.h"

TitleUI::TitleUI()
{
}

TitleUI::~TitleUI()
{
}

void TitleUI::Init()
{
	m_pTitleLogo = std::make_shared<KdTexture>();
	if (m_pTitleLogo)m_pTitleLogo->Load("Asset/Textures/UI/titleLogo.png");
	//m_pTitleLogo->SetScale({ 9, 9 }, KdSquarePolygon::PivotType::Center_Middle);


	m_pStartTex = std::make_shared<KdTexture>();
	if (m_pStartTex)m_pStartTex->Load("Asset/Textures/UI/PushEnter.png");
}

void TitleUI::Update()
{

	static int frame = 40;

	alpha = sin(DirectX::XMConvertToRadians(frame));

	//Math::Matrix scale = Math::Matrix::CreateScale(10000);

	m_mWorld = m_mRot * m_mTrans;

	frame++;

	if (frame > 155)
	{
		frame = 25;
	}
}

void TitleUI::Draw2D()
{
	if (m_pTitleLogo)
	{
		//KdCamera* camera = Application::Instance().GetCamera();

			//spriteshader全体のサイズ感を変える
		/*	Math::Matrix scale = Math::Matrix::CreateScale(2);
			D3D.WorkShaderManager().m_spriteShader.SetMatrix(scale);*/

		D3D.WorkShaderManager().m_spriteShader.DrawTex(m_pTitleLogo.get(), 350, 100);

		D3D.WorkShaderManager().m_spriteShader.DrawTex(m_pStartTex.get(), 380, -100, nullptr, &Math::Color(1, 1, 1, alpha));

		//D3D.WorkShaderManager().m_HD2DShader.DrawSquarePolygon(*m_pTitleLogo, m_mWorld);
	}
}
