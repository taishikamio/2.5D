#pragma once
class Model3D :public KdGameObject
{
public:
	Model3D();
	virtual ~Model3D() {}

	void SetAsset(const std::string_view filePath)override { if (m_pModelData) m_pModelData->Load(filePath.data()); }

	//•s“§–¾•¨‚Ì•`‰æ
	void DrawOpeque()override;
	void Update();
	void Init();

protected:
	std::shared_ptr<KdModelWork>m_pModel = nullptr;
	std::shared_ptr<KdModelData>m_pModelData = nullptr;
};