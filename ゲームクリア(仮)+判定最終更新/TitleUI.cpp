#include"TitleUI.h"

TitleUI::TitleUI()
{
}

TitleUI::~TitleUI()
{
}

void TitleUI::Init()
{
	m_pTitleLogo = std::make_unique<KdSquarePolygon>();
	if (m_pTitleLogo)m_pTitleLogo->SetMaterial("Asset/titleLogo.png");
	m_pTitleLogo->SetScale({ 9, 9 }, KdSquarePolygon::PivotType::Center_Middle);
}

void TitleUI::Update()
{
	m_mWorld = rot * mat;
}

void TitleUI::Draw()
{
	if (m_pTitleLogo)
	{
		D3D.WorkShaderManager().m_HD2DShader.DrawSquarePolygon(*m_pTitleLogo, m_mWorld);
	}
}
