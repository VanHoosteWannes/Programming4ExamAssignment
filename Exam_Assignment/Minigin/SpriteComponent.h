#pragma once
#include "Component.h"
#include <SDL.h>
#include "Texture2D.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(push)

namespace dae
{
	class SpriteComponent :public Component
	{
	public:
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) noexcept = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) noexcept = delete;
		virtual ~SpriteComponent() = default;
		SpriteComponent(const std::string& filename, float width, float height);
		void Render(glm::vec3 pos);
		void SetSpriteInfo(int rows, int cols, int xOffset1, int xOffset2, int yOffset, float scale);
		void Update(float deltaTime) override;
	protected:
		std::shared_ptr<Texture2D> m_Texture;
		SDL_Rect m_SourceRect;
		int m_Rows;
		int m_Cols;
		int m_Xoffset1;
		int m_Xoffset2;
		int m_YOffset;
		int m_ActFrame;
		float m_Height;
		float m_Width;
		float m_Scale;
		float m_FrameSec;
		float m_AccuSet;

		void Initialize() override;
		void Render() override;
	};
}

