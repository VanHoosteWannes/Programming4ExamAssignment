#pragma once
#include "Component.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(push)

namespace dae
{
	class TextComponent;
	class Font;

	class FPSComponent : public Component
	{
	public:
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) noexcept = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) noexcept = delete;
		FPSComponent(std::shared_ptr<Font> font, glm::vec3 color);
		virtual ~FPSComponent() = default;
	protected:
		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() override;
	private:
		std::shared_ptr<TextComponent> m_TextComp;
		float m_FpsUpdateDelay;
		std::string m_Text;
	};
}
