#include "GameCamera.h"
#include"Application/main.h"
#include"Application/Game/KdGameSystem.h"
#include"../Character/Player/Player.h"

GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}

void GameCamera::SetSpotCamera(const Math::Vector3& pos, const float& angle, const float& range)
{
	m_CameraPos = pos;
	m_angle_z = angle;
	m_range = range;
}

void GameCamera::Init()
{
	m_pCamera = std::make_shared< KdCamera>();

	m_bRotating = false;
	m_bRotateRight = false;
	m_bRotateLeft = false;

	m_mWorld = Math::Matrix::CreateTranslation(m_CameraPos);
}

void GameCamera::Update()
{
	

	//Math::Matrix cameraMat = Math::Matrix::CreateTranslation(m_CameraPos);

	if (!m_bSpot)
	{
		RotationCamera();
	}
	else//スポットを当ててる際は動けない
	{
		static int frame = 0;

		frame++;
		if (frame > 240)
		{
			m_bSpot = false;
			SetPos(GetSavePos(), GetSaveAngle(),GetSaveRange());//元の位置に戻す
			SetSavePos(Math::Vector3{ 0,0,0 }, 0,0);//保存内容をクリア
			frame = 0;
		}
	}
	//m_mWorld *= Math::Matrix::CreateTranslation(m_CameraPos);


	//スポット時のために移動行列二つ(中心座標から遠ざける->中心座標を軸に回転->中心座標をずらす)
	Math::Matrix rotMat = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_angle_y))
		* DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_angle_z));
	Math::Matrix trans = Math::Matrix::CreateTranslation(0, 0, m_range);

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_CameraPos.x, m_CameraPos.y, m_CameraPos.z);


	//スポット中以外はplayerに追従
	if (!m_bSpot)
	{
		std::shared_ptr<Player>player = Application::Instance().GetObj()->GetPlayer();
		m_trackingPos = player->GetPos();
	}
	else
	{
		m_trackingPos = Math::Vector3::Zero;
	}


	Math::Matrix transForPos = Math::Matrix::CreateTranslation(m_trackingPos);


	m_mWorld = trans * rotMat * transForPos * transMat;

	m_pCamera->SetCameraMatrix(m_mWorld);

}

void GameCamera::Draw()
{
	m_pCamera->SetProjectionMatrix(104.f);

	m_pCamera->SetToShader();
}

void GameCamera::UpdateTitle()
{
	Math::Matrix rotMat = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(m_angle_y))
		* DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(m_angle_z));
	Math::Matrix trans = Math::Matrix::CreateTranslation(0, 0, m_range);

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_CameraPos.x+7, m_CameraPos.y+2, m_CameraPos.z-5);

	m_mWorld = trans * rotMat * transMat;


	m_pCamera->SetCameraMatrix(m_mWorld);
}


void GameCamera::RotationCamera()
{
	if (GetAsyncKeyState('D') & 0x8000)
	{
		if (!m_bRotating)
		{
			m_saveAngle = m_angle_z;
			m_bRotating = true;
			m_bRotateRight = true;
		}

	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		if (!m_bRotating)
		{
			m_saveAngle = m_angle_z;
			m_bRotating = true;
			m_bRotateLeft = true;
		}
	}

	if (m_bRotating)
	{
		RotateRight();
		RotateLeft();
	}



	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_angle_y--;

		if (m_angle_y < -20)
		{
			m_angle_y = -20;
		}
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_angle_y++;

		if (m_angle_y > 30)
		{
			m_angle_y = 30;
		}
	}


	if (GetAsyncKeyState('F') & 0x8000)
	{
		if (m_range > -10)
		{
			m_range -= 0.5;
		}
	}
	if (GetAsyncKeyState('R') & 0x8000)
	{

		if (m_range < -3)
		{
			m_range += 0.5;
		}
	}
}

void GameCamera::RotateRight()
{
	if (!m_bRotateRight)return;

	if (m_angle_z < m_saveAngle + 45)//元の角度から90移動
	{
		m_angle_z += 3;
	}
	else
	{
		m_bRotating = false;
		m_bRotateRight = false;
	}
}

void GameCamera::RotateLeft()
{
	if (!m_bRotateLeft)return;

	if (m_angle_z > m_saveAngle - 45)//元の角度から90移動
	{
		m_angle_z -= 3;
	}
	else
	{
		m_bRotating = false;
		m_bRotateLeft = false;
	}
}
