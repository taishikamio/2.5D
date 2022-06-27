#pragma once

class GoalUI :public KdGameObject
{
public:
	GoalUI();
	virtual~GoalUI();

	void Init()override;
	void Update()override;
	void Draw2D();
private:

	std::shared_ptr<KdTexture>m_pGoalTex = nullptr;
	
	Math::Vector2 m_pos;
};