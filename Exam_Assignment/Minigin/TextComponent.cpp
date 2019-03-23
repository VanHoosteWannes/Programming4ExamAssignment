#include "MiniginPCH.h"
#include "TextComponent.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "TransformComponent.h"

dae::TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font, glm::vec3 color = {255,255,255})
	: mNeedsUpdate(true), m_Text(text), m_Font(font), m_Texture(nullptr)
,m_isFPS(false), m_FpsUpdateDelay(1.0f),  m_Color(color)
{
}

void dae::TextComponent::setFPS(bool FPS) {
	m_isFPS = FPS;
}

void dae::TextComponent::Initialize() {}
void dae::TextComponent::Update(float deltaTime) {
	if (mNeedsUpdate)
	{
		if (m_isFPS) {
		    m_FpsUpdateDelay -= deltaTime;
			if (m_FpsUpdateDelay <= 0)
			{
				m_Text = "FPS: " + std::to_string(int(1.0f / deltaTime));
				m_FpsUpdateDelay = 1.0f;
			}
		}
		const SDL_Color color = {UINT8(m_Color.x), UINT8(m_Color.y), UINT8(m_Color.z) }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
	}
	UNREFERENCED_PARAMETER(deltaTime);
}
void dae::TextComponent::Render() {
	if (m_Texture != nullptr)
	{
		const auto pos = GetGameObject()->GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}
