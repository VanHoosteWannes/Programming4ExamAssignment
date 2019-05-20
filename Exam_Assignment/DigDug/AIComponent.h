#pragma once
#include "Component.h"
#include "StateMachine.h"
#include "SpriteComponent.h"

namespace dae {
	class AIComponent :public Component
	{
	public:
		AIComponent();
		AIComponent(const AIComponent& other) = delete;
		AIComponent(AIComponent&& other) noexcept = delete;
		AIComponent& operator=(const AIComponent& other) = delete;
		AIComponent& operator=(AIComponent&& other) noexcept = delete;
		~AIComponent();
		void Update(float deltaTime) override;
		void Render() override;
		int GetInflateState() { return m_InflateStage; }
		void Inflate(float deltaTime);
		void Deflate(float deltaTime);
		void Dead();
		static void ResetCount() { m_index = 0; };
		void DeadByRock(float deltaTime);
		void CalculateScore();
		void Idle();
		bool IsDead() { return m_IsDead; }
	private:
		StateMachine* m_pStateMachine;
		//std::shared_ptr<StateMachine> m_pStateMachine;
		int m_InflateStage = 0;
		float m_AccuSec;
		float m_CheckTime = 0.5f;
		float m_DeadTime = 0.9f;
		bool m_IsDead;
		int m_GridSize = 32;
		int m_Cols = 14;
		static int m_index;
	};
}

