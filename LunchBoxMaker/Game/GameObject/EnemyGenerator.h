//
// EnemyGenerator.h
//
#pragma once
#include "DirectXTK\GeometricPrimitive.h"
#include "DirectXTK\SimpleMath.h"
#include "Game\GameObject\GameObject.h"

class EnemyGenerator : public GameObject
{
private:
	float m_interval;
	float m_elapsedTime;

public:
	EnemyGenerator(float interval);
	~EnemyGenerator();

	void Update(float elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix,const DirectX::SimpleMath::Matrix& projectionMatrix) override;
	
	void Generate() const;
};
