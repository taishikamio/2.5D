#include "GameUI.h"
#include"../../../GameObject/Environment/MoveGimmick/Lever/Lever.h"
#include"Application/main.h"
#include"Application/Game/KdGameSystem.h"
#include"../../../GameObject/GameCamera/GameCamera.h"


#include"../../../GameObject/Character/Player/Player.h"


GameUI::GameUI()
{
}

GameUI::~GameUI()
{
}

void GameUI::Init()
{
	m_pGimmickUITex = std::make_shared<KdTexture>();
	if (m_pGimmickUITex)m_pGimmickUITex->Load("Asset/Textures/UI/gimmickUI.png");

	m_pCameraMove = std::make_shared<KdTexture>();
	if (m_pCameraMove)m_pCameraMove->Load("Asset/Textures/UI/cameramove.png");

	m_pMove = std::make_shared<KdTexture>();
	if (m_pMove)m_pMove->Load("Asset/Textures/UI/move.png");

	m_pJump = std::make_shared<KdTexture>();
	if (m_pJump)m_pJump->Load("Asset/Textures/UI/jump.png");

}

void GameUI::Update()
{
	


}

void GameUI::Draw2D()
{
	
	std::vector<std::shared_ptr<Lever>>lever = Application::Instance().GetObj()->GetLever();

	for (std::shared_ptr<Lever> pLever : lever)
	{
		if (pLever->GetUIFlg())
		{
			D3D.WorkShaderManager().m_spriteShader.DrawTex(m_pGimmickUITex.get(),130,100);
		
		}
	}

	D3D.WorkShaderManager().m_spriteShader.DrawTex(m_pCameraMove.get(), -250, -200);
	D3D.WorkShaderManager().m_spriteShader.DrawTex(m_pMove.get(), 250, -200);
	D3D.WorkShaderManager().m_spriteShader.DrawTex(m_pJump.get(), 250, -150);
}

