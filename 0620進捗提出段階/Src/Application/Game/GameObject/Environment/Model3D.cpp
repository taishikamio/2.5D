#include"Model3D.h"
Model3D::Model3D()
{
	m_pModel = std::make_shared<KdModelWork>();
	m_pModelData=std::make_shared<KdModelData>();
}
void Model3D::DrawOpeque()
{
	if (m_pModel) { D3D.WorkShaderManager().m_HD2DShader.DrawModel(*m_pModel, m_mWorld); }
}

void Model3D::Update()
{
	
}

void Model3D::Init()
{
	if (!m_pCollider)m_pCollider = std::make_unique<KdCollider>(*this);//ŽÀ‘Ô‚ð“n‚·
	m_pCollider->AddCollisionShape(std::make_shared<ModelCollision>(m_pModel, KdCollider::TypeGround|KdCollider::TypeBump|KdCollider::TypeCeiling));

	if (m_pModel) m_pModel->SetModel(m_pModelData);
}