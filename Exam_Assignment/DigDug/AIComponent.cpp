#include "pch.h"
#include "AIComponent.h"


dae::AIComponent::AIComponent()
{

	State* yes = new State{};
	m_pStateMachine = new StateMachine{ std::vector<State*>{yes}, yes };
}

