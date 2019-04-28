#pragma once
#include "Singleton.h"
#include "GameObject.h"

namespace dae {

	class ButtonManager final
	{
	public:
		ButtonManager() = default;
		void AddButton(const std::shared_ptr<GameObject>& button);
		void NextButton();
		void PreviousButton();
		//void Update();
		std::shared_ptr<GameObject> GetActiveButton();
	private:
		std::vector<std::shared_ptr<GameObject>> m_pButtons;
		std::shared_ptr<GameObject> m_pActiveButton;
	};
}

