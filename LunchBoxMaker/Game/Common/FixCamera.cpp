#include "pch.h"
#include "FixCamera.h"


FixCamera::FixCamera()
{
}


FixCamera::~FixCamera()
{
}

void FixCamera::Initialize()
{

}

void FixCamera::Update()
{
	DirectX::SimpleMath::Vector3 eye(0.0f, 10.0f, 10.0f);
	DirectX::SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	m_eye = eye;
	m_target = target;

	m_viewMatrix = DirectX::SimpleMath::Matrix::CreateLookAt(eye, target, up);
}

void FixCamera::Create(float fovAngle, float aspectRatio, float nearPlane, float farPlane)
{
	m_projectionMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(fovAngle, aspectRatio, nearPlane, farPlane);
}