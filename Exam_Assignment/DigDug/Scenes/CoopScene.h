#pragma once
#include "Scene.h"
#include "GameObject.h"

namespace dae {
	class CoopScene :
		public Scene
	{
	public:
		CoopScene();
		~CoopScene() = default;
		CoopScene(const CoopScene& other) = delete;
		CoopScene(CoopScene&& other) noexcept = delete;
		CoopScene& operator=(const CoopScene& other) = delete;
		CoopScene& operator=(CoopScene&& other) noexcept = delete;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;
	private:
		std::shared_ptr<GameObject> m_Obj;
		std::shared_ptr<GameObject> m_Obj2;
		std::shared_ptr<GameObject> m_Level;
	};
}

