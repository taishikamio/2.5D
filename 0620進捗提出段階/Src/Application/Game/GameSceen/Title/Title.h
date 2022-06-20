#pragma once
#include"../SceenBase.h"

class Title :public SceenBase
{
public:
	Title();
	virtual~Title() {};

	void Draw()override;

	//const std::shared_ptr<Title>GetThis() { return ; }

private:
};