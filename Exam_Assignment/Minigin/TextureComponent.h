#pragma once
#include "Component.h"
#include "Texture2D.h"
#include <SDL.h>

namespace dae
{
	class TextureComponent : public Component
	{
	public:
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) noexcept = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) noexcept = delete;
		virtual ~TextureComponent() = default;
		TextureComponent(const std::string& filename);
		TextureComponent(const std::string& filename, float width, float height);
		TextureComponent(const std::string& filename, float width, float height, SDL_Rect sourceRect);

	protected:
		std::shared_ptr<Texture2D> m_Texture;
		bool m_IsWidthHeight;
		bool m_IsSourceRect;
		SDL_Rect m_SourceRect;
		float m_Height;
		float m_Width;

		void Initialize() override;
		void Render() override;
		void Update(float deltaTime) override;
	};
}

