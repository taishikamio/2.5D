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
	KdSquarePolygon *poly;
	//Math::Matrix m_mWorld;
};