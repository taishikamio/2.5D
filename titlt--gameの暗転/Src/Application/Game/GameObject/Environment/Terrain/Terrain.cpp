#include "Terrain.h"

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
}

void Terrain::InitTitle(Math::Vector3 pos)
{
	m_mTrans = Math::Matrix::CreateTranslation(pos);
	if (m_pModel) m_pModel->SetModel(m_pModelData);
}

void Terrain::UpdateTitle()
{

	m_angle++;
	if (m_angle >= 360)m_angle = 0;

	m_mRot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));

	m_mWorld = m_mRot* m_mTrans;
}
