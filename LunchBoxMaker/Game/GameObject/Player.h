#pragma once
#include "DirectXTK\GeometricPrimitive.h"
#include "DirectXTK\SimpleMath.h"
#include "DirectXTK\SpriteBatch.h"
#include "DirectXTK\SpriteFont.h"
#include "GameObject.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Player : public GameObject
{
public:
	Player(const DirectX::SimpleMath::Vector3& position,float fireInterval);
	~Player();
	void Update(float elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix) override;
	void Fire();
private:
	float m_elapsedTime;
	float m_fireInterval;
	bool  m_isLoading;
	float m_horizontalAngle;
	std::unique_ptr<DirectX::GeometricPrimitive> m_playerGeometric;
	std::string m_bulletName;

	DirectX::SimpleMath::Vector2 m_stringpos;
	//スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	//スプライトフォント
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;
	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_state;
};