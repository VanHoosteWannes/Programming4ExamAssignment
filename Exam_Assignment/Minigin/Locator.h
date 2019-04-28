#pragma once
#include "InputManager.h"

namespace dae {
	class Locator //class based off Week7 locator
	{
	public:
		static void Initialize() { m_Input1 = m_NullInput; m_Input2 = m_NullInput; }

		static std::shared_ptr<InputBase>& GetPlayerOneInput() { return m_Input1; }
		static std::shared_ptr<InputBase>& GetPlayerTwoInput() { return m_Input2; }

		static void ProvidePlayerOneInput(std::shared_ptr<InputBase> service)
		{
			if (service == nullptr)
			{
				m_Input1 = m_NullInput;
			}
			else
			{
				m_Input1 = service;
			}
		}
		static void ProvidePlayerTwoInput(std::shared_ptr<InputBase> service)
		{
			if (service == nullptr)
			{
				m_Input2 = m_NullInput;
			}
			else
			{
				m_Input2 = service;
			}
		}

	private:
		static std::shared_ptr<InputBase> m_Input1;
		static std::shared_ptr<InputBase> m_Input2;
		static std::shared_ptr<NullInput> m_NullInput;
	};
}

