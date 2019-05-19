#pragma once
#include "Vector3.h"

//Class based off Gameplay Programming

namespace dae {
	//Function pointer type to heuristic function
	typedef float(*Heuristics)(float, float);

	class Connection;
	class Node;
	class AStarPathfinder
	{
	public:
		AStarPathfinder();
		~AStarPathfinder() = default;

		std::vector<dae::Vector2> FindPath(std::shared_ptr<Node> pStartNode, std::shared_ptr<Node> pEndNode,Heuristics heuristicFunction);
		void CalculateCosts(std::shared_ptr<Connection> pC, std::shared_ptr<Node> pStartNode, std::shared_ptr<Node> pTargetNode, Heuristics heuristicFunction);
	};
}

