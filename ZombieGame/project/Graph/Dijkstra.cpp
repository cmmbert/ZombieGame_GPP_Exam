#include "stdafx.h"
#include "Dijkstra.h"

std::vector<GraphNode*> Dijkstra::FindPath(Graph* pGraph, GraphNode* pStartNode, GraphNode* pGoalNode)
{
	vector<GraphNode*> path;
	vector<NodeRecord*> openList;
	for(auto node : pGraph->GetAllConnectionsFromNode(pStartNode->GetIndex()))
	{
		NodeRecord* record = new NodeRecord();
		record->pNode = pGraph->GetNodeByIdx(node->GetToIdx());
		record->previousRecord = nullptr;
		openList.push_back(record);
	}


	vector<NodeRecord*> closedList;
	auto lastRecord = new NodeRecord();

	int loopCounter = 0;
	int maxLoops = 1000;
	while(!openList.empty())
	{
		++loopCounter;
		if (loopCounter >= maxLoops)
			break;
		bool endNodeFound = false;
		for (size_t i = 0; i < openList.size(); ++i)
		{
			auto currentRecord = lastRecord = openList[i];

			if (currentRecord->pNode == pGoalNode)
			{
				endNodeFound = true;
				break; //End node found
			}
			auto currentConns = pGraph->GetAllConnectionsFromNode(currentRecord->pNode->GetIndex());
			//If node has no connections left, remove it
			if(currentConns.empty())
			{
				openList.erase(std::remove(openList.begin(), openList.end(), currentRecord), openList.end());
				closedList.push_back(currentRecord);
				continue;
			}

			for(auto conn : currentConns)
			{
				auto toNode = pGraph->GetNodeByIdx(conn->GetToIdx());

				bool nodeAlreadyAdded = false;
				for(auto* existingRecord : openList)
				{
					if (existingRecord->pNode == toNode)
					{
						nodeAlreadyAdded = true;
						break;
					}
				}
				if (nodeAlreadyAdded) continue;

				auto* newRecord = new NodeRecord();
				newRecord->pNode = toNode;
				newRecord->costSoFar += conn->GetCost();
				newRecord->previousRecord = currentRecord;
				openList.push_back(newRecord);
			}
			//openList.erase(std::remove(openList.begin(), openList.end(), currentRecord), openList.end());

		}
		if (endNodeFound) 
			break;
	}


	NodeRecord* currentRecord = lastRecord;
	while (true)
	{
		path.push_back(currentRecord->pNode);
		if (currentRecord->previousRecord == nullptr)
			break;
		currentRecord = currentRecord->previousRecord;
	} 

	path.push_back(pStartNode);

	std::reverse(path.begin(), path.end());
	return path;
}
