#pragma once
#include "Scene.h"
#include "GameObject.h"


namespace dae {
	class VersusScene :
		public Scene
	{
	public:
		VersusScene();
		~VersusScene() = default;
		VersusScene(const VersusScene& other) = delete;
		VersusScene(VersusScene&& other) noexcept = delete;
		VersusScene& operator=(const VersusScene& other) = delete;
		VersusScene& operator=(VersusScene&& other) noexcept = delete;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;
	private:
		std::shared_ptr<GameObject> m_Obj;
		std::shared_ptr<GameObject> m_Obj2;
		std::shared_ptr<GameObject> m_Level;
		std::shared_ptr<GameObject> m_Score;
	};
}

