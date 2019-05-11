#pragma once
#include "Component.h"
#include <map>


namespace dae {
	struct Rectangle {
		float xPos;
		float yPos;
		float Widht;
		float height;
	};

	class CollisionComponent final:public Component
	{
	public:
		CollisionComponent(float Width, float Height, const std::string& tag);
		void AllowCollisionWithTag(const std::string& tag);
		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) noexcept = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) noexcept = delete;
		virtual ~CollisionComponent() = default;
		bool CheckCollision(Rectangle other);
		void Render() override;
		void Update(float deltaTime) override;
		void Update(float posX, float posY);
	private:
		void CheckCollisionWithTags();
		bool m_IsColliding;
		Rectangle m_Rect;
		static std::multimap<std::string, CollisionComponent*> m_Colliders;
		std::vector<std::string> m_CollidingTags;
	};
}

