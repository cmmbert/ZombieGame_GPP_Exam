#include "stdafx.h"
#include "Graph.h"

Graph::Graph()
{
	m_NextValidNodeIdx = 0;
}

int Graph::AddNode(const std::string& description)
{
	auto newNode = new GraphNode(m_NextValidNodeIdx);
	newNode->SetDescription(description);
	m_NodeVector.push_back(newNode);
	++m_NextValidNodeIdx;
	return newNode->GetIndex();
}

void Graph::AddConnection(int FromNodeIdx, int ToNodeIdx, float cost)
{
	auto newCon = new GraphConnection();
	newCon->SetFromIdx(FromNodeIdx);
	newCon->SetToIdx(ToNodeIdx);
	newCon->SetCost(cost);
	m_ConnectionVector.push_back(newCon);
}

std::vector<GraphConnection*> Graph::GetAllConnectionsToNode(int nodeIdx)
{
	std::vector<GraphConnection*> conns;
	for (GraphConnection* conn : m_ConnectionVector)
	{
		if (conn->GetToIdx() == nodeIdx) conns.push_back(conn);
	}
	return conns;
}

std::vector<GraphConnection*> Graph::GetAllConnectionsFromNode(int nodeIdx)
{
	std::vector<GraphConnection*> conns;
	for (GraphConnection* conn : m_ConnectionVector)
	{
		if (conn->GetFromIdx() == nodeIdx) conns.push_back(conn);
	}
	return conns;
}


GraphNode* Graph::GetNodeByIdx(int idx)
{
	for (auto* node : m_NodeVector)
	{
		if (node->GetIndex() == idx) return node;
	}
	assert(false); //should never reach this "GetNodeByIdx: invalid node idx"
	return nullptr;
}

void Graph::Reset()
{
	m_NextValidNodeIdx = 0;
	for (auto element : m_NodeVector)
	{
		delete element;
		element = nullptr;
	}
	for (auto element : m_ConnectionVector)
	{
		delete element;
		element = nullptr;
	}
	m_NodeVector.clear();
	m_ConnectionVector.clear();
}
