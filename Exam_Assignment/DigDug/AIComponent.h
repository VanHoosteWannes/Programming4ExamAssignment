#pragma once
#include "Component.h"
#include "StateMachine.h"

namespace dae {
	class AIComponent :public Component
	{
	public:
		AIComponent();
		AIComponent(const AIComponent& other) = delete;
		AIComponent(AIComponent&& other) noexcept = delete;
		AIComponent& operator=(const AIComponent& other) = delete;
		AIComponent& operator=(AIComponent&& other) noexcept = delete;
		virtual ~AIComponent() = default;
	private:
		StateMachine* m_pStateMachine;
	};
}

