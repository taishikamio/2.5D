#pragma once
#include"../SceenBase.h"

class Game :public SceenBase
{
public:
	Game();
	virtual~Game() {};

	void Draw()override;

private:
};