#include "pch.h"
#include "StartScene.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "MapComponent.h"
#include "Command.h"
#include "Locator.h"
#include "ButtonManager.h"
#include "SceneManager.h"
#include "ButtonComponent.h"
#include "InputCommands.h"

dae::StartScene::StartScene()
	:Scene("StartScene")
,m_Song(std::make_unique<SoundEffect>("../Data/Sounds/Death_screen.ogg"))
{
	m_ButtonManager = std::make_shared<ButtonManager>();
	m_ButtonSolo = std::make_shared<GameObject>();
	m_ButtonCoop = std::make_shared<GameObject>();
	m_ButtonVersus = std::make_shared<GameObject>();

	m_Song->SetVolume(10);
	m_Song->Play(true);
}

void dae::StartScene::Initialize() {

//std::shared_ptr<ButtonActivateCommand> buttonDown = std::make_shared<ButtonActivateCommand>();
//Locator::GetPlayerOneInput()->SetCommandToButton(buttonDown, ControllerButton::ButtonA);

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
ButtonComponent* button = new ButtonComponent("Solo", font, Vector3{ 0.0f,0.0f,0.0f }, []() {SceneManager::GetInstance().SetActivateScene("SoloScene");}, Vector3{ 180.0f,144.0f,0 });
m_ButtonSolo->AddComponent(button);
m_ButtonManager->AddButton(m_ButtonSolo);
Add(m_ButtonSolo);

ButtonComponent* button1 = new ButtonComponent("Co-op", font, Vector3{ 0.0f,0.0f,0.0f }, []() {SceneManager::GetInstance().SetActivateScene("CoopScene");}, Vector3{ 180.0f,288.0f,0 });
m_ButtonCoop->AddComponent(button1);
m_ButtonManager->AddButton(m_ButtonCoop);
Add(m_ButtonCoop);

ButtonComponent* button2 = new ButtonComponent("Versus", font, Vector3{ 0.0f,0.0f,0.0f }, []() {SceneManager::GetInstance().SetActivateScene("VersusScene");}, Vector3{ 180.0f,432.0f,0 });
m_ButtonVersus->AddComponent(button2);
m_ButtonManager->AddButton(m_ButtonVersus);
Add(m_ButtonVersus);

}

void dae::StartScene::Update(float deltaTime) {
	auto& input = InputManager::GetInstance();
	auto activeButton = m_ButtonManager->GetActiveButton();
	if(input.IsActionTriggered(2)) {
		input.GetCommand(2)->Execute(activeButton);
	}
	m_ButtonManager->Update(deltaTime);
}

void dae::StartScene::Render() {
}
