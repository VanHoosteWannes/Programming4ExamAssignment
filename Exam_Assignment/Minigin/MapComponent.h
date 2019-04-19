#pragma once
#include "Component.h"
#include "Block.h"
#include "Texture2D.h"

namespace dae {
	class TextureComponent;
	class MapComponent : public Component
	{
	public:
		virtual ~MapComponent() = default;
		MapComponent(const MapComponent& other) = delete;
		MapComponent(MapComponent&& other) noexcept = delete;
		MapComponent& operator=(const MapComponent& other) = delete;
		MapComponent& operator=(MapComponent&& other) noexcept = delete;
		MapComponent(int rows, int cols);
		void AddDigger(std::shared_ptr<GameObject> digger);
	private:
		std::vector<std::shared_ptr<Block>> m_Blocks;
		std::vector<std::shared_ptr<TextureComponent>> m_Textures;
		std::vector<std::shared_ptr<GameObject>> m_Diggers;
		int m_Rows;
		int m_Cols;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;
	};
}

