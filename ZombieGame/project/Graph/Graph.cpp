#include "stdafx.h"
#include "Graph.h"

int Graph::AddNode()
{
	m_NodeVector.push_back(new GraphNode(m_NextValidNodeIdx));
	++m_NextValidNodeIdx;
	return m_NextValidNodeIdx - 1;
}

void Graph::AddConnection(int FromNodeIdx, int ToNodeIdx, float cost)
{
	auto newCon = new GraphConnection();
	newCon->SetFromIdx(ToNodeIdx);
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
