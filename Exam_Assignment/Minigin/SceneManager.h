#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		//scenemanager based on the overlord engine

		void AddScene(std::shared_ptr<Scene> pScene);
		void RemoveScene(std::shared_ptr<Scene> pScene);
		void NextScene();
		std::shared_ptr<Scene> GetActiveScene() const { return m_ActiveScene; }


		void Initialize();
		void Update(float deltaTime);
		void Render();

	private:
		std::vector<std::shared_ptr<Scene>> m_pScenes;
		std::shared_ptr<Scene> m_ActiveScene, m_NewActiveScene;
	};

}
