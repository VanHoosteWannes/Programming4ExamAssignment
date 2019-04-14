#include "MiniginPCH.h"
#include "MovementComponent.h"
#include "TransformComponent.h"

dae::MovementComponent::MovementComponent(float speed):m_Speed(speed) {
}

void dae::MovementComponent::MoveUp() const {
	m_pGameObject->GetTransform()->Translate(0, -m_Speed, 0);
}
void dae::MovementComponent::MoveDown() const{
	m_pGameObject->GetTransform()->Translate(0, m_Speed, 0);
}
void dae::MovementComponent::MoveRight() const{
	m_pGameObject->GetTransform()->Translate(m_Speed, 0, 0);
}
void dae::MovementComponent::MoveLeft() const{
	m_pGameObject->GetTransform()->Translate(-m_Speed, 0, 0);
}

void dae::MovementComponent::Initialize() {
}
void dae::MovementComponent::Render() {}
void dae::MovementComponent::Update(float) {

}
