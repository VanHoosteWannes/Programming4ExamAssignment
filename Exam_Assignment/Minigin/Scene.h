#pragma once
#include "SceneManager.h"

namespace dae
{
	class SceneObject;
	class Scene
	{
	public:

		void Add(const std::shared_ptr<SceneObject>& object);

		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

		void RootInitialize();
		void RootUpdate(float deltaTime);
		void RootRender();

		Scene(const std::string& name);
		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;
	private: 

		//std::string m_Name{};
		std::vector < std::shared_ptr<SceneObject>> mObjects{};
	};

}
