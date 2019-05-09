#include "MiniginPCH.h"
#include "HealthComponent.h"


dae::HealthComponent::HealthComponent(int lives)
	:m_Lives(lives)
{
}

void dae::HealthComponent::SetLives(int amountOfLives) {
	m_Lives = amountOfLives;
}

void dae::HealthComponent::RemoveLife() {
	--m_Lives;
}
void dae::HealthComponent::Update(float) {
}
void dae::HealthComponent::Render() {}
