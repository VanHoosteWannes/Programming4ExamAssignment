#include "pch.h"
#include "DigDugHealthComponent.h"
#include "TextureComponent.h"
#include "CollisionComponent.h"
#include "MovementComponent.h"
#include "TransformComponent.h"
#include "PointsManager.h"
#include "SceneManager.h"

dae::DigDugHealthComponent::DigDugHealthComponent(int lives, Vector3 startPos, const std::string& filePath, Vector3 respawnPoint)
	:HealthComponent{ lives }
	, m_StartPos(startPos)
	, m_DieTime(0.9f)
	, m_AccuSec(0.0f)
,m_RespawnPoint(respawnPoint)
{
	for(int i{}; i < lives; ++i) {
		m_LifeTextures.push_back(std::make_shared<TextureComponent>(filePath));
	}
}

void dae::DigDugHealthComponent::Update(float elapsedSec) {
	if (!m_IsDying)
	{
		if (m_pGameObject->GetComponent<CollisionComponent>()->GetColliding()) {
			RemoveLife();
			m_pGameObject->GetComponent<MovementComponent>()->LockMovement(true);
			m_pGameObject->GetComponent<MovementComponent>()->SetSpriteInfo(7, 7, 0, 5, 6, 2);

			if(m_pGameObject->GetComponent<CollisionComponent>()->GetLastCollidedTag() == "Rock" && m_pGameObject->GetComponent<CollisionComponent>()->GetTag() == "Enemy") {
				PointsManager::GetInstance().AddPoints(1000);
			}
			m_IsDying = true;
		}
	}
	if(m_IsDying) {
		m_AccuSec += elapsedSec;
		if(m_AccuSec >= m_DieTime) {
			m_pGameObject->GetTransform()->SetPosition(m_RespawnPoint.x, m_RespawnPoint.y, m_RespawnPoint.z);
			m_pGameObject->GetComponent<MovementComponent>()->SetSpriteInfo(7, 7, 0, 2, 0, 2);
			m_pGameObject->GetComponent<MovementComponent>()->LockMovement(false);
			m_AccuSec = 0.0f;
			m_IsDying = false;
		}
	}
	if(m_Lives == 0) {
		SceneManager::GetInstance().SetActivateScene("EndScene");
	}
}

void dae::DigDugHealthComponent::Render() {
	if (m_Lives >= 0)
	{
		for (int i{}; i < m_Lives; ++i) {
			m_LifeTextures[i]->Render(Vector3{ float(m_StartPos.x + (i * 40)),m_StartPos.y,m_StartPos.z });
		}
	}
}
