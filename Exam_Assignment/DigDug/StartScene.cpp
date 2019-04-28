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

dae::StartScene::StartScene()
	:Scene("StartScene")
{
	m_ButtonManager = std::make_shared<ButtonManager>();
	m_ButtonSolo = std::make_shared<GameObject>();
	m_ButtonCoop = std::make_shared<GameObject>();
	m_ButtonVersus = std::make_shared<GameObject>();
}

void dae::StartScene::Initialize() {

std::shared_ptr<ButtonActivateCommand> buttonDown = std::make_shared<ButtonActivateCommand>();
Locator::GetPlayerOneInput()->SetCommandToButton(buttonDown, ControllerButton::ButtonA);

auto go = std::make_shared<GameObject>();
TextureComponent* texture = new TextureComponent{ "Level.png" };
go->AddComponent(texture);
Add(go);

auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
ButtonComponent* button = new ButtonComponent("Solo", font, Vector3{ 0.0f,0.0f,0.0f }, []() {SceneManager::GetInstance().NextScene(); }, Vector3{ 100.0f,100.0f,0 });
m_ButtonSolo->AddComponent(button);
m_ButtonManager->AddButton(m_ButtonSolo);
Add(m_ButtonSolo);

ButtonComponent* button1 = new ButtonComponent("Co-op", font, Vector3{ 0.0f,0.0f,0.0f }, []() {SceneManager::GetInstance().PreviousScene(); }, Vector3{ 100.0f,300.0f,0 });
m_ButtonCoop->AddComponent(button1);
m_ButtonManager->AddButton(m_ButtonCoop);
Add(m_ButtonCoop);
}

void dae::StartScene::Update(float) {
	auto& input = Locator::GetPlayerOneInput();
	auto activeButton = m_ButtonManager->GetActiveButton();
	if(input->HandleInput() != nullptr) {
		input->HandleInput()->Execute(activeButton);
	}
	if(input->IsPressed(ControllerButton::ButtonDown)) {
		m_ButtonManager->PreviousButton();
	}
	else if(input->IsPressed(ControllerButton::ButtonUp)){
		m_ButtonManager->NextButton();
	}
}

void dae::StartScene::Render() {
}
