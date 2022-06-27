#pragma once
class CharacterBase :public KdGameObject
{
public:
	CharacterBase() {}
	virtual ~CharacterBase() {}

	virtual void Draw() {};
	virtual void Update() {};
	virtual void Init() {};

protected:
	std::shared_ptr<KdSquarePolygon> m_pPoly = nullptr;
	//Math::Matrix m_mWorld;
};