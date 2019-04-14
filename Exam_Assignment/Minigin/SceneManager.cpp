#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>


void dae::SceneManager::Update(float deltaTime)
{
	m_ActiveScene->RootUpdate(deltaTime);
}

void dae::SceneManager::Render()
{

	m_ActiveScene->RootRender();
}

void dae::SceneManager::AddScene(std::shared_ptr<Scene> pScene) {
	//only add if not in already
	auto it = std::find(m_pScenes.begin(), m_pScenes.end(), pScene);

	if (it == m_pScenes.end())
	{
		m_pScenes.push_back(pScene);
		if (m_ActiveScene == nullptr && m_NewActiveScene == nullptr)
		{
			m_ActiveScene = pScene;
			m_NewActiveScene = pScene;
		}
	}
}

void dae::SceneManager::RemoveScene(std::shared_ptr<Scene> pScene) {
	auto it = find(m_pScenes.begin(), m_pScenes.end(), pScene);

	if (it != m_pScenes.end())
	{
		m_pScenes.erase(it);
	}
}

void dae::SceneManager::NextScene() {
	for (unsigned int i = 0; i < m_pScenes.size(); ++i)
	{
		if (m_pScenes[i] == m_ActiveScene)
		{
			auto nextScene = ++i % m_pScenes.size();
			m_NewActiveScene = m_pScenes[nextScene];
			break;
		}
	}
}

void dae::SceneManager::Initialize() {
	for(auto scenes: m_pScenes) {
		scenes->RootInitialize();
	}
}
