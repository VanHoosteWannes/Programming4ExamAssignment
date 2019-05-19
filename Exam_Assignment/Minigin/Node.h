#pragma once
#include "Vector3.h"
#include "Connection.h"

//class based off Gameplay Programming
namespace dae {
	class Node
	{
	public:
		Node(const Vector2& position)
			:m_Position(position) {}
		~Node() = default;

		const Vector2& GetPosition() const { return m_Position; }
		void SetPosition(const Vector2& p) { m_Position = p; }
		bool IsWalkable() const { return m_IsWalkable; }
		void SetWalkable(bool state) { m_IsWalkable = state; }

		void AddConnection(const std::shared_ptr<Node>& m_pNode)
		{
			std::shared_ptr<Connection> newConnection = std::make_shared<Connection>(std::make_shared<Node>(*this), m_pNode);
			m_pConnections.push_back(newConnection);
		}

		std::vector<std::shared_ptr<Connection>> GetConnections() const
		{
			return m_pConnections;
		}

		void ResetCosts()
		{
			for (auto pC : m_pConnections)
			{
				pC->ResetCosts();
			}
		}

	private:
		//--- Datamembers ---
		std::vector<std::shared_ptr<Connection>> m_pConnections;
		Vector2 m_Position = Vector2{0,0};
		bool m_IsWalkable = true;
	};
}

