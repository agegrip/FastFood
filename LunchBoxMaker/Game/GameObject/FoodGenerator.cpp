//======================================================
// File Name	: FoodGenerator.cpp
// Summary		: 食品オブジェクト生成
// Date			: 2020/7/21
// Author		: Ryo Irino
//======================================================

#include "FoodGenerator.h"
#include <random>
#include "Game\Common\DeviceResources.h"
#include "Game\Common\GameContext.h"
#include "Game\Common\Utilities.h"
#include "Game\GameObject\GameObjectManager.h"
#include "Game\GameObject\Food.h"

FoodGenerator::FoodGenerator(float interval)
	:GameObject("Food")
	,m_interval(interval)
	,m_elapsedTime(0.0f)
{
}

FoodGenerator::~FoodGenerator()
{
}

void FoodGenerator::Update(float elapsedTime)
{
	m_elapsedTime += elapsedTime;
	if (m_elapsedTime > m_interval)
	{
		std::vector<GameObject*> result = GameContext<GameObjectManager>::Get()->Find("Food");
		if (result.size() < 3)
		{
			Generate();
			m_elapsedTime = 0.0f;
		}
	}
}

void FoodGenerator::Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
}

void FoodGenerator::Generate() const
{
	std::unique_ptr<Food> food = std::make_unique<Food>(DirectX::SimpleMath::Vector3(5.0f,0.0f,2.0f));
	GameContext<GameObjectManager>::Get()->Add(std::move(food));
}