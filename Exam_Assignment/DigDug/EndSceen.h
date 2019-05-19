#pragma once
#include "Scene.h"
#include "ButtonManager.h"

namespace  dae {
	class EndSceen :
		public Scene
	{
	public:
		EndSceen();
		~EndSceen() = default;
		EndSceen(const EndSceen& other) = delete;
		EndSceen(EndSceen&& other) noexcept = delete;
		EndSceen& operator=(const EndSceen& other) = delete;
		EndSceen& operator=(EndSceen&& other) noexcept = delete;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;
	private:
		std::shared_ptr<GameObject> m_ButtonMenu;
		std::shared_ptr<GameObject> m_ButtonRestart;
		std::shared_ptr<GameObject> m_ButtonQuit;
		std::shared_ptr<ButtonManager> m_ButtonManager;
	};
}

