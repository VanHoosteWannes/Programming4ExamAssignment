#include "MiniginPCH.h"
#include "ButtonManager.h"
#include "ButtonComponent.h"

void dae::ButtonManager::AddButton(const std::shared_ptr<GameObject>& button) {
	m_pButtons.push_back(button);
	m_pActiveButton = m_pButtons[0];
}

void dae::ButtonManager::NextButton() {
	for (unsigned int i = 0; i < m_pButtons.size(); ++i)
	{
		if (m_pButtons[i] == m_pActiveButton)
		{
			auto nextButton = ++i % m_pButtons.size();
			m_pActiveButton = m_pButtons[nextButton];
			break;
		}
	}
}

void dae::ButtonManager::PreviousButton() {
	for (unsigned int i = 0; i < m_pButtons.size(); ++i)
	{
		if (m_pButtons[i] == m_pActiveButton)
		{
			if (i == 0)
			{
				i = unsigned int(m_pButtons.size() - 1);
			}
			m_pActiveButton = m_pButtons[i];
			break;
		}
	}
}

//void dae::ButtonManager::Update() {
//	for(int i{}; i < m_pButtons.size(); ++i) {
//		if(m_pButtons[i] == m_pActiveButton) {
//			m_pActiveButton->GetComponent<ButtonComponent>()->Focus();
//		}
//		else {
//			m_pActiveButton->GetComponent<ButtonComponent>()->Unfocus();
//		}
//	}
//}

std::shared_ptr<dae::GameObject> dae::ButtonManager::GetActiveButton() {
	return m_pActiveButton;
}
