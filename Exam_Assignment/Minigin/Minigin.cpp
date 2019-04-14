#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "StartScene.h"


#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(push)

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	SceneManager::GetInstance().AddScene(std::make_shared<StartScene>());

	SceneManager::GetInstance().Initialize();
	//auto go = std::make_shared<GameObject>();
	//TextureComponent* texture = new TextureComponent{ "background.jpg" };
	//go->AddComponent(texture);
	//scene.Add(go);

	//go = std::make_shared<GameObject>();
	//TextureComponent* texture1 = new TextureComponent{ "logo.png" };
	//go->AddComponent(texture1);
	//go->GetTransform()->SetPosition(216, 180, 0);
	//scene.Add(go);
	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//go = std::make_shared<GameObject>();
	//SpriteComponent* texture2 = new SpriteComponent{ "CharacterSpriteSheet.png",112,112 };
	//texture2->SetSpriteInfo(7, 7, 0, 5, 6, 3);
	//go->AddComponent(texture2);
	//go->GetTransform()->SetPosition(30, 240, 0);
	//scene.Add(go);

	//go = std::make_shared<GameObject>();
	//TextComponent* text = new TextComponent{ "Programming 4 Assignment", font, glm::vec3{255,255,255} };
	//go->AddComponent(text);
	//go->GetTransform()->SetPosition(80, 20, 0);
	//scene.Add(go);
	// 
	//font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	//go = std::make_shared<GameObject>();
	//FPSComponent* comp = new FPSComponent{ font, glm::vec3{255,255,0} };
	//go->AddComponent(comp);
	//go->GetTransform()->SetPosition(0, 0, 0);
	//scene.Add(go);

}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();

		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		while (doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			doContinue = input.ProcessInput();

			sceneManager.Update(deltaTime);
			renderer.Render();

			lastTime = currentTime;
		}
	}

	Cleanup();
}
