#include "pch.h"
#include "DigDugWeaponComponent.h"
#include "MovementComponent.h"
#include "TransformComponent.h"

dae::DigDugWeaponComponent::DigDugWeaponComponent(const std::string& filePath)
{
	for(int i{}; i < 4; ++i) {
		m_WeaponTextures.push_back(std::make_shared<TextureComponent>(filePath, 64.0f, 64.0f, SDL_Rect{i * 64,0,64,64}));
	}
}

void dae::DigDugWeaponComponent::Update(float deltaTime) {
	if (m_Active)
	{
		m_AccuSet += deltaTime;
		if (m_AccuSet > m_FrameTime)
		{
			m_Active = false;

			m_AccuSet = 0;
		}
	}
}

void dae::DigDugWeaponComponent::Render() {
	if (m_Active)
	{
		if (m_pGameObject->HasComponent<MovementComponent>()) {
			Vector3 pos{};
			int movementID = int(m_pGameObject->GetComponent<MovementComponent>()->GetDirection());
			if (movementID == 0)
			{
				pos = Vector3{ m_pGameObject->GetTransform()->GetPosition().x - 64, m_pGameObject->GetTransform()->GetPosition().y - 32, m_pGameObject->GetTransform()->GetPosition().z };
			}
			else if (movementID == 1) {
				pos = Vector3{ m_pGameObject->GetTransform()->GetPosition().x, m_pGameObject->GetTransform()->GetPosition().y - 32, m_pGameObject->GetTransform()->GetPosition().z };
			}
			else if (movementID == 2) {
				pos = Vector3{ m_pGameObject->GetTransform()->GetPosition().x - 32, m_pGameObject->GetTransform()->GetPosition().y - 64, m_pGameObject->GetTransform()->GetPosition().z };
			}
			else {
				pos = Vector3{ m_pGameObject->GetTransform()->GetPosition().x - 32, m_pGameObject->GetTransform()->GetPosition().y, m_pGameObject->GetTransform()->GetPosition().z };
			}
			m_WeaponTextures[movementID]->Render(pos);
		}
	}
}

void dae::DigDugWeaponComponent::Activate() {
	m_Active = true;
}


