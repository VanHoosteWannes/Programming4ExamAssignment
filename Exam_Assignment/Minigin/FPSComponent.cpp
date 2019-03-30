#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"

dae::FPSComponent::FPSComponent(std::shared_ptr<Font> font, glm::vec3 color) {
	m_TextComp = new TextComponent{ "FPS:", font, color };
}

void dae::FPSComponent::Initialize() {}

void dae::FPSComponent::Update(float deltaTime) {
	m_FpsUpdateDelay -= deltaTime;
	if (m_FpsUpdateDelay <= 0)
	{
		m_Text = "FPS: " + std::to_string(int(1.0f / deltaTime));
		m_TextComp->setText(m_Text);
		m_FpsUpdateDelay = 1.0f;
		m_TextComp->Update(deltaTime);
	}
}

void dae::FPSComponent::Render() {
	m_TextComp->Render(GetGameObject()->GetTransform()->GetPosition());
}
