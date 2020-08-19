//======================================================
// File Name	: FoodGenerator.h
// Summary		: 食品オブジェクト生成
// Date			: 2020/7/21
// Author		: Ryo Irino
//======================================================

#include "DirectXTK\GeometricPrimitive.h"
#include "DirectXTK\SimpleMath.h";
#include "Game\GameObject\GameObject.h"

class FoodGenerator : public GameObject
{
private:
	float m_interval;
	float m_elapsedTime;
public:
	FoodGenerator(float interval);
	~FoodGenerator();
	void Update(float elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix) override;

	void Generate() const;
};