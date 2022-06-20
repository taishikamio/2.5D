#pragma once

class GameUI :public KdGameObject
{
public:
	GameUI();
	virtual~GameUI();

	void Init()override;
	void Update()override;
	void Draw2D();
private:

	std::shared_ptr<KdTexture>m_pGimmickUITex = nullptr;

	std::shared_ptr<KdTexture>m_pCameraMove = nullptr;
	std::shared_ptr<KdTexture>m_pMove = nullptr;
	std::shared_ptr<KdTexture>m_pJump = nullptr;

};