#pragma once
#include "Component.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(push)

namespace dae
{
	class TransformComponent final : public Component
	{
		glm::vec3 m_Position;
	public:
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) noexcept = delete;
		virtual ~TransformComponent() = default;
		TransformComponent();

		const glm::vec3& GetPosition() const { return m_Position; }
		void Translate(float x, float y, float z);
		void SetPosition(float x, float y, float z);
	protected:
		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;
	};
}

