#pragma once
#include "Component.h"
#include "Vector3.h"

namespace dae {

	struct Block;
	class TextureComponent;
	class RockComponent final:public Component
	{
	public:
		RockComponent(const std::vector<std::shared_ptr<Block>>& blocks, const std::vector<std::shared_ptr<GameObject>>& diggers, int row, int col);
		virtual ~RockComponent() = default;
		RockComponent(const RockComponent& other) = delete;
		RockComponent(RockComponent&& other) noexcept = delete;
		RockComponent& operator=(const RockComponent& other) = delete;
		RockComponent& operator=(RockComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;
	private:
		std::shared_ptr<TextureComponent> m_Texture;
		int m_Index;
		Vector3 m_Position;
		float m_EndPosition;
		bool m_IsFalling;
		bool m_CheckRest;
		std::vector<std::shared_ptr<Block>> m_Blocks;
		std::vector<std::shared_ptr<GameObject>> m_Diggers;
	};
}

