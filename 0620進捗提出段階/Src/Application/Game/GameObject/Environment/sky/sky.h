#pragma once
class Sky
{
public:
	Sky();
	~Sky() {}

	void SetAsset(const string_view filePath) { if (m_pModel) m_pModel->Load(filePath.data()); }

	void Draw();
	void Update();

private:
	unique_ptr<KdModelData>m_pModel = nullptr;

	Math::Matrix m_mWorld = Math::Matrix::Identity;
};
