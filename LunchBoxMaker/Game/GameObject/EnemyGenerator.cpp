//
// EnemyGenerator.cpp
//

#include "EnemyGenerator.h"
#include <random>
#include "Game\Common\DeviceResources.h"
#include "Game\Common\GameContext.h"
#include "Game\Common\Utilities.h"
#include "Game\GameObject\GameObjectManager.h"
#include "Game\GameObject\Enemy.h"

EnemyGenerator::EnemyGenerator(float interval)
	: GameObject("EnemyGenerator")
	, m_interval(interval)
	, m_elapsedTime(0.0f)
{
}

EnemyGenerator::~EnemyGenerator()
{
}

void EnemyGenerator::Update(float elapsedTime)
{
	m_elapsedTime += elapsedTime;
	if (m_elapsedTime > m_interval)
	{
		std::vector<GameObject*> result = GameContext<GameObjectManager>::Get()->Find("Enemy");
		if (result.size() < 3)
		{
			Generate();
			m_elapsedTime = 0.0f;
		}
	}
}

void EnemyGenerator::Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
}

void EnemyGenerator::Generate() const
{
	std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>();
	GameContext<GameObjectManager>::Get()->Add(std::move(enemy));
}