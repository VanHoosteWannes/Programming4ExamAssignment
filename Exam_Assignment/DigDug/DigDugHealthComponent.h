#pragma once
#include "HealthComponent.h"
#include "TextureComponent.h"

namespace dae {
	class DigDugHealthComponent final:public HealthComponent
	{
	public:
		DigDugHealthComponent(int lives, Vector3 startPos, const std::string& filePath, Vector3 respawnPoint);
		virtual ~DigDugHealthComponent() = default;
		DigDugHealthComponent(const DigDugHealthComponent& other) = delete;
		DigDugHealthComponent(DigDugHealthComponent&& other) noexcept = delete;
		DigDugHealthComponent& operator=(const DigDugHealthComponent& other) = delete;
		DigDugHealthComponent& operator=(DigDugHealthComponent&& other) noexcept = delete;
		void Update(float deltaTime) override;
		void Render() override;
	private:
		std::vector<std::shared_ptr<TextureComponent>> m_LifeTextures;
		Vector3 m_StartPos;
		bool m_IsDying = false;
		float m_DieTime;
		float m_AccuSec;
		Vector3 m_RespawnPoint;
	};
}

