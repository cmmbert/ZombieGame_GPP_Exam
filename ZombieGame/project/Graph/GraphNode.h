#pragma once
class GraphNode
{
public:
	GraphNode() = delete;
	GraphNode(int idx);
	int GetIndex() { return m_Index; }
	void SetIndex(int idx) { m_Index = idx; }
private:
	int m_Index;
};

