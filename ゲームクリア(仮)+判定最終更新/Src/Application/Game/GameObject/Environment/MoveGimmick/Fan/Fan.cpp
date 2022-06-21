#include "Fan.h"

Fan::Fan(Math::Vector3 pos)
{
	defaultPos = pos;
}

Fan::~Fan()
{
}

void Fan::Init()
{
	Model3D::Init();
	m_pos = defaultPos;

	m_mWorld = Math::Matrix::CreateTranslation(m_pos);
}

void Fan::Update()
{
	static int angle = 0;

	Math::Matrix scale = Math::Matrix::CreateScale(0.5);

	Math::Matrix trans = Math::Matrix::CreateTranslation(m_pos);

	Math::Matrix rot = Math::Matrix::CreateRotationY(angle);

	m_mWorld = scale * rot* trans;

	angle++;
	if (angle >= 360)
	{
		angle = 0;
	}
}

void Fan::Draw()
{
	if (m_pModel)
	{
		Model3D::DrawOpeque();//fan•”•ª‚Æ”»’è•”•ª‚Å•ª‚¯‚È‚¢‚Æ‚¢‚¯‚È‚¢
	}
}
