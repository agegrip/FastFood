
#include "Game\Scene\ResultScene.h"

#include "Game\Scene\SceneManager.h"
#include "Game\Common\GameContext.h"

ResultScene::ResultScene()
{
	m_deviceResources = std::make_unique<DX::DeviceResources>();
}

ResultScene::~ResultScene()
{
	
}

void ResultScene::Initialize()
{

	// デバイスリソース作成
	DirectX::CommonStates* state = GameContext<DirectX::CommonStates>().Get();
	DX::DeviceResources*  deviceResources = GameContext<DX::DeviceResources>().Get();
	ID3D11Device*         device = deviceResources->GetD3DDevice();
	ID3D11DeviceContext*  deviceContext = deviceResources->GetD3DDeviceContext();
	//ステート作成
	m_state = std::make_unique<DirectX::CommonStates>(device);

	//スプライト作成
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(deviceContext);
	//フォント作成
	m_spriteFont = std::make_unique <DirectX::SpriteFont>(device, L"Resources\\Fonts\\SegoeUI_18.spritefont");
}

void ResultScene::Update(float elapsedTime)
{
	DirectX::Keyboard::State keystate = GameContext<DirectX::Keyboard>::Get()->GetState();
	if (keystate.R)
	{
		SceneManager* scene = GameContext<SceneManager>().Get();
		scene->ChangeState(SceneManager::TITLE);
	}
}

void ResultScene::Render()
{
	wchar_t text[50];
	swprintf(text, L"ResultScene\nPresing R Key", m_pos.x, m_pos.y);
	m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, m_state->NonPremultiplied());
	m_spriteFont->DrawString(m_spriteBatch.get(), text, DirectX::SimpleMath::Vector2(0, 0));
	m_spriteBatch->End();
}

void ResultScene::Finalize()
{

}