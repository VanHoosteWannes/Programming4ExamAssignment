#include "pch.h"
#include "SoloScene.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "TransformComponent.h"
#include "InputManager.h"
#include "MapComponent.h"
#include "Locator.h"
#include "../DigDugMapComponent.h"

dae::SoloScene::SoloScene()
	:Scene("SoloScene") {
	m_Obj = std::make_shared<GameObject>();
	m_Level = std::make_shared<GameObject>();
}

void dae::SoloScene::Initialize() {

	auto& input = InputManager::GetInstance();

	input.AddInputAction(InputAction{ 0,KeyState::Down, 'A', XINPUT_GAMEPAD_DPAD_LEFT, GamepadIndex::PlayerOne });
	std::shared_ptr<MoveLeftCommand> left = std::make_shared<MoveLeftCommand>();
	input.SetCommand(0, left);

	input.AddInputAction(InputAction{ 1,KeyState::Down, 'D', XINPUT_GAMEPAD_DPAD_RIGHT, GamepadIndex::PlayerOne });
	std::shared_ptr<MoveRightCommand> right = std::make_shared<MoveRightCommand>();
	input.SetCommand(1, right);

	input.AddInputAction(InputAction{ 2,KeyState::Down, 'W', XINPUT_GAMEPAD_DPAD_UP, GamepadIndex::PlayerOne });
	std::shared_ptr<MoveUpCommand> up = std::make_shared<MoveUpCommand>();
	input.SetCommand(2, up);

	input.AddInputAction(InputAction{ 3,KeyState::Down, 'S', XINPUT_GAMEPAD_DPAD_DOWN, GamepadIndex::PlayerOne });
	std::shared_ptr<MoveDownCommand> down = std::make_shared<MoveDownCommand>();
	input.SetCommand(3, down);


	//std::shared_ptr<Input> m_Player2 = std::make_shared<Input>();
	//Locator::ProvidePlayerTwoInput(m_Player2);

	auto go = std::make_shared<GameObject>();
	TextureComponent* texture = new TextureComponent{ "Level.png" };
	go->AddComponent(texture);
	Add(go);


	//MapComponent* map = new MapComponent{ 15, 14,32, 0,64,16 };
	DigDugMapComponent* map = new DigDugMapComponent{ 15,14,32,0,64,16 };
	m_Level->AddComponent(map);
	Add(m_Level);
	//go = std::make_shared<GameObject>();
	//TextureComponent* texture1 = new TextureComponent{ "logo.png" };
	//go->AddComponent(texture1);
	//go->GetTransform()->SetPosition(216, 180, 0);
	//Add(go);
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//SpriteComponent* texture2 = new SpriteComponent{ "CharacterSpriteSheet.png",112,112 };
	MovementComponent* movement = new MovementComponent{ 0.1f,0,64,448, 542,16,32 };
	//texture2->SetSpriteInfo(7, 7, 0, 2, 0, 2);
	//m_Obj->AddComponent(texture2);
	m_Obj->AddComponent(movement);
	m_Obj->GetTransform()->SetPosition(48, 48, 0);
	Add(m_Obj);

	map->AddDigger(m_Obj);
	/*go = std::make_shared<GameObject>();
	TextComponent* text = new TextComponent{ "Programming 4 Assignment", font, glm::vec3{255,255,255} };
	go->AddComponent(text);
	go->GetTransform()->SetPosition(80, 20, 0);
	Add(go)*/;

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	go = std::make_shared<GameObject>();
	FPSComponent* comp = new FPSComponent{ font, Vector3{255,255,0} };
	go->AddComponent(comp);
	go->GetTransform()->SetPosition(0, 0, 0);
	Add(go);

}

void dae::SoloScene::Update(float) {
	auto& input = InputManager::GetInstance();
	//auto& input = Locator::GetPlayerOneInput();
	//if (input->HandleInput() != nullptr) {
	//	input->HandleInput()->Execute(m_Obj);
	//}

	if (input.IsActionTriggered(0)) {
		input.GetCommand(0)->Execute(m_Obj);
	}
	if (input.IsActionTriggered(1)) {
		input.GetCommand(1)->Execute(m_Obj);
	}
	if (input.IsActionTriggered(2)) {
		input.GetCommand(2)->Execute(m_Obj);
	}
	if (input.IsActionTriggered(3)) {
		input.GetCommand(3)->Execute(m_Obj);
	}
}

void dae::SoloScene::Render() {

}