#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"

dae::SpriteComponent::SpriteComponent(const std::string& filename, float width, float height)
	: m_Texture{ ResourceManager::GetInstance().LoadTexture(filename) }
	, m_Height{ height }
	, m_Width{ width }
	, m_SourceRect{}
    ,m_Cols{0}
    ,m_Rows{0}
    ,m_Xoffset1{0}
    ,m_Xoffset2{0}
    ,m_YOffset{0}
	,m_FrameSec{0.2f}
    , m_ActFrame{0}
    ,m_AccuSet{0}
    ,m_Scale{1}
{
}

void dae::SpriteComponent::SetSpriteInfo(int rows, int cols, int xOffset1, int xOffset2, int yOffset, float scale) {
	m_Rows = rows;
	m_Cols = cols;
	m_Xoffset1 = xOffset1;
	m_ActFrame = xOffset1;
	m_Xoffset2 = xOffset2;
	m_YOffset = yOffset;
	m_Scale = scale;
}

void dae::SpriteComponent::Initialize() {}
void dae::SpriteComponent::Render() {
	auto pos = m_pGameObject->GetTransform()->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x - m_Width / m_Cols / 2, pos.y - m_Height / m_Rows / 2, m_Width / m_Cols * m_Scale, m_Height / m_Rows * m_Scale,
		SDL_Rect{ int((m_Width / m_Cols) * m_ActFrame), int(m_Height / m_Rows * m_YOffset), int(m_Width / m_Cols), int(m_Height / m_Rows) });
}
void dae::SpriteComponent::Update(float deltaTime) {
	UNREFERENCED_PARAMETER(deltaTime);
	m_AccuSet += deltaTime;
	if (m_AccuSet > m_FrameSec)
	{
		++m_ActFrame;
		if (m_ActFrame >= m_Xoffset2)
		{
			m_ActFrame = m_Xoffset1;
		}

		m_AccuSet -= m_FrameSec;
	}
}
