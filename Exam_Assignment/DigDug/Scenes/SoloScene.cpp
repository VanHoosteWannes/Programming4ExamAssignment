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
#include "../InputCommands.h"
#include "../DigDugHealthComponent.h"
#include "../DigDugWeaponComponent.h"

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


	input.AddInputAction(InputAction{ 4,KeyState::Down, VK_SPACE, XINPUT_GAMEPAD_A, GamepadIndex::PlayerOne });
	std::shared_ptr<ShootCommand> shoot = std::make_shared<ShootCommand>();
	input.SetCommand(4, shoot);


	//std::shared_ptr<Input> m_Player2 = std::make_shared<Input>();
	//Locator::ProvidePlayerTwoInput(m_Player2);

	auto go = std::make_shared<GameObject>();
	TextureComponent* texture = new TextureComponent{ "Level.png" };
	go->AddComponent(texture);
	Add(go);


	DigDugMapComponent* map = new DigDugMapComponent{ 15,14,32,0,64,16 };
	m_Level->AddComponent(map);
	Add(m_Level);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);


	MovementComponent* movement = new MovementComponent{ 0.1f,0,64,448, 542,16,32 };
	DigDugHealthComponent* health = new DigDugHealthComponent{ 3, Vector3{10,544,0}, "LifeP1.png" };
	DigDugWeaponComponent* weapon = new DigDugWeaponComponent{ "Weapon.png" };

	m_Obj->AddComponent(movement);
	m_Obj->AddComponent(health);
	m_Obj->AddComponent(weapon);
	m_Obj->GetTransform()->SetPosition(48, 48, 0);
	Add(m_Obj);

	map->AddDigger(m_Obj);

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	go = std::make_shared<GameObject>();
	FPSComponent* comp = new FPSComponent{ font, Vector3{255,255,0} };
	go->AddComponent(comp);
	go->GetTransform()->SetPosition(0, 0, 0);
	Add(go);

}

void dae::SoloScene::Update(float) {
	auto& input = InputManager::GetInstance();

	for (int i{}; i < 5; ++i)
	{
		if (input.IsActionTriggered(i)) {
			input.GetCommand(i)->Execute(m_Obj);
		}
	}
}

void dae::SoloScene::Render() {

}