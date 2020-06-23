#pragma once
#include <3rdParty\DirectXTK\Include\DirectXTK\SimpleMath.h>

class FixCamera
{
public:
	// ビュー行列取得
	DirectX::SimpleMath::Matrix getViewMatrix()
	{
		return m_viewMatrix;
	}
	// 射影行列取得
	DirectX::SimpleMath::Matrix getProjectionMatrix()
	{
		return m_projectionMatrix;
	}
	// カメラの位置取得
	DirectX::SimpleMath::Vector3 getEyePosition()
	{
		return m_eye;
	}
	// カメラの注視点取得
	DirectX::SimpleMath::Vector3 getTargetPosition()
	{
		return m_target;
	}
	// カメラの射影行列取得
	FixCamera();
	~FixCamera();
	void Initialize();
	void Update();
	void Create(float fovAngle, float aspectRatio, float nearPlane, float farPlane);

private:
	// ビュー行列
	DirectX::SimpleMath::Matrix			m_viewMatrix;
	// 射影行列
	DirectX::SimpleMath::Matrix			m_projectionMatrix;
	// 視点
	DirectX::SimpleMath::Vector3		m_eye;
	// 注視点
	DirectX::SimpleMath::Vector3		m_target;
};

