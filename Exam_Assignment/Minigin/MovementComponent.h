#pragma once
#include "Component.h"

namespace dae {
	class MovementComponent :
		public Component
	{
	public:
		MovementComponent(float speed);
		MovementComponent(const MovementComponent& other) = delete;
		MovementComponent(MovementComponent&& other) noexcept = delete;
		MovementComponent& operator=(const MovementComponent& other) = delete;
		MovementComponent& operator=(MovementComponent&& other) noexcept = delete;
		virtual ~MovementComponent() = default;

		void MoveUp() const;
		void MoveDown() const;
		void MoveRight() const;
		void MoveLeft() const;

	protected:
		void Initialize() override;
		void Render() override;
		void Update(float deltaTime) override;

		float m_Speed;
	};
}

