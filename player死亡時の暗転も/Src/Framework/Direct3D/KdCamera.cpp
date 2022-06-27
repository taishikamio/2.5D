#include "KdCamera.h"

// 射影行列の設定
void KdCamera::SetProjectionMatrix(float fov, float maxRange, float minRange, float aspectRatio)
{
	m_mProj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(fov), aspectRatio, minRange, maxRange);


	SetProjectionMatrix(m_mProj);

	m_nearClippingDistance = minRange;
	m_farClippingDistance = maxRange;
}

void KdCamera::SetProjectionMatrix(const DirectX::SimpleMath::Matrix& rProj)
{
	m_mProj = rProj;

	m_nearClippingDistance = -(m_mProj._43 / m_mProj._33);
	m_farClippingDistance = -(m_mProj._43 / (m_mProj._33 - 1));
}

void KdCamera::SetFocus(float focusDist, float focusForeRange, float focusBackRange)
{
	m_focusDistance = focusDist;
	m_focusForeRange = focusForeRange;
	m_focusBackRange = focusBackRange;
}

// カメラ行列のセット・カメラ行列からビュー行列を生成
void KdCamera::SetCameraMatrix(const DirectX::SimpleMath::Matrix& mCam)
{
	// カメラ行列セット
	m_mCam = mCam;

	// カメラ行列からビュー行列を算出
	m_mView = mCam.Invert();
}

// ビュー行列のセット・ビュー行列からカメラ行列を生成
void KdCamera::SetViewMatrix(const DirectX::SimpleMath::Matrix& mView)
{
	// ビュー行列セット
	m_mView = mView;

	// ビュー行列からカメラ行列を算出
	m_mCam = mView.Invert();
}

// カメラ情報(ビュー・射影行列など)をシェーダへセット
void KdCamera::SetToShader() const
{
	auto& cbCamera = D3D.WorkShaderManager().m_cb7_Camera.Work();

	// カメラ座標をセット
	cbCamera.CamPos = m_mCam.Translation();

	// ビュー行列をセット
	cbCamera.mView = m_mView;

	// 射影行列をセット
	cbCamera.mProj = m_mProj;

	cbCamera.mProjInv = m_mProj.Invert();

	// カメラ情報(ビュー行列、射影行列)を、シェーダの定数バッファへ書き込む
	D3D.WorkShaderManager().m_cb7_Camera.Write();

	// DepthOfFieldの情報も更新
	float viewRange = m_farClippingDistance - m_nearClippingDistance;

	D3D.WorkShaderManager().m_postProcessShader.SetNearClippingDistance(m_nearClippingDistance);
	D3D.WorkShaderManager().m_postProcessShader.SetFarClippingDistance(m_farClippingDistance);
	D3D.WorkShaderManager().m_postProcessShader.SetFocusDistance((m_focusDistance - m_nearClippingDistance) / viewRange);
	D3D.WorkShaderManager().m_postProcessShader.SetFocusRange(m_focusForeRange / viewRange, m_focusBackRange / viewRange);
}

void KdCamera::GenerateCameraRayInfoFromClientPos(const POINT& clientPos, Math::Vector3& rayPos, Math::Vector3& rayDir, float& rayRange)
{
	Math::Vector3 farPos;

	D3D.ClientToWorld(clientPos, 0.0f, rayPos);
	D3D.ClientToWorld(clientPos, 1.0f, farPos);

	rayDir = farPos - rayPos;

	rayRange = rayDir.Length();

	rayDir.Normalize();
}



void KdCamera::ConvertScreenToWorldDetail(const Math::Vector2& pos, Math::Vector3& result)
{
	// ビューポートを取得する
	Math::Viewport vp;
	D3D.CopyViewportInfo(vp);

	// 射影行列系に変換
	Math::Matrix trans = Math::Matrix::CreateTranslation
	(
		pos.x / (vp.width * 0.5f),
		pos.y / (vp.height * 0.5f),
		0
	);

	// 2D -> 3Dの変換用行列
	Math::Matrix convertMat = trans * GetProjMatrix().Invert() * GetViewMatrix().Invert();

	// 奥行情報を元に戻す
	convertMat._41 /= convertMat._44;
	convertMat._42 /= convertMat._44;
	convertMat._43 /= convertMat._44;

	result = convertMat.Translation();
}

void KdCamera::ConvertWorldToScreenDetail(const Math::Vector3& pos, Math::Vector3& result)
{
	// ビューポートを取得する
	Math::Viewport vp;
	D3D.CopyViewportInfo(vp);

	// ワールド変換行列 * ビュー行列 * 射影行列を取得
	Math::Matrix world = Math::Matrix::CreateTranslation(pos);
	Math::Matrix wvp = world * GetViewMatrix() * GetProjMatrix();

	// 奥行情報を取得
	wvp._41 /= wvp._44;
	wvp._42 /= wvp._44;
	wvp._43 /= wvp._44;

	// 射影行列での2D座標(に近いもの)
	Math::Vector3 localPos = wvp.Translation();

	// 幅や高さを考慮して最計算する
	result.x = localPos.x * (vp.width * 0.5f);
	result.y = localPos.y * (vp.height * 0.5f);
	result.z = wvp._44;
}
