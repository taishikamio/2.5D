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
	if (m_pGoalTex)m_pGoalTex->Load("Asset/Textures/UI/clear.png");
}

void GoalUI::Update()
{

}

void GoalUI::Draw2D()
{
	D3D.WorkShaderManager().m_spriteShader.DrawTex(m_pGoalTex.get(), 0, 0);
}
