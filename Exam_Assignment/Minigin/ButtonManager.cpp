#include "MiniginPCH.h"
#include "ButtonManager.h"
#include "ButtonComponent.h"
#include "Locator.h"

void dae::ButtonManager::AddButton(const std::shared_ptr<GameObject>& button)
{
	m_pButtons.push_back(button);
	m_pActiveButton = m_pButtons[0];
	m_pActiveButton->GetComponent<ButtonComponent>()->Focus();
	m_ElapsedSec = 0.0f;
}

void dae::ButtonManager::NextButton() {
	for (unsigned int i = 0; i < m_pButtons.size(); ++i)
	{
		if (m_pButtons[i] == m_pActiveButton)
		{
			auto nextButton = ++i % m_pButtons.size();
			m_pActiveButton = m_pButtons[nextButton];
			m_pActiveButton->GetComponent<ButtonComponent>()->Focus();
			break;
		}
	}
	for(unsigned int i = 0; i < m_pButtons.size(); ++i) {
		if(m_pButtons[i] != m_pActiveButton) {
			m_pButtons[i]->GetComponent<ButtonComponent>()->Unfocus();
		}
	}
}

void dae::ButtonManager::PreviousButton() {
	for (unsigned int i = 0; i < m_pButtons.size(); ++i)
	{
		if (m_pButtons[i] == m_pActiveButton)
		{
			if(i == m_pButtons.size() - 1) {
				i = 0;
			}
			else {
				i += 1;
			}
			m_pActiveButton = m_pButtons[i];
			m_pActiveButton->GetComponent<ButtonComponent>()->Focus();
			break;
		}
	}
	for (unsigned int i = 0; i < m_pButtons.size(); ++i) {
		if (m_pButtons[i] != m_pActiveButton) {
			m_pButtons[i]->GetComponent<ButtonComponent>()->Unfocus();
		}
	}
}

void dae::ButtonManager::Update(float deltaTime) {
	m_ElapsedSec += deltaTime;
	if (m_ElapsedSec >= 0.2f)
	{
		auto& input = InputManager::GetInstance();
		if (input.IsActionTriggered(0)) {
			PreviousButton();
		}
		else if (input.IsActionTriggered(1)) {
			NextButton();
		}
		m_ElapsedSec = 0.0f;
	}
}

std::shared_ptr<dae::GameObject> dae::ButtonManager::GetActiveButton() {
	return m_pActiveButton;
}
