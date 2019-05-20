#include "pch.h"
#include "VersusScene.h"
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
#include "DigDugMapComponent.h"
#include "InputCommands.h"
#include "DigDugHealthComponent.h"
#include "PointsManager.h"
#include "DigDugInflateComponent.h"
#include "DigDugGhostComponent.h"

dae::VersusScene::VersusScene()
	:Scene("VersusScene") {
	m_Obj = std::make_shared<GameObject>();
	m_Obj2 = std::make_shared<GameObject>();
	m_Level = std::make_shared<GameObject>();
	m_Score = std::make_shared<GameObject>();
}

void dae::VersusScene::Initialize() {

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

	input.AddInputAction(InputAction{ 4,KeyState::Released, VK_SPACE, XINPUT_GAMEPAD_A, GamepadIndex::PlayerOne });
	std::shared_ptr<ShootCommand> shoot = std::make_shared<ShootCommand>();
	input.SetCommand(4, shoot);

	input.AddInputAction(InputAction{ 5,KeyState::Down, VK_LEFT, XINPUT_GAMEPAD_DPAD_LEFT, GamepadIndex::PlayerTwo });
	left = std::make_shared<MoveLeftCommand>();
	input.SetCommand(5, left);

	input.AddInputAction(InputAction{ 6,KeyState::Down, VK_RIGHT, XINPUT_GAMEPAD_DPAD_RIGHT, GamepadIndex::PlayerTwo });
	right = std::make_shared<MoveRightCommand>();
	input.SetCommand(6, right);

	input.AddInputAction(InputAction{ 7,KeyState::Down, VK_UP, XINPUT_GAMEPAD_DPAD_UP, GamepadIndex::PlayerTwo });
	up = std::make_shared<MoveUpCommand>();
	input.SetCommand(7, up);

	input.AddInputAction(InputAction{ 8,KeyState::Down, VK_DOWN, XINPUT_GAMEPAD_DPAD_DOWN, GamepadIndex::PlayerTwo });
	down = std::make_shared<MoveDownCommand>();
	input.SetCommand(8, down);

	input.AddInputAction(InputAction{ 9,KeyState::Released, VK_SHIFT, XINPUT_GAMEPAD_A, GamepadIndex::PlayerTwo });
	shoot = std::make_shared<ShootCommand>();
	input.SetCommand(9, shoot);

	auto go = std::make_shared<GameObject>();
	TextureComponent* texture = new TextureComponent{ "Level.png" };
	go->AddComponent(texture);
	Add(go);


	DigDugMapComponent* map = new DigDugMapComponent{15, 14,32, 0,64,16 };
	m_Level->AddComponent(map);
	Add(m_Level);


	MovementComponent* movement = new MovementComponent{ 2.0f,0,64,448, 542,16,32,"CharacterSpriteSheet.png" };

	MovementComponent* movement2 = new MovementComponent{ 2.0f,0,64,448, 542, 16,32,"FygarSpriteSheet.png" };
	DigDugHealthComponent* health = new DigDugHealthComponent{ 3, Vector3{10,544,0}, "LifeP1.png", Vector3{48,48,0} };

	DigDugHealthComponent* health2 = new DigDugHealthComponent{ 3, Vector3{320,544,0}, "LifeFygar.png",Vector3{368,48,0} };

	DigDugWeaponComponent* weapon = new DigDugWeaponComponent{ "Weapon.png",true };
	weapon->AllowCollisionWithTag("Enemy");

	DigDugWeaponComponent* weapon2 = new DigDugWeaponComponent{ "Fire.png",false };
	weapon2->AllowCollisionWithTag("Player");

	CollisionComponent* collision = new CollisionComponent{ 30,30, "Player",16 };
	//collision->AllowCollisionWithTag("Enemy");
	collision->AllowCollisionWithTag("Rock");
	collision->AllowCollisionWithTag("Fire");

	CollisionComponent* enemyCollision = new CollisionComponent{ 30,30, "Enemy",16 };
	//enemyCollision->AllowCollisionWithTag("Player");
	enemyCollision->AllowCollisionWithTag("Rock");
	enemyCollision->AllowCollisionWithTag("Weapon");

	DigDugInflateComponent* inflateComp = new DigDugInflateComponent{};
	DigDugGhostComponent* ghostComp = new DigDugGhostComponent{ 32,14 };

	m_Obj->AddComponent(movement);
	m_Obj->AddComponent(health);
	m_Obj->AddComponent(weapon);
	m_Obj->AddComponent(collision);
	m_Obj->GetTransform()->SetPosition(48, 48, 0);
	Add(m_Obj);

	m_Obj2->AddComponent(movement2);
	m_Obj2->AddComponent(health2);
	m_Obj2->AddComponent(ghostComp);
	m_Obj2->AddComponent(inflateComp);
	m_Obj2->AddComponent(weapon2);
	m_Obj2->AddComponent(enemyCollision);
	m_Obj2->GetTransform()->SetPosition(368, 48, 0);
	Add(m_Obj2);
	
	map->AddDigger(m_Obj);


	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	go = std::make_shared<GameObject>();
	FPSComponent* comp = new FPSComponent{ font, Vector3{255,255,0} };
	go->AddComponent(comp);
	go->GetTransform()->SetPosition(0, 0, 0);
	Add(go);

	TextComponent* score = new TextComponent{ "Score: 0", font, Vector3{1.0f,1.0f,1.0f} };
	m_Score->AddComponent(score);
	Add(m_Score);
	m_Score->GetTransform()->Translate(200, 0, 0);
}

void dae::VersusScene::Update(float) {
	m_Score->GetComponent<TextComponent>()->SetText("Score: " + std::to_string(PointsManager::GetInstance().GetPoints()));

	auto& input = InputManager::GetInstance();

	if (input.IsActionTriggered(4)) {
		input.GetCommand(4)->Execute(m_Obj);
	}
	if (input.IsActionTriggered(0)) {
		input.GetCommand(0)->Execute(m_Obj);
	}
	else if (input.IsActionTriggered(1)) {
		input.GetCommand(1)->Execute(m_Obj);
	}
	else if (input.IsActionTriggered(2)) {
		input.GetCommand(2)->Execute(m_Obj);
	}
	else if (input.IsActionTriggered(3)) {
		input.GetCommand(3)->Execute(m_Obj);
	}

	if (input.IsActionTriggered(9)) {
		input.GetCommand(9)->Execute(m_Obj2);
	}

	if (input.IsActionTriggered(5)) {
		input.GetCommand(5)->Execute(m_Obj2);
	}
	else if (input.IsActionTriggered(6)) {
		input.GetCommand(6)->Execute(m_Obj2);
	}
	else if (input.IsActionTriggered(7)) {
		input.GetCommand(7)->Execute(m_Obj2);
	}
	else if (input.IsActionTriggered(8)) {
		input.GetCommand(8)->Execute(m_Obj2);
	}
}

void dae::VersusScene::Render() {

}
