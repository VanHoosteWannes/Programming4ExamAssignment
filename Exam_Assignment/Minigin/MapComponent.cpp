#include "MiniginPCH.h"
#include "MapComponent.h"
#include "Vector3.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"

dae::MapComponent::MapComponent(int rows, int cols) 
:m_Rows(rows)
,m_Cols(cols)
{
	//map size 210
	for(int i{}; i < rows; ++i) {
		for(int j{}; j < cols; ++j) {
			m_Blocks.push_back(std::make_shared<Block>(Block{ Vector3{ j * 32.0f + 16,80 + (i * 32.0f),0 }, true }));
		}
	}
}

void dae::MapComponent::AddDigger(std::shared_ptr<GameObject> digger) {
	m_Diggers.push_back(digger);
}

void dae::MapComponent::Initialize() {}
void dae::MapComponent::Update(float) {
	for(int i{}; i < m_Cols * m_Rows; ++i) {
		if (int(m_Diggers[0]->GetTransform()->GetPosition().x) == m_Blocks[i]->position.x && int(m_Diggers[0]->GetTransform()->GetPosition().y) == m_Blocks[i]->position.y) {
			m_Blocks[i]->isPassed = true;
		}
	}
}

void dae::MapComponent::Render() {
	auto& renderInstance = Renderer::GetInstance();
	for (int i{}; i < (m_Cols * m_Rows); ++i)
	{
		if(m_Blocks[i]->isPassed == true) {
			//renderInstance.RenderTexture(*m_Texture, m_Blocks[i]->position.x - 16, m_Blocks[i]->position.y - 16);
			renderInstance.RenderQuad(m_Blocks[i]->position.x - 16, m_Blocks[i]->position.y - 16, 32, 32);
		}
	}
}
