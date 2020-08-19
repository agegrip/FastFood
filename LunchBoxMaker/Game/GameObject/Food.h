//======================================================
// File Name	: Food.h
// Summary		: 食品オブジェクト
// Date			: 2020/7/01
// Author		: Ryo Irino
//======================================================
#include "Game\GameObject\GameObject.h"
#include "DirectXTK\SimpleMath.h"
#include "DirectXTK\GeometricPrimitive.h"
#include "Game\Collider\SphereCollider.h"

class Food :public GameObject
{
public:
	static const float MOVE_SPEED;
	static float MOVABLE_AREA_SIZE;
public:
	Food(const DirectX::SimpleMath::Vector3& azimuth);
	~Food();
	void Update(float elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix) override;
	void OnCollision(GameObject* object) override;
private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;
	DirectX::SimpleMath::Vector3				 m_velocity;
	DirectX::SimpleMath::Vector3				 m_origin;
	std::unique_ptr<SphereCollider>				 m_collider;
	bool										 m_flag;
};