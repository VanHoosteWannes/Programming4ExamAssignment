#pragma once

//Class based off Gameplay Programming

namespace dae {
	class Node;
	class Connection
	{
	public:
		Connection(std::shared_ptr<Node> pStartNode, std::shared_ptr<Node> pTargetNode) :
			m_pStartNode(pStartNode), m_pTargetNode(pTargetNode) {}
		~Connection() = default;

		void SetGCost(float g) { m_GCost = g; }
		float GetGCost() const { return m_GCost; }
		void SetHCost(float h) { m_HCost = h; }
		float GetHCost() const { return m_HCost; }
		float GetFCost() const { return m_GCost + m_HCost; }
		void ResetCosts() { m_GCost = 0; m_FCost = 0; m_HCost = 0; }

		std::shared_ptr<Node> GetStartNode() const { return m_pStartNode; }
		void SetStartNode(std::shared_ptr<Node> pStartNode) { m_pStartNode = pStartNode; }
		std::shared_ptr<Node> GetEndNode() const { return m_pTargetNode; }
		void SetEndNode(std::shared_ptr<Node> pEndNode) { m_pTargetNode = pEndNode; }
		std::shared_ptr<Connection> GetHeadConnection() const { return m_pHeadConnection; }
		void SetHeadConnection(std::shared_ptr<Connection> pC) { m_pHeadConnection = pC; }

	private:
		std::shared_ptr<Node> m_pStartNode = nullptr;
		std::shared_ptr<Node> m_pTargetNode = nullptr;
		std::shared_ptr<Connection> m_pHeadConnection = nullptr;

		float m_GCost = 0.f;
		float m_HCost = 0.f;
		float m_FCost = 0.f;
	};
}

