#include "pch.h"
#include "AIComponent.h"
#include "DigDugConditions.h"
#include "DigDugActions.h"
#include "PointsManager.h"
#include "TransformComponent.h"
#include "MapComponent.h"

int dae::AIComponent::m_index = 0;

dae::AIComponent::AIComponent()
{
	State* idle = new State{};
	State* inflating = new State{};
	State* deflating = new State{};
	State* dead = new State{};
	State* hitByRock = new State{};

	idle->AddTransition(std::make_shared<Transition>( std::make_shared<InflateCondition>(),inflating ));
	idle->AddTransition(std::make_shared<Transition>(std::make_shared<RockCondition>(), hitByRock));
	idle->AddActions(std::make_shared<IdleAction>());

	inflating->AddTransition(std::make_shared<Transition>(std::make_shared<DeflateCondition>(),deflating ));
	inflating->AddTransition(std::make_shared<Transition>(std::make_shared<DeadCondition>(), dead ));
	inflating->AddTransition(std::make_shared<Transition>(std::make_shared<RockCondition>(), hitByRock));
	inflating->AddActions(std::make_shared<InflateAction>());

	deflating->AddTransition(std::make_shared<Transition>(std::make_shared<IdleCondition>(), idle ));
	deflating->AddTransition(std::make_shared<Transition>(std::make_shared<InflateCondition>(), inflating ));
	deflating->AddTransition(std::make_shared<Transition>(std::make_shared<RockCondition>(), hitByRock));
	deflating->AddActions(std::make_shared<DeflateAction>());

	dead->AddActions(std::make_shared<DeadAction>());
	hitByRock->AddActions(std::make_shared<RockAction>());
	//m_pStateMachine = std::make_shared<StateMachine>( std::vector<State*>{idle, inflating, deflating, dead}, idle,m_index );
	m_pStateMachine = new StateMachine{ std::vector<State*>{idle, inflating, deflating, dead, hitByRock}, idle,m_index };

	++m_index;
}

dae::AIComponent::~AIComponent() {
	if (m_pStateMachine != nullptr)
		delete m_pStateMachine;
}

void dae::AIComponent::Update(float deltaTime) {
	if (!m_IsDead)
	{
		m_pStateMachine->Update(deltaTime);
	}
}

void dae::AIComponent::Render() {
	
}

void dae::AIComponent::Dead() {
	m_IsDead = true;
	m_pGameObject->GetComponent<SpriteComponent>()->StopRender(true);
	m_pGameObject->GetComponent<CollisionComponent>()->SetActive(false);
	CalculateScore();
}

void dae::AIComponent::DeadByRock(float deltaTime) {
	m_AccuSec += deltaTime;
	m_pGameObject->GetComponent<SpriteComponent>()->SetSpriteInfo(7, 7, 0, 5, 6, 2);
	if(m_AccuSec >= m_DeadTime) {
		m_IsDead = true;
		m_pGameObject->GetComponent<SpriteComponent>()->StopRender(true);
		m_pGameObject->GetComponent<CollisionComponent>()->SetActive(false);
		PointsManager::GetInstance().AddPoints(1000);
	}
}

void dae::AIComponent::CalculateScore() {
	float yPos = m_pGameObject->GetTransform()->GetPosition().y;
	if (yPos <= 192) {
		PointsManager::GetInstance().AddPoints(400);
	}
	else if (yPos > 192 && yPos <= 320) {
		PointsManager::GetInstance().AddPoints(600);
	}
	else if (yPos > 320 && yPos <= 448) {
		PointsManager::GetInstance().AddPoints(800);
	}
	else if (yPos > 448 && yPos <= 576) {
		PointsManager::GetInstance().AddPoints(1000);
	}
}

void dae::AIComponent::Idle() {
	int x = int(m_pGameObject->GetTransform()->GetPosition().x) / m_GridSize;
	int y = int(m_pGameObject->GetTransform()->GetPosition().y - 64) / m_GridSize;

	if (!MapComponent::GetBlocks()[y * m_Cols + x]->isPassed && (y * m_Cols + x) >13 ) {
		m_pGameObject->GetComponent<SpriteComponent>()->SetSpriteInfo(7, 7, 2, 4, 1, 2);
	}
	else {
		m_pGameObject->GetComponent<SpriteComponent>()->SetSpriteInfo(7,7,0,2,0,2);
	}
}

void dae::AIComponent::Inflate(float deltaTime) {
  	m_AccuSec += deltaTime;
	if (m_AccuSec >= m_CheckTime) {
		++m_InflateStage;
		m_AccuSec = 0;
		m_pGameObject->GetComponent<SpriteComponent>()->SetSpriteInfo(7, 7, 2 + m_InflateStage, 2 + m_InflateStage, 0, 2);
	}
}

void dae::AIComponent::Deflate(float deltaTime) {
	m_AccuSec += deltaTime;
	if (m_AccuSec >= m_CheckTime) {
		--m_InflateStage;
		m_AccuSec = 0;
		m_pGameObject->GetComponent<SpriteComponent>()->SetSpriteInfo(7, 7, 2 + m_InflateStage, 2 + m_InflateStage, 0, 2);
	}
}

