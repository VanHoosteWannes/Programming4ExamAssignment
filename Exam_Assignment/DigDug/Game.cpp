#include "pch.h"
#include "Game.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "StartScene.h"
#include "SoloScene.h"
#include "Locator.h"
#include "CoopScene.h"
#include <stdexcept>

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(push)

void dae::Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		448,
		576,
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
void dae::Game::LoadGame() const
{
	std::shared_ptr<Input> m_Player1 = std::make_shared<Input>();
	Locator::ProvidePlayerOneInput(m_Player1);

	SceneManager::GetInstance().AddScene(std::make_shared<StartScene>());
	SceneManager::GetInstance().AddScene(std::make_shared<SoloScene>());
	SceneManager::GetInstance().AddScene(std::make_shared<CoopScene>());

	SceneManager::GetInstance().Initialize();

}

void dae::Game::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Game::Run()
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
		auto& input1 = Locator::GetPlayerOneInput();
		auto& input2 = Locator::GetPlayerTwoInput();
		//auto& input = InputManager::GetInstance();

		while (doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			//doContinue = input.ProcessInput();
			if (input1 != nullptr) {
				doContinue = input1->ProcessInput(0);
			}
			if (input2 != nullptr) {
				input2->ProcessInput(1);
			}

			sceneManager.Update(deltaTime);
			renderer.Render();

			lastTime = currentTime;
		}
	}

	Cleanup();
}