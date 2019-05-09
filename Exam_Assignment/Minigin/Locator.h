#pragma once
#include "InputManager.h"

namespace dae {
	class Locator //class based off Week7 locator
	{
	public:
		static void Initialize() { m_Player1 = m_NullGameObject; m_Player2 = m_NullGameObject; }

		static std::shared_ptr<GameObject>& GetPlayerOne() { return m_Player1; }
		static std::shared_ptr<GameObject>& GetPlayerTwo() { return m_Player2; }

		static void ProvidePlayerOne(std::shared_ptr<GameObject> service)
		{
			if (service == nullptr)
			{
				m_Player1 = m_NullGameObject;
			}
			else
			{
				m_Player1 = service;
			}
		}
		static void ProvidePlayerTwo(std::shared_ptr<GameObject> service)
		{
			if (service == nullptr)
			{
				m_Player2 = m_NullGameObject;
			}
			else
			{
				m_Player2 = service;
			}
		}

	private:
		static std::shared_ptr<GameObject> m_Player1;
		static std::shared_ptr<GameObject> m_Player2;
		static std::shared_ptr<GameObject> m_NullGameObject;
	};
}

