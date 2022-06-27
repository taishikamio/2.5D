#pragma once

class TitleUI
{
public:
	TitleUI(); 
	~TitleUI(); 

	void Init();
	void Update();
	void Draw();

private:

	std::unique_ptr<KdSquarePolygon>m_pTitleLogo = nullptr;
	Math::Matrix rot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(-90));
	Math::Matrix mat = Math::Matrix::CreateTranslation({ 8,0,8 });

	Math::Matrix m_mWorld;
};