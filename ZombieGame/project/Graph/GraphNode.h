#pragma once
class GraphNode
{
public:
	GraphNode() = delete;
	GraphNode(int idx);
	int GetIndex() { return m_Index; }
	void SetIndex(int idx) { m_Index = idx; }

	void SetDescription(const std::string& desc) { m_Description = desc; }
private:
	int m_Index;
	std::string m_Description;  //For debug purposes
};

