#pragma once

class GameCamera :public KdCamera
{
public:

	GameCamera();
	virtual~GameCamera();

	Math::Vector3 GetPos() { return m_CameraPos; }
	float GetAngle() { return m_angle_z; }
	float GetRange() { return m_range; }
	bool GetRotate() { return m_bRotating; }
	Math::Matrix GetMatrix() { return m_mWorld; }


	void SetSpot(bool spot) { m_bSpot = spot; }
	bool GetSpot() { return m_bSpot; }

	void SetSpotCamera(Math::Vector3 pos, float angle, float range);

	Math::Vector3 GetSavePos() { return m_savePos; }
	float GetSaveAngle() { return m_saveAngle; }
	float GetSaveRange() { return m_saveRange; }
	void  SetSavePos(const Math::Vector3 pos, float angle, float rangle)
	{
		m_savePos = pos;
		m_saveAngle = angle;
		m_saveRange = rangle;
	}

	void  SetPos(const Math::Vector3 pos, float angle, float range)
	{
		m_CameraPos = pos;
		m_angle_z = angle;
		m_range = range;
	}




	void Init();
	void Update();
	void Draw();


	void UpdateTitle();

private:

	void RotationCamera();

	void RotateRight();
	void RotateLeft();

	std::shared_ptr<KdCamera>m_pCamera = nullptr;

	Math::Matrix m_mWorld;

	float m_range = -5;
	float m_angle_z = -90;
	float m_angle_y = 10;


	bool m_bRotating;
	bool m_bRotateRight;
	bool m_bRotateLeft;


	bool m_bSpot = false;

	Math::Vector3 m_trackingPos;

	//•Û‘¶—p
	Math::Vector3 m_savePos = { 0,0,0 };
	float m_saveAngle;
	float m_saveRange;

	Math::Vector3 m_CameraPos = { 0.0f,0.0f,0.0f };


};