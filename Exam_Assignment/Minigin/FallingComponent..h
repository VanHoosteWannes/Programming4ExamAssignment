#pragma once
#include "Component.h"
#include "Vector3.h"
#include "CollisionComponent.h"

namespace dae {

	struct Block;
	class TextureComponent;
	class FallingComponent final:public Component
	{
	public:
		FallingComponent(const std::vector<std::shared_ptr<Block>>& blocks, const std::string& texturePath,int row, int col, int rows, int cols, float tileSize, float textureOffset);
		virtual ~FallingComponent() = default;
		FallingComponent(const FallingComponent& other) = delete;
		FallingComponent(FallingComponent&& other) noexcept = delete;
		FallingComponent& operator=(const FallingComponent& other) = delete;
		FallingComponent& operator=(FallingComponent&& other) noexcept = delete;

		void Update(float deltaTime) override;
		void Render() override;
	private:
		std::shared_ptr<TextureComponent> m_Texture;
		std::shared_ptr<CollisionComponent> m_Collider;
		int m_Index;
		int m_Rows;
		int m_Cols;
		float m_TileSize;
		float m_TextureOffset;
		Vector3 m_Position;
		float m_EndPosition;
		bool m_IsFalling;
		bool m_CheckRest;
		std::vector<std::shared_ptr<Block>> m_Blocks;
	};
}

