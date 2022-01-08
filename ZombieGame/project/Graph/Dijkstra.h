#pragma once
#include "Graph.h"

class Dijkstra
{
public:
	static std::vector<GraphNode*> FindPath(Graph* pGraph, GraphNode* pStartNode, GraphNode* pGoalNode);
private:
	struct NodeRecord
	{
		GraphNode* pNode = nullptr;
		NodeRecord* previousRecord = nullptr;
		float costSoFar = 0.f; // accumulated g-costs of all the connections leading up to this one

		bool operator==(const NodeRecord& other) const
		{
			return pNode == other.pNode
				&& previousRecord == other.previousRecord
				&& costSoFar == other.costSoFar;
		}

		bool operator<(const NodeRecord& other) const
		{
			return costSoFar < other.costSoFar;
		}
	};
	
};

