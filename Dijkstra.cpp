#include "Dijkstra.h"
#include "BetterPriorityQueue.h"
#include <stdexcept>
#include <map>

//  Time Complexity: O((V + E) * log V), reason: 
// 	Each node is inserted into the priority queue at most once
// 	For each node, we process all outgoing edges
// 	The priority queue rebuild (Update) is not optimal, but acceptable for small to medium graphs
 
int dijkstra(nodekey_t start, nodekey_t end, const Graph* g) {
	if (!g->IsPresent(start) || !g->IsPresent(end)) {
		throw invalid_argument("Start or end node is not in the graph.");
	}

	BetterPriorityQueue pq;
	map<nodekey_t, int> dist;

	// Initialize distances for all nodes
	for (nodekey_t key : g->GetNodes()) {
		BPQNode node;
		node.gnode = key;
		node.pri = (key == start) ? 0 : INT_MAX;
		dist[key] = node.pri;
		pq.push(node);
	}

	while (!pq.empty()) {
		BPQNode current = pq.top();
		pq.pop();

		if (current.visited) continue;

		if (current.gnode == end) {
			return current.pri; // Shortest path found
		}

		// Mark as visited to avoid re-processing
		current.visited = true;

		for (const GraphEdge* edge : g->GetOutwardEdgesFrom(current.gnode)) {
			int newDist = dist[current.gnode] + edge->weight;

			if (newDist < dist[edge->to]) {
				dist[edge->to] = newDist;

				BPQNode next;
				next.gnode = edge->to;
				next.pri = newDist;
				pq.Update(next);  // Update the priority in the queue
			}
		}
	}

	return -1; // If end node is unreachable
}
