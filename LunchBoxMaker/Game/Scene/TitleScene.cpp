//
// TitleScene.cpp
//
#include "Game\Scene\TitleScene.h"

#include "Game\Scene\SceneManager.h"
#include "Game\Common\GameContext.h"

TitleScene::TitleScene()
{
	m_deviceResources = std::make_unique<DX::DeviceResources>();
}

TitleScene::~TitleScene()
{
	
}

void TitleScene::Initialize()
{

	// �f�o�C�X���\�[�X�쐬
	DirectX::CommonStates* state = GameContext<DirectX::CommonStates>().Get();
	DX::DeviceResources*  deviceResources = GameContext<DX::DeviceResources>().Get();
	ID3D11Device*         device = deviceResources->GetD3DDevice();
	ID3D11DeviceContext*  deviceContext = deviceResources->GetD3DDeviceContext();
	//�X�e�[�g�쐬
	m_state = std::make_unique<DirectX::CommonStates>(device);

	//�X�v���C�g�쐬
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(deviceContext);
	//�t�H���g�쐬
	m_spriteFont = std::make_unique <DirectX::SpriteFont>(device, L"Resources\\Fonts\\SegoeUI_18.spritefont");
}

void TitleScene::Update(float elapsedTime)
{
	DirectX::Keyboard::State keystate = GameContext<DirectX::Keyboard>::Get()->GetState();
	if (keystate.Z)
	{
		SceneManager* scene = GameContext<SceneManager>().Get();
		scene->ChangeState(SceneManager::PLAY);
	}
}

void TitleScene::Render()
{
	wchar_t text[50];
	swprintf(text, L"TitleScene\n Presing Z Key", m_pos.x, m_pos.y);
	m_spriteBatch->Begin(DirectX::SpriteSortMode_Deferred, m_state->NonPremultiplied());
	m_spriteFont->DrawString(m_spriteBatch.get(), text, DirectX::SimpleMath::Vector2(0, 0));
	m_spriteBatch->End();
}

void TitleScene::Finalize()
{

}