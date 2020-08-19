//
// Player.cpp
//
#include "Player.h"
#include <memory>
#include "DirectXTK\Keyboard.h"
#include "Game\Common\DeviceResources.h"
#include "Game\Common\GameContext.h"
#include "Game\GameObject\GameObjectManager.h"
#include "Game\GameObject\Bullet.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Player::Player(const DirectX::SimpleMath::Vector3& position, float fireInterval)
	:GameObject("Player")
	, m_playerGeometric()
	, m_fireInterval(fireInterval)
	, m_elapsedTime(0.f)
	, m_horizontalAngle(-90.0f)
	, m_isLoading(false)
	, m_bulletName("Humberger")
	, m_counter(0)
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>::Get();
	ID3D11Device*		 device = deviceResources->GetD3DDevice();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();

	// ポジション
	m_position = position;
	// ジオメトリ
	m_playerGeometric = DirectX::GeometricPrimitive::CreateBox(deviceContext, DirectX::SimpleMath::Vector3(1.0f, 2.0f, 1.0f));
	//ステート作成
	m_state = std::make_unique<DirectX::CommonStates>(device);
	//スプライト作成
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(deviceContext);
	//フォント作成
	m_spriteFont = std::make_unique <DirectX::SpriteFont>(device, L"Resources\\Fonts\\SegoeUI_18.spritefont");
	
}

Player::~Player()
{
}

void Player::Update(float elapsedTime)
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	DirectX::Keyboard::KeyboardStateTracker keyStateTraker;
	DirectX::Mouse::State mouseState = DirectX::Mouse::Get().GetState();
	keyStateTraker.Update(keyState);
	if (m_counter <= 0)
	{
		if (keyStateTraker.pressed.A)
		{
			if (m_position.x != -3.0f)
			{
				m_position.x -= 3.0f;
				m_counter = 10;
			}
		}

		if (keyStateTraker.pressed.D)
		{
			if (m_position.x != 3.0f)
			{
				m_position.x += 3.0f;
				m_counter = 10;
			}
		}
	}
	else
	{
		m_counter--;
	}
}

void Player::Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_playerGeometric->Draw(world, viewMatrix, projectionMatrix);

	wchar_t text[50];
	std::wstring ws = std::wstring(m_bulletName.begin(), m_bulletName.end());
	swprintf(text, ws.c_str(), m_stringpos.x, m_stringpos.y);
	m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, m_state->NonPremultiplied());
	m_spriteFont->DrawString(m_spriteBatch.get(), text, DirectX::SimpleMath::Vector2(0, 0));
	m_spriteBatch->End();
}

void Player::Fire()
 {
	float rad = DirectX::XMConvertToRadians(m_horizontalAngle);
	DirectX::SimpleMath::Vector3 direction(cos(rad), 0.f, sin(rad));
	std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(m_position, direction,m_bulletName);
	GameContext<GameObjectManager>::Get()->Add(std::move(bullet));
	m_elapsedTime = 0.f;
	m_isLoading = true;
}