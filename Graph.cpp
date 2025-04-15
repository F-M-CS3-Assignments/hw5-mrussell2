
#include "Graph.h"
#include <iostream>
#include <vector>
#include <stdexcept>


using namespace std;



// This method is not part of the Graph class / header on purpose
const GraphEdge* findExistingEdge(nodekey_t gnFrom, nodekey_t gnTo, vector<vector<GraphEdge *>> adjList)
{
	if(adjList.size() == 0)
	{
		return nullptr;
	}


	for(size_t rowIDX = 0; rowIDX < adjList.size(); rowIDX++)
	{
		vector<GraphEdge*> row = adjList.at(rowIDX);
		for(size_t i = 0; i < row.size(); i++)
		{
			GraphEdge *cur = row.at(i);

			// It might make sense for there to be an == operator overload in the GraphEdge struct
			// but adding methods to a struct feels so _wrong_ to me!
			if(cur->from == gnFrom && cur->to == gnTo)
			{
				return cur;
			}
		}
	} 

	return nullptr;
}

// This method is not part of the Graph class / header on purpose
// This should probably be a method in the GraphEdge struct
// but adding methods to a struct feels so _wrong_ to me!
string GraphEdgeToString(const GraphEdge* e)
{
	return "((" + to_string(e->from) + ")->(" + to_string(e->to) + ") w:" + to_string(e->weight) + ")";
}





void Graph::AddNode(nodekey_t key)
{

	if(this->IsPresent(key))
	{
		throw invalid_argument("Duplicate node cannot be added: " + to_string(key));
	}


	nodes.push_back(key);
	vector <GraphEdge*> *newRow = new vector<GraphEdge*>;
	adjList.push_back(*newRow);
	delete newRow; // ?
}




const GraphEdge *Graph::AddEdge(nodekey_t gnFrom, nodekey_t gnTo, unsigned int w)
{

	// The AddEdge method creates new edges.  It does not and should not update / change
	// the weights of existing edges.  findExistingEdge does not check the weight for this reason
	const GraphEdge* dup = findExistingEdge(gnFrom, gnTo, this->adjList);
	if(dup != nullptr)
	{
		throw invalid_argument("Duplicate edge cannot be added: " + GraphEdgeToString(dup));
	}

	if(!this->IsPresent(gnFrom))
	{
		throw invalid_argument("No such node: " + to_string(gnFrom));
	}

	if(!this->IsPresent(gnTo))
	{
		throw invalid_argument("No such node: " + to_string(gnTo));
	}

	GraphEdge *ge = new GraphEdge;

	// TODO:
	// Do stuff here?  IDK what though
	ge->from = gnFrom;
	ge->to = gnTo;
	ge->weight = w;

	// Find the row corresponding to gnFrom and insert the edge there
	for (size_t i = 0; i < nodes.size(); ++i) {
		if (nodes[i] == gnFrom) {
			adjList[i].push_back(ge);
			break;
		}
	}

	const GraphEdge *response = ge; // this helps the compiler go
	return response;
}


bool Graph::IsPresent(nodekey_t key) const
{
	for (size_t i = 0; i < nodes.size(); ++i) {
		if (nodes[i] == key) return true;
	}
	return false;
	// TODO:
	// iterate through this->nodes and look for one that matches key
}




set<const GraphEdge*> Graph::GetOutwardEdgesFrom(nodekey_t node) const 
{
	size_t idx = 0;
	while(idx < this->nodes.size() && (this->nodes.at(idx) != node))
	{
		idx++;
	}
	if(idx == this->nodes.size()){
		throw invalid_argument("No such node: " + to_string(node));
	}



	set<const GraphEdge*> result = set<const GraphEdge*>();
	// TODO:
	// iterate over this->adjList.at(idx); and find nodes that match the given node
	// in their "from" field, put those nodes in result
	for (GraphEdge* edge : adjList[idx]) {
		if (edge->from == node) {
			result.insert(edge);
		}
	}

	return result;
}

 set<nodekey_t> Graph::GetNodes() const 
{
	// TODOL
	// iterate of this->nodes, accumulate into a set<nodekey_t> and return it
	set<nodekey_t> result;
	for (nodekey_t key : nodes) {
		result.insert(key);
	}
	return result;
}


size_t Graph::Order() const 
{
	return nodes.size();
}

size_t Graph::Size() const 
{
	size_t total = 0;
	for(size_t i = 0; i < adjList.size(); i++){
		vector<GraphEdge*> row = adjList.at(i);
		for(size_t j = 0; j < row.size(); j++){
			total++;
		}
	}

	return total;
}



string Graph::NodesToString() const 
{
	if(nodes.size() == 0)
	{
		return "[]";
	}

	string str = "[";
	for(size_t i = 0; i < (nodes.size() - 1); i++)
	{
		str = str + "(" + to_string(nodes.at(i)) + "), ";
	}

	str = str + "(" + to_string(nodes.at(nodes.size()-1)) + ")]";
	return str;
}

string Graph::EdgesToString() const 
{
	if(this->adjList.size() == 0)
	{
		return "[]";
	}

	size_t count = 0;
	string str = "[";
	for(size_t rowIDX = 0; rowIDX < this->adjList.size(); rowIDX++)
	{
		vector<GraphEdge*> row = this->adjList.at(rowIDX);
		for(size_t i = 0; i < row.size(); i++)
		{
			GraphEdge *cur = row.at(i);
			str = str + GraphEdgeToString(cur);

			if(count < (this->Size() - 1)){
				 str = str + ", ";
			}
			count++;
		}
	} 

	str = str +  "]";
	return str;

}



Graph::~Graph() {
	// TODO:
	// Right now the memory leaks are bad, I need to
	// implement something here to fix it
	for (auto &row : adjList) {
		for (GraphEdge* edge : row) {
			delete edge;
		}
		row.clear();
	}
	adjList.clear();
	nodes.clear();
}

