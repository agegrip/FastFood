//
// Game.cpp
//


#include "Game.h"
#include "Common\GameContext.h"

extern void ExitGame();

using namespace DirectX;

using Microsoft::WRL::ComPtr;


const wchar_t* Game::WINDOW_TITLE  = L"FastFood";
const int      Game::WINDOW_WIDTH  = 1280;
const int      Game::WINDOW_HEIGHT = 720;


Game::Game() noexcept(false)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
	GameContext<DX::DeviceResources>::Register(m_deviceResources);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

	// CreateCommonState
	m_state = std::make_unique<CommonStates>(m_deviceResources->GetD3DDevice());
	GameContext<CommonStates>::Register(m_state);

	// �L�[�{�[�h�쐬
	m_pkeyboard = std::make_unique<DirectX::Keyboard>();
	GameContext<DirectX::Keyboard>::Register(m_pkeyboard);
	// �}�E�X�쐬
	m_pMouse = std::make_unique<DirectX::Mouse>();
	m_pMouse->SetWindow(window);
	GameContext<DirectX::Mouse>::Register(m_pMouse);

	// CreateSceneManager
	m_sceneManager = std::make_unique<SceneManager>();
	m_sceneManager->GetInstance();
	m_sceneManager->ChangeState(SceneManager::LOGO);
	GameContext<SceneManager>::Register(m_sceneManager);

	m_gameObjectManager = std::make_unique<GameObjectManager>();
	GameContext<GameObjectManager>::Register(m_gameObjectManager);
	m_collisionManager = std::make_unique<CollisionManager>();
	GameContext<CollisionManager>::Register(m_collisionManager);

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(const DX::StepTimer& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());
	std::unique_ptr<DX::StepTimer> stepTimer = std::make_unique<DX::StepTimer>(timer);
	GameContext<DX::StepTimer>::Register(stepTimer);
	m_sceneManager->Update(elapsedTime);

    // TODO: Add your game logic here.
    elapsedTime;
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
    context;

	m_sceneManager->Render();

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    auto r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width  = WINDOW_WIDTH;
    height = WINDOW_HEIGHT;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}

#pragma endregion