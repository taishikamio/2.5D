#pragma once

class SceenBase
{
public:
	SceenBase();
	~SceenBase();

	virtual void Draw() = 0;
	virtual void Init() = 0;
	virtual void Update() = 0;



protected:
};