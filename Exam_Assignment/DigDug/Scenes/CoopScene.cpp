#include "pch.h"
#include "CoopScene.h"
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

dae::CoopScene::CoopScene()
	:Scene("CoopScene") {
	m_Obj = std::make_shared<GameObject>();
	m_Obj2 = std::make_shared<GameObject>();
	m_Level = std::make_shared<GameObject>();
}

void dae::CoopScene::Initialize() {

	//std::shared_ptr<Input> m_Player2 = std::make_shared<Input>();
	//Locator::ProvidePlayerTwoInput(m_Player2);

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

	input.AddInputAction(InputAction{ 4,KeyState::Down, VK_LEFT, XINPUT_GAMEPAD_DPAD_LEFT, GamepadIndex::PlayerTwo });
	left = std::make_shared<MoveLeftCommand>();
	input.SetCommand(4, left);

	input.AddInputAction(InputAction{ 5,KeyState::Down, VK_RIGHT, XINPUT_GAMEPAD_DPAD_RIGHT, GamepadIndex::PlayerTwo });
	right = std::make_shared<MoveRightCommand>();
	input.SetCommand(5, right);

	input.AddInputAction(InputAction{ 6,KeyState::Down, VK_UP, XINPUT_GAMEPAD_DPAD_UP, GamepadIndex::PlayerTwo });
	up = std::make_shared<MoveUpCommand>();
	input.SetCommand(6, up);

	input.AddInputAction(InputAction{ 7,KeyState::Down, VK_DOWN, XINPUT_GAMEPAD_DPAD_DOWN, GamepadIndex::PlayerTwo });
	down = std::make_shared<MoveDownCommand>();
	input.SetCommand(7, down);

	auto go = std::make_shared<GameObject>();
	TextureComponent* texture = new TextureComponent{ "Level.png" };
	go->AddComponent(texture);
	Add(go);


	DigDugMapComponent* map = new DigDugMapComponent{ 15, 14,32, 0,64,16 };
	m_Level->AddComponent(map);
	Add(m_Level);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);


	MovementComponent* movement = new MovementComponent{ 0.1f,0,64,448, 542,16,32 };
	MovementComponent* movement2 = new MovementComponent{ 0.1f,0,64,448, 542, 16,32 };

	m_Obj->AddComponent(movement);
	m_Obj->GetTransform()->SetPosition(45, 48, 0);
	Add(m_Obj);

	m_Obj2->AddComponent(movement2);
	m_Obj2->GetTransform()->SetPosition(345, 48, 0);
	Add(m_Obj2);

	map->AddDigger(m_Obj);
	map->AddDigger(m_Obj2);


	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	go = std::make_shared<GameObject>();
	FPSComponent* comp = new FPSComponent{ font, Vector3{255,255,0} };
	go->AddComponent(comp);
	go->GetTransform()->SetPosition(0, 0, 0);
	Add(go);

}

void dae::CoopScene::Update(float) {
	auto& input = InputManager::GetInstance();

	if(input.IsActionTriggered(0)) {
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
	if (input.IsActionTriggered(4)) {
		input.GetCommand(4)->Execute(m_Obj2);
	}
	if (input.IsActionTriggered(5)) {
		input.GetCommand(5)->Execute(m_Obj2);
	}
	if (input.IsActionTriggered(6)) {
		input.GetCommand(6)->Execute(m_Obj2);
	}
	if (input.IsActionTriggered(7)) {
		input.GetCommand(7)->Execute(m_Obj2);
	}
}

void dae::CoopScene::Render() {

}