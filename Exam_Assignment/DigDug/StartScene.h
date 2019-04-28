#pragma once
#include "Scene.h"
#include "GameObject.h"

namespace dae {
	class ButtonManager;
	class StartScene final:public Scene
	{
	public:
		StartScene();
		~StartScene() = default;

		StartScene(const StartScene& other) = delete;
		StartScene(StartScene&& other) noexcept = delete;
		StartScene& operator=(const StartScene& other) = delete;
		StartScene& operator=(StartScene&& other) noexcept = delete;
		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;
	private:
		std::shared_ptr<GameObject> m_ButtonSolo;
		std::shared_ptr<GameObject> m_ButtonCoop;
		std::shared_ptr<GameObject> m_ButtonVersus;
		std::shared_ptr<ButtonManager> m_ButtonManager;
	};
}

