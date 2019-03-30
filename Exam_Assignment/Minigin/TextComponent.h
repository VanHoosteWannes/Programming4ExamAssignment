#pragma once
#include "Component.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(push)

namespace dae
{
	class Font;
	class Texture2D;

	class TextComponent : public Component
	{
	public:
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) noexcept = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;
		TextComponent(const std::string& text, std::shared_ptr<Font> font, glm::vec3 color);
		virtual ~TextComponent() = default;
		void setText(std::string text);
		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;
		void Render(glm::vec3 pos); //used by the FPSComponent
	private:
		bool mNeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
		glm::vec3 m_Color;
	};
}

