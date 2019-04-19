#include "MiniginPCH.h"
#include "MovementComponent.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

dae::MovementComponent::MovementComponent(float speed, float maxWidth, float maxHeight)
:m_Speed(speed)
,m_MaxHeight(maxHeight)
,m_MaxWidth(maxWidth)
,m_CurrentDirection(Direction::Right)
,m_PreviousDirection(Direction::Right)
,m_CanMoveUpDown(true)
,m_CanMoveLeftRight(true)
{
	m_Sprite = std::make_shared<SpriteComponent>("CharacterSpriteSheet.png", 112.0f, 112.0f);
	m_Sprite->SetSpriteInfo(7, 7, 0, 2, 0, 2);
}

void dae::MovementComponent::MoveUp() {
	m_PreviousDirection = m_CurrentDirection;
	m_CurrentDirection = Direction::Up;
	if (m_CanMoveUpDown)
	{
		m_Sprite->SetSpriteInfo(7, 7, 0, 2, 5, 2);

		if (m_pGameObject->GetTransform()->GetPosition().y + m_Speed >= 48)
		{
			m_pGameObject->GetTransform()->Translate(0, -m_Speed, 0);
			m_CanMoveLeftRight = false;
		}
	}
}
void dae::MovementComponent::MoveDown(){
	m_PreviousDirection = m_CurrentDirection;
	m_CurrentDirection = Direction::Down;
	if (m_CanMoveUpDown)
	{
		m_Sprite->SetSpriteInfo(7, 7, 0, 2, 3, 2);

		if (m_pGameObject->GetTransform()->GetPosition().y - m_Speed <= m_MaxHeight - 48)
		{
			m_pGameObject->GetTransform()->Translate(0, m_Speed, 0);
			m_CanMoveLeftRight = false;
		}
	}
}
void dae::MovementComponent::MoveRight(){
	m_PreviousDirection = m_CurrentDirection;
	m_CurrentDirection = Direction::Right;
	if (m_CanMoveLeftRight)
	{
		m_Sprite->SetSpriteInfo(7, 7, 0, 2, 0, 2);

		if (m_pGameObject->GetTransform()->GetPosition().x + m_Speed <= m_MaxWidth - 16)
		{
			m_pGameObject->GetTransform()->Translate(m_Speed, 0, 0);
			m_CanMoveUpDown = false;
		}
	}
}
void dae::MovementComponent::MoveLeft() {
	m_PreviousDirection = m_CurrentDirection;
	m_CurrentDirection = Direction::Left;
	if (m_CanMoveLeftRight)
	{
		m_Sprite->SetSpriteInfo(7, 7, 0, 2, 1, 2);

		if (m_pGameObject->GetTransform()->GetPosition().x - m_Speed >= 16)
		{
			m_pGameObject->GetTransform()->Translate(-m_Speed, 0, 0);
			m_CanMoveUpDown = false;
		}
	}
}

void dae::MovementComponent::Initialize() {
}
void dae::MovementComponent::Render() {
	m_Sprite->Render(GetGameObject()->GetTransform()->GetPosition());
}
void dae::MovementComponent::Update(float deltaTime) {
	m_Sprite->Update(deltaTime);
	//this makes sure you stay locked on the grid
	if (!m_CanMoveUpDown) //Check for up down movement
	{
		if (m_CurrentDirection == Direction::Up && m_PreviousDirection == Direction::Right) {
			m_Corrections[0] = true;
		}
		else if (m_CurrentDirection == Direction::Up && m_PreviousDirection == Direction::Left) {
			m_Corrections[1] = true;
		}
		else if (m_CurrentDirection == Direction::Down && m_PreviousDirection == Direction::Right) {
			m_Corrections[2] = true;
		}
		else if (m_CurrentDirection == Direction::Down && m_PreviousDirection == Direction::Left) {
			m_Corrections[3] = true;
		}
	}
	if(!m_CanMoveLeftRight) {
		if (m_CurrentDirection == Direction::Left && m_PreviousDirection == Direction::Up) {
			m_Corrections[4] = true;
		}
		else if (m_CurrentDirection == Direction::Left && m_PreviousDirection == Direction::Down) {
			m_Corrections[5] = true;
		}
		else if (m_CurrentDirection == Direction::Right && m_PreviousDirection == Direction::Up) {
			m_Corrections[6] = true;
		}
		else if (m_CurrentDirection == Direction::Right && m_PreviousDirection == Direction::Down) {
			m_Corrections[7] = true;
		}
	}

	if(m_Corrections[0]) {
		if (int(m_pGameObject->GetTransform()->GetPosition().x - 16) % 32 == 0) {
			m_CanMoveUpDown = true;
			m_Corrections[0] = false;
		}
		else {
			m_pGameObject->GetTransform()->Translate(m_Speed, 0, 0);
		}
	}
	else if(m_Corrections[1]){
		if (int(m_pGameObject->GetTransform()->GetPosition().x - 16) % 32 == 0) {
			m_CanMoveUpDown = true;
			m_Corrections[1] = false;
		}
		else {
			m_pGameObject->GetTransform()->Translate(-m_Speed, 0, 0);
		}
	}
	else if (m_Corrections[2]) {
		if (int(m_pGameObject->GetTransform()->GetPosition().x - 16) % 32 == 0) {
			m_CanMoveUpDown = true;
			m_Corrections[2] = false;
		}
		else {
			m_pGameObject->GetTransform()->Translate(m_Speed, 0, 0);
		}
	}
	else if (m_Corrections[3]) {
		if (int(m_pGameObject->GetTransform()->GetPosition().x - 16) % 32 == 0) {
			m_CanMoveUpDown = true;
			m_Corrections[3] = false;
		}
		else {
			m_pGameObject->GetTransform()->Translate(-m_Speed, 0, 0);
		}
	}
	else if (m_Corrections[4]) {
		if (int(m_pGameObject->GetTransform()->GetPosition().y - 16) % 32 == 0) {
			m_CanMoveLeftRight = true;
			m_Corrections[4] = false;
		}
		else {
			m_pGameObject->GetTransform()->Translate(0, -m_Speed, 0);
		}
	}
	else if (m_Corrections[5]) {
		if (int(m_pGameObject->GetTransform()->GetPosition().y - 16) % 32 == 0) {
			m_CanMoveLeftRight = true;
			m_Corrections[5] = false;
		}
		else {
			m_pGameObject->GetTransform()->Translate(0, m_Speed, 0);
		}
	}
	else if (m_Corrections[6]) {
		if (int(m_pGameObject->GetTransform()->GetPosition().y - 16) % 32 == 0) {
			m_CanMoveLeftRight = true;
			m_Corrections[6] = false;
		}
		else {
			m_pGameObject->GetTransform()->Translate(0, -m_Speed, 0);
		}
	}
	else if (m_Corrections[7]) {
		if (int(m_pGameObject->GetTransform()->GetPosition().y - 16) % 32 == 0) {
			m_CanMoveLeftRight = true;
			m_Corrections[7] = false;
		}
		else {
			m_pGameObject->GetTransform()->Translate(0, m_Speed, 0);
		}
	}
}
