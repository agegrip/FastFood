#pragma once
#include <3rdParty\DirectXTK\Include\DirectXTK\SimpleMath.h>

class FixCamera
{
public:
	// �r���[�s��擾
	DirectX::SimpleMath::Matrix getViewMatrix()
	{
		return m_viewMatrix;
	}
	// �ˉe�s��擾
	DirectX::SimpleMath::Matrix getProjectionMatrix()
	{
		return m_projectionMatrix;
	}
	// �J�����̈ʒu�擾
	DirectX::SimpleMath::Vector3 getEyePosition()
	{
		return m_eye;
	}
	// �J�����̒����_�擾
	DirectX::SimpleMath::Vector3 getTargetPosition()
	{
		return m_target;
	}
	// �J�����̎ˉe�s��擾
	FixCamera();
	~FixCamera();
	void Initialize();
	void Update();
	void Create(float fovAngle, float aspectRatio, float nearPlane, float farPlane);

private:
	// �r���[�s��
	DirectX::SimpleMath::Matrix			m_viewMatrix;
	// �ˉe�s��
	DirectX::SimpleMath::Matrix			m_projectionMatrix;
	// ���_
	DirectX::SimpleMath::Vector3		m_eye;
	// �����_
	DirectX::SimpleMath::Vector3		m_target;
};

