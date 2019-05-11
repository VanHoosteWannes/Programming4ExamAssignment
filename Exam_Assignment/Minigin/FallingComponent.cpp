#include "MiniginPCH.h"
#include "FallingComponent..h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "Block.h"

dae::FallingComponent::FallingComponent(const std::vector<std::shared_ptr<Block>>& blocks,const std::string& texturePath, int row, int col, int rows, int cols, float tileSize, float textureOffset)
:m_Blocks(std::move(blocks)),m_CheckRest(false),m_IsFalling(false)
,m_Cols(cols)
,m_Rows(rows)
,m_TileSize(tileSize)
,m_TextureOffset(textureOffset){
	m_Texture = std::make_shared<TextureComponent>(texturePath);
	m_Collider = std::make_shared<CollisionComponent>(32.0f, 32.0f, "Rock");
	m_Index = (row *  cols) + col;
	m_Position = Vector3{ col * tileSize + textureOffset, (tileSize*2 + textureOffset) + (row * tileSize), 0 };
}

void dae::FallingComponent::Update(float) {
	m_Collider->Update(m_Position.x, m_Position.y);
	if (m_Blocks[m_Index + m_Cols]->isPassed) {
		m_CheckRest = true;
	}
	else {
		m_CheckRest = false;
	}
	for (int i{ 1 }; i < m_Rows; ++i) {
		if (m_Index + (m_Cols * i) <= int(m_Blocks.size())) {
			if (m_CheckRest) {
				if (m_Blocks[m_Index + (m_Cols * i)]->isPassed) {
					m_EndPosition = m_Blocks[m_Index + (m_Cols * i)]->position.y;
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
void dae::FallingComponent::Render() {
	m_Texture->Render(Vector3{ m_Position.x - m_TextureOffset, m_Position.y - m_TextureOffset, 0 });
}
