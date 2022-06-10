#pragma once
class KdGameSystem;
class Enemy;

class Bullet
{
public:
	Bullet() {}
	~Bullet() { Release(); }

	void Draw();
	void Update();
	void Init();

	inline void SetAsset(std::string_view filePath) { poly->SetMaterial(filePath); }
	void SetEnemy(Enemy* enemy) { m_pEnemy = enemy; }

	void Shot(Math::Vector3 _pos, Math::Vector3 _dir) { m_mWorld.Translation(_pos); moveDir = _dir; };
private:
	KdSquarePolygon* poly;

	Enemy* m_pEnemy = nullptr;

	Math::Vector3 moveDir = { 0,0,0 };
	float moveSpeed = 0.2;
	Math::Matrix m_mWorld = Math::Matrix::Identity;

	bool m_Alive = true;
	void Release();
};
