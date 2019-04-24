#include "MiniginPCH.h"
#include "RockComponent.h"
#include "TransformComponent.h"

dae::RockComponent::RockComponent(std::vector<std::shared_ptr<Block>> blocks, std::vector<std::shared_ptr<GameObject>> diggers, int row, int col) 
:m_Blocks(blocks),m_Diggers(diggers),m_CheckRest(false),m_IsFalling(false) {
	m_Texture = std::make_shared<TextureComponent>("rock.png");
	m_Index = (row *  14) + col;
	m_Position = Vector3{ col * 32.0f + 16, 80 + (row * 32.0f), 0 };
}

void dae::RockComponent::Initialize() {}
void dae::RockComponent::Update(float) {
	if (m_Blocks[m_Index + 14]->isPassed) {
		m_CheckRest = true;
	}
	else {
		m_CheckRest = false;
	}
	for (int i{ 1 }; i < 15; ++i) {
		if (m_Index + (14 * i) <= int(m_Blocks.size())) {
			if (m_CheckRest) {
				if (m_Blocks[m_Index + (14 * i)]->isPassed) {
					m_EndPosition = m_Blocks[m_Index + (14 * i)]->position.y;
				}
				else {
						m_CheckRest = false;
						m_IsFalling = true;
				}
			}
		}
		else {
					m_IsFalling = true;
			}
	}

	if (m_IsFalling) {
		if (m_Position.y < m_EndPosition) {
			m_Position.y += 0.1f;
		}
	}
}
void dae::RockComponent::Render() {
	m_Texture->Render(Vector3{ m_Position.x - 16, m_Position.y - 16, 0 });
}
