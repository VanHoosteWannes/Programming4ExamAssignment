#include "MiniginPCH.h"
#include "TransformComponent.h"

dae::TransformComponent::TransformComponent()
	:m_Position(0,0,0)
{
}

void dae::TransformComponent::Translate(float x, float y, float z) {
	m_Position.x += x;
	m_Position.y += y;
	m_Position.z += z;
}

void dae::TransformComponent::SetPosition(const float x, const float y, const float z) {
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
void dae::TransformComponent::Initialize() {
}
void dae::TransformComponent::Update(float deltaTime) {
	UNREFERENCED_PARAMETER(deltaTime);
}
void dae::TransformComponent::Render() {
	
}


