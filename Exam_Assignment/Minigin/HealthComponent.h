#pragma once
#include "Component.h"

namespace dae {
	class HealthComponent :
		public Component
	{
	public:
		HealthComponent(int lives);
		virtual ~HealthComponent() = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) noexcept = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) noexcept = delete;

		void RemoveLife();
		void SetLives(int amountOfLives);
		void Update(float deltaTime) override;
		void Render() override;
	protected:
		int m_Lives;
	};
}

