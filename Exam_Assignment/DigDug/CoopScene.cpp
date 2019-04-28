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

dae::CoopScene::CoopScene()
	:Scene("CoopScene") {
	m_Obj = std::make_shared<GameObject>();
	m_Obj2 = std::make_shared<GameObject>();
	m_Level = std::make_shared<GameObject>();
}

void dae::CoopScene::Initialize() {

	std::shared_ptr<Input> m_Player2 = std::make_shared<Input>();
	Locator::ProvidePlayerTwoInput(m_Player2);

	auto go = std::make_shared<GameObject>();
	TextureComponent* texture = new TextureComponent{ "Level.png" };
	go->AddComponent(texture);
	Add(go);


	MapComponent* map = new MapComponent{ 15, 14 };
	m_Level->AddComponent(map);
	Add(m_Level);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);


	MovementComponent* movement = new MovementComponent{ 0.1f,448, 574 };
	MovementComponent* movement2 = new MovementComponent{ 0.1f,448, 574 };

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
	//auto& input = InputManager::GetInstance();
	auto& input = Locator::GetPlayerOneInput();
	auto& input2 = Locator::GetPlayerTwoInput();
	if (input->HandleInput() != nullptr) {
		input->HandleInput()->Execute(m_Obj);
	}
	if (input2->HandleInput() != nullptr) {
		input2->HandleInput()->Execute(m_Obj2);
	}
}

void dae::CoopScene::Render() {

}