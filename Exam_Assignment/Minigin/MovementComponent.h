#pragma once
#include "Component.h"

//component made so i can easily assign it to an enemy for the versus mode
namespace dae {

	class SpriteComponent;
	class MovementComponent final:public Component
	{
	public:
		enum class Direction {
			Left,
			Right,
			Up,
			Down
		};
		MovementComponent(float speed, float minX, float minY, float maxX, float maxY, float textureOffset, float tileSize);
		MovementComponent(const MovementComponent& other) = delete;
		MovementComponent(MovementComponent&& other) noexcept = delete;
		MovementComponent& operator=(const MovementComponent& other) = delete;
		MovementComponent& operator=(MovementComponent&& other) noexcept = delete;
		virtual ~MovementComponent() = default;

		void MoveUp();
		void MoveDown();
		void MoveRight();
		void MoveLeft();

	protected:
		void Render() override;
		void Update(float deltaTime) override;

		float m_Speed;
		float m_MaxX;
		float m_MaxY;
		float m_MinX;
		float m_MinY;
		float m_TextureOffset;
		float m_TileSize;
		Direction m_CurrentDirection;
		Direction m_PreviousDirection;
		bool m_CanMoveUpDown;
		bool m_CanMoveLeftRight;
		bool m_Corrections[8];
		std::shared_ptr<SpriteComponent> m_Sprite;
	};
}

