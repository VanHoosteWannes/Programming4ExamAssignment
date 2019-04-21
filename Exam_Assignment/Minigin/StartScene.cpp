#include "MiniginPCH.h"
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
#include "RockComponent.h"

dae::StartScene::StartScene()
	:Scene("StartScene")
{
	m_Obj = std::make_shared<GameObject>();
	m_Level = std::make_shared<GameObject>();
}

void dae::StartScene::Initialize() {

auto go = std::make_shared<GameObject>();
TextureComponent* texture = new TextureComponent{ "Level.png" };
go->AddComponent(texture);
Add(go);


MapComponent* map = new MapComponent{ 15, 14};
m_Level->AddComponent(map);
Add(m_Level);
//go = std::make_shared<GameObject>();
//TextureComponent* texture1 = new TextureComponent{ "logo.png" };
//go->AddComponent(texture1);
//go->GetTransform()->SetPosition(216, 180, 0);
//Add(go);
auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

//SpriteComponent* texture2 = new SpriteComponent{ "CharacterSpriteSheet.png",112,112 };
MovementComponent* movement = new MovementComponent{ 0.1f,448, 574 };
//texture2->SetSpriteInfo(7, 7, 0, 2, 0, 2);
//m_Obj->AddComponent(texture2);
m_Obj->AddComponent(movement);
m_Obj->GetTransform()->SetPosition(45, 48, 0);
Add(m_Obj);

map->AddDigger(m_Obj);
//map->AddTunnel(2, 2, 4, true);
//map->AddTunnel(5, 6, 3, false);
//go = std::make_shared<GameObject>();
//TextComponent* text = new TextComponent{ "Programming 4 Assignment", font, glm::vec3{255,255,255} };
//go->AddComponent(text);
//go->GetTransform()->SetPosition(80, 20, 0);
//Add(go);
 
font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
go = std::make_shared<GameObject>();
FPSComponent* comp = new FPSComponent{ font, Vector3{255,255,0} };
go->AddComponent(comp);
go->GetTransform()->SetPosition(0, 0, 0);
Add(go);

}

void dae::StartScene::Update(float) {
	auto& input = InputManager::GetInstance();
	if(input.HandleInput() != nullptr) {
		input.HandleInput()->Execute(m_Obj);
	}
}

void dae::StartScene::Render() {
	
}