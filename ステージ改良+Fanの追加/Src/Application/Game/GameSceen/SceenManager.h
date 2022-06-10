#pragma once
#include"SceenBase.h"

class SceenManager:public SceenBase
{
public:
	SceenManager();
	~SceenManager(){};

	enum SCENE {
		TITLE,
		GAME,
		RESULT
	};


	void Init();
	void Update();
	void Draw();

	void ChangeSceen(SCENE scene);

private:

	std::shared_ptr<SceenBase>m_pSceen = nullptr;
};