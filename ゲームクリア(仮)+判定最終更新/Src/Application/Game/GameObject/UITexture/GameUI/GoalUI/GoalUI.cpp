#include "GoalUI.h"
#include"../../../Environment/GoalObject/GoalObject.h"
//#include""

GoalUI::GoalUI()
{

}

GoalUI::~GoalUI()
{
}

void GoalUI::Init()
{
	m_pGoalTex = std::make_shared<KdTexture>();
	if (m_pGoalTex)
	{
		m_pGoalTex->Load("Asset/Textures/UI/clear.png");

		m_pos = Math::Vector2{ 0.0f,400.0f };
	}
}

void GoalUI::Update()
{
	if (m_pos.y > 200)
	{
		m_pos.y--;
	}
}

void GoalUI::Draw2D()
{
	D3D.WorkShaderManager().m_spriteShader.DrawTex(m_pGoalTex.get(), m_pos.x, m_pos.y);
}
