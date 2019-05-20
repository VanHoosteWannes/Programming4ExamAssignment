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
#include "DigDugMapComponent.h"
#include "InputCommands.h"
#include "DigDugHealthComponent.h"
#include "DigDugWeaponComponent.h"
#include "CollisionComponent.h"
#include "PointsManager.h"
#include "AIComponent.h"
#include "EnemySpawner.h"

dae::SoloScene::SoloScene()
	:Scene("SoloScene") {
	m_Obj = std::make_shared<GameObject>();
	m_Level = std::make_shared<GameObject>();
	m_Score = std::make_shared<GameObject>();
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


	input.AddInputAction(InputAction{ 4,KeyState::Released, VK_SPACE, XINPUT_GAMEPAD_A, GamepadIndex::PlayerOne });
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


	MovementComponent* movement = new MovementComponent{ 2.0f,0,64,448, 542,16,32, "CharacterSpriteSheet.png"};
	DigDugHealthComponent* health = new DigDugHealthComponent{ 3, Vector3{10,544,0}, "LifeP1.png", Vector3{48,48} };
	DigDugWeaponComponent* weapon = new DigDugWeaponComponent{ "Weapon.png",true };
	weapon->AllowCollisionWithTag("Enemy");
	CollisionComponent* collision = new CollisionComponent{ 30,30, "Player",16 };
	collision->AllowCollisionWithTag("Enemy");
	collision->AllowCollisionWithTag("Rock");

	m_Obj->AddComponent(movement);
	m_Obj->AddComponent(health);
	m_Obj->AddComponent(weapon);
	m_Obj->AddComponent(collision);
	m_Obj->GetTransform()->SetPosition(48, 48, 0);
	Add(m_Obj);

	map->AddDigger(m_Obj);

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	go = std::make_shared<GameObject>();
	FPSComponent* comp = new FPSComponent{ font, Vector3{255,255,0} };
	go->AddComponent(comp);
	go->GetTransform()->SetPosition(0, 0, 0);
	Add(go);

	Add(EnemySpawner::SpawnEnemy("FygarSpriteSheet.png", Vector3{ 48,368,0 }));
	Add(EnemySpawner::SpawnEnemy("FygarSpriteSheet.png", Vector3{ 368,48,0 }));
	Add(EnemySpawner::SpawnEnemy("PookaSpriteSheet.png", Vector3{ 304,304,0 }));
	Add(EnemySpawner::SpawnEnemy("PookaSpriteSheet.png", Vector3{ 368,368,0 }));

	TextComponent* score = new TextComponent{ "Score: 0", font, Vector3{1.0f,1.0f,1.0f} };
	m_Score->AddComponent(score);
	Add(m_Score);
	m_Score->GetTransform()->SetPosition(200, 0, 0);
}

void dae::SoloScene::Update(float) {
	auto& input = InputManager::GetInstance();
	m_Score->GetComponent<TextComponent>()->SetText("Score: " + std::to_string(PointsManager::GetInstance().GetPoints()));

	//can't use for loop because that creates issue with my movement
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

	int i{ 0 };
	for(auto elements: Locator::GetEnemies()) {
		if(elements->GetComponent<AIComponent>()->IsDead()) {
			++i;
		}
	}
	if(i == int(Locator::GetEnemies().size())) {
		AIComponent::ResetCount();
		Locator::FlushEnemies();
		SceneManager::GetInstance().SetActivateScene("EndScene");
	}
}

void dae::SoloScene::Render() {

}