#include "pch.h"
#include "DigDugHealthComponent.h"
#include "TextureComponent.h"

dae::DigDugHealthComponent::DigDugHealthComponent(int lives, Vector3 startPos, const std::string& filePath)
:HealthComponent{lives}
,m_StartPos(startPos)
{
	for(int i{}; i < lives; ++i) {
		m_LifeTextures.push_back(std::make_shared<TextureComponent>(filePath));
	}
}

void dae::DigDugHealthComponent::Update(float) {

}

void dae::DigDugHealthComponent::Render() {
	for (int i{}; i < m_Lives; ++i) {
		m_LifeTextures[i]->Render(Vector3{ float(m_StartPos.x + (i * 40)),m_StartPos.y,m_StartPos.z });
	}
}
