#include "sky.h"

Sky::Sky()
{
	m_pModel = make_unique<KdModelData>();
}

void Sky::Draw()
{
	if (m_pModel)D3D.WorkShaderManager().m_HD2DShader.DrawModel(*m_pModel, Math::Matrix::Identity, Math::Color(1.0f, 0.6f, 0.6f, 1.0f));
}

void Sky::Update()
{
}