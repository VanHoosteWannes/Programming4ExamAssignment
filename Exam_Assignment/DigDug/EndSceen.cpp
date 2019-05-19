#include "pch.h"
#include "EndSceen.h"
#include "InputManager.h"
#include "InputCommands.h"
#include "ResourceManager.h"
#include <unordered_map>


dae::EndSceen::EndSceen()
	:Scene("EndScene")
{
	m_ButtonManager = std::make_shared<ButtonManager>();
	m_ButtonMenu = std::make_shared<GameObject>();
	m_ButtonQuit = std::make_shared<GameObject>();
	m_ButtonRestart = std::make_shared<GameObject>();
}

void dae::EndSceen::Initialize() {
	auto& input = InputManager::GetInstance();

	input.AddInputAction(InputAction{ 0,KeyState::Down, 'W', XINPUT_GAMEPAD_DPAD_UP, GamepadIndex::PlayerOne });

	input.AddInputAction(InputAction{ 1,KeyState::Down, 'S', XINPUT_GAMEPAD_DPAD_DOWN, GamepadIndex::PlayerOne });

	input.AddInputAction(InputAction{ 2,KeyState::Released, 'P', XINPUT_GAMEPAD_A, GamepadIndex::PlayerOne });
	std::shared_ptr<ButtonActivateCommand> press = std::make_shared<ButtonActivateCommand>();
	input.SetCommand(2, press);

	auto go = std::make_shared<GameObject>();
	TextureComponent* texture = new TextureComponent{ "Level.png" };
	go->AddComponent(texture);
	Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	ButtonComponent* button = new ButtonComponent("Restart", font, Vector3{ 0.0f,0.0f,0.0f }, []() {SceneManager::GetInstance().SetActivateScene(SceneManager::GetInstance().GetLastActiveScene()); }, Vector3{ 180.0f,144.0f,0 });
	m_ButtonRestart->AddComponent(button);
	m_ButtonManager->AddButton(m_ButtonRestart);
	Add(m_ButtonRestart);

	ButtonComponent* button1 = new ButtonComponent("Menu", font, Vector3{ 0.0f,0.0f,0.0f }, []() {SceneManager::GetInstance().SetActivateScene("StartScene"); }, Vector3{ 180.0f,288.0f,0 });
	m_ButtonMenu->AddComponent(button1);
	m_ButtonManager->AddButton(m_ButtonMenu);
	Add(m_ButtonMenu);

	ButtonComponent* button2 = new ButtonComponent("Quit", font, Vector3{ 0.0f,0.0f,0.0f }, []() { InputManager::GetInstance().QuitGame(); }, Vector3{ 180.0f,432.0f,0 });
	m_ButtonQuit->AddComponent(button2);
	m_ButtonManager->AddButton(m_ButtonQuit);
	Add(m_ButtonQuit);
}
void dae::EndSceen::Update(float deltaTime) {
	auto& input = InputManager::GetInstance();
	auto activeButton = m_ButtonManager->GetActiveButton();
	if (input.IsActionTriggered(2)) {
		input.GetCommand(2)->Execute(activeButton);
	}
	m_ButtonManager->Update(deltaTime);
}
void dae::EndSceen::Render() {}


