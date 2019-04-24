#include "MiniginPCH.h"
#include "MapComponent.h"
#include "Vector3.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "RockComponent.h"
#include "BinaryReader.h"

dae::MapComponent::MapComponent(int rows, int cols) 
:m_Rows(rows)
,m_Cols(cols)
{
	//map size 210
	for(int i{}; i < rows; ++i) {
		for(int j{}; j < cols; ++j) {
			m_Blocks.push_back(std::make_shared<Block>(Block{ Vector3{ j * 32.0f + 16,80 + (i * 32.0f),0 }, false }));
		}
	}

	BinaryReader reader{ "level1.bin" };
	for(int i{}; i < rows * cols; ++i) {
		if(reader.Read<bool>() == true) {
			m_Blocks[i]->isPassed = true;
		}
	}

	m_Rocks.push_back(std::make_shared<RockComponent>(m_Blocks, m_Diggers,2, 1));
	m_Rocks.push_back(std::make_shared<RockComponent>(m_Blocks, m_Diggers, 3, 7));
	m_Rocks.push_back(std::make_shared<RockComponent>(m_Blocks, m_Diggers, 5, 3));
}

void dae::MapComponent::AddDigger(std::shared_ptr<GameObject> digger) {
	m_Diggers.push_back(digger);
}

void dae::MapComponent::AddTunnel(int row, int col, int size, bool isHorizontal) {
	if(isHorizontal) {
		if (row * 14 + col + size <= int(m_Blocks.size()))
		{
			for (int i{ 0 }; i < size; ++i) {
				m_Blocks[row * 14 + col + i]->isPassed = true;
			}
		}
	}
	else {
		if (row * 14 + col + (size * 14) <= int(m_Blocks.size()))
		{
			for (int i{ 0 }; i < size; ++i) {
				m_Blocks[row * 14 + col + (i * 14)]->isPassed = true;
			}
		}
	}
}

void dae::MapComponent::Initialize() {}
void dae::MapComponent::Update(float deltaTime) {
	for(int i{}; i < m_Cols * m_Rows; ++i) {
		if (int(m_Diggers[0]->GetTransform()->GetPosition().x) == m_Blocks[i]->position.x && int(m_Diggers[0]->GetTransform()->GetPosition().y) == m_Blocks[i]->position.y) {
			m_Blocks[i]->isPassed = true;
		}
	}
	for (auto element : m_Rocks) {
		element->Update(deltaTime);
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
	for(auto element: m_Rocks) {
		element->Render();
	}
}
