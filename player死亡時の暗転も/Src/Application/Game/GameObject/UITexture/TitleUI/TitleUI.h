#pragma once

class TitleUI :public KdGameObject
{
public:
	TitleUI();
	virtual~TitleUI();

	void Init()override;
	void Update()override;
	void Draw2D();

private:

	std::shared_ptr<KdTexture>m_pTitleLogo = nullptr;

	std::shared_ptr<KdTexture>m_pStartTex = nullptr;

	Math::Matrix m_mRot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(-90));
	Math::Matrix m_mTrans=Math::Matrix::CreateTranslation({8,0,8});

	//‰æ‘œ‚Ìƒ¿’l
	float alpha = 0;

};