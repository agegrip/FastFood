//#pragma once
//#include "DirectXTK\GeometricPrimitive.h"
//#include "DirectXTK\SimpleMath.h"
//#include "GameObject.h"
//#include "Game\Collider\SphereCollider.h"
//
//class Humberger : public GameObject
//{
//public:
//	Humberger(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Vector3& azimuth);
//	~Humberger();
//	void Update(float elapsedTime) override;
//	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix) override;
//	void OnCollision(GameObject* object) override;
//private:
//	std::unique_ptr<DirectX::GeometricPrimitive> m_geomrtricPrimitive;
//	DirectX::SimpleMath::Vector3				 m_velocty;
//	DirectX::SimpleMath::Vector3				 m_origin;
//	std::unique_ptr<SphereCollider>				 m_collider;
//	bool										 m_flag;
//};