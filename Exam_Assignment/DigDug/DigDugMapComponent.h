#pragma once
#include "MapComponent.h"
#include "FallingComponent..h"

namespace dae {
	class DigDugMapComponent final :public MapComponent
	{
	public:
		DigDugMapComponent(int rows, int cols, float tileSize, float startPositionX, float startPositionY, float textureOffset);
		virtual ~DigDugMapComponent() = default;

	private:
		std::vector<std::shared_ptr<FallingComponent>> m_Rocks;

		void Update(float deltaTime) override;
		void Render() override;
	};
}

