#pragma once

namespace Elite
{
	template <class T_NodeType, class T_ConnectionType>
	class AStar
	{
	public:
		AStar(IGraph<T_NodeType, T_ConnectionType>* pGraph, Heuristic hFunction);

		// stores the optimal connection to a node and its total costs related to the start and end node of the path
		struct NodeRecord
		{
			T_NodeType* pNode = nullptr;
			T_ConnectionType* pConnection = nullptr;
			float costSoFar = 0.f; // accumulated g-costs of all the connections leading up to this one
			float estimatedTotalCost = 0.f; // f-cost (= costSoFar + h-cost)

			bool operator==(const NodeRecord& other) const
			{
				return pNode == other.pNode
					&& pConnection == other.pConnection
					&& costSoFar == other.costSoFar
					&& estimatedTotalCost == other.estimatedTotalCost;
			};

			bool operator<(const NodeRecord& other) const
			{
				return estimatedTotalCost < other.estimatedTotalCost;
			};
		};

		std::vector<T_NodeType*> FindPath(T_NodeType* pStartNode, T_NodeType* pDestinationNode);

	private:
		float GetHeuristicCost(T_NodeType* pStartNode, T_NodeType* pEndNode) const;

		IGraph<T_NodeType, T_ConnectionType>* m_pGraph;
		Heuristic m_HeuristicFunction;
	};

	template <class T_NodeType, class T_ConnectionType>
	AStar<T_NodeType, T_ConnectionType>::AStar(IGraph<T_NodeType, T_ConnectionType>* pGraph, Heuristic hFunction)
		: m_pGraph(pGraph)
		, m_HeuristicFunction(hFunction)
	{
	}

	template <class T_NodeType, class T_ConnectionType>
	std::vector<T_NodeType*> AStar<T_NodeType, T_ConnectionType>::FindPath(T_NodeType* pStartNode, T_NodeType* pGoalNode)
	{
		vector<T_NodeType*> path;
		vector<NodeRecord> openList;
		vector<NodeRecord> closedList;
		NodeRecord startRecord;
		startRecord.pNode = pStartNode;
		startRecord.pConnection = nullptr;
		startRecord.estimatedTotalCost = GetHeuristicCost(pStartNode, pGoalNode);
		openList.push_back(startRecord); //Kickstarting the loop
		NodeRecord currentRecord = startRecord;

		while (!openList.empty())
		{
			float lowestCost = FLT_MAX;
			for (NodeRecord record : openList)
			{
				if (record.estimatedTotalCost < lowestCost)
				{
					currentRecord = record;
					lowestCost = record.estimatedTotalCost;
				}
			}
			T_NodeType* currentNode = currentRecord.pNode;

			if (currentNode == pGoalNode)
			{
				break; //End node found
			}
			for (Elite::GraphConnection* conn : m_pGraph->GetNodeConnections(currentNode))
			{
				float gCostCurrentConn = conn->GetCost() + currentRecord.costSoFar;
				for (NodeRecord closedRecord : closedList)
				{
					if (m_pGraph->GetNode(conn->GetTo()) == closedRecord.pNode)
					{
						if (closedRecord.costSoFar > gCostCurrentConn)
						{
							closedList.erase(std::remove(closedList.begin(), closedList.end(), closedRecord), closedList.end());
						}
					}
					else
					{
						for (NodeRecord openRecord : openList)
						{
							if (m_pGraph->GetNode(conn->GetTo()) == openRecord.pNode)
							{
								if (openRecord.costSoFar > gCostCurrentConn)
								{
									openList.erase(std::remove(openList.begin(), openList.end(), openRecord), openList.end());
								}
							}
						}
					}
				}
				
				NodeRecord newRecord;
				newRecord.pNode = m_pGraph->GetNode(conn->GetTo());
				newRecord.pConnection = conn;
				newRecord.costSoFar = gCostCurrentConn;
				newRecord.estimatedTotalCost = newRecord.costSoFar + GetHeuristicCost(newRecord.pNode, pGoalNode);
				openList.push_back(newRecord);
			}
			openList.erase(std::remove(openList.begin(), openList.end(), currentRecord), openList.end());
			closedList.push_back(currentRecord);
			if (closedList.size()/6 >= m_pGraph->GetNrOfNodes())
				return path;
		}
		path.push_back(currentRecord.pNode);
		closedList.push_back(currentRecord);
		while(currentRecord.pConnection != nullptr)
		{
			for (auto closedRecord : closedList)
			{
				if (currentRecord.pConnection->GetFrom() == closedRecord.pNode->GetIndex())
				{
					currentRecord = closedRecord;
					break;
				}
			}
			path.push_back(currentRecord.pNode);
			closedList.erase(std::remove(closedList.begin(), closedList.end(), currentRecord), closedList.end());
		}
		std::reverse(path.begin(), path.end());
		return path;
	}

	template <class T_NodeType, class T_ConnectionType>
	float Elite::AStar<T_NodeType, T_ConnectionType>::GetHeuristicCost(T_NodeType* pStartNode, T_NodeType* pEndNode) const
	{
		Vector2 toDestination = m_pGraph->GetNodePos(pEndNode) - m_pGraph->GetNodePos(pStartNode);
		return m_HeuristicFunction(abs(toDestination.x), abs(toDestination.y));
	}
}