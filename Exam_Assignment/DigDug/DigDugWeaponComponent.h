#pragma once
#include <Component.h>
#include "TextureComponent.h"

namespace dae {
	class DigDugWeaponComponent :public Component
	{
	public:
		DigDugWeaponComponent(const std::string& filePath);
		virtual ~DigDugWeaponComponent() = default;
		DigDugWeaponComponent(const DigDugWeaponComponent& other) = delete;
		DigDugWeaponComponent(DigDugWeaponComponent&& other) noexcept = delete;
		DigDugWeaponComponent& operator=(const DigDugWeaponComponent& other) = delete;
		DigDugWeaponComponent& operator=(DigDugWeaponComponent&& other) noexcept = delete;
		void Update(float deltaTime) override;
		void Render() override;
		void Activate();

	private:
		bool m_Active;
		float m_AccuSet;
		float m_FrameTime = 0.1f;
		std::vector<std::shared_ptr<TextureComponent>> m_WeaponTextures;
	};
}

