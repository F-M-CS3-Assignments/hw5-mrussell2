#ifndef BETTER_PRIORITY_QUEUE_H
#define BETTER_PRIORITY_QUEUE_H

#include "Graph.h"
#include <queue>
#include <vector>
#include <string>
#include <climits>

using namespace std;

struct BPQNode {
	int pri = INT_MAX;
	bool visited = false;
	nodekey_t gnode = INVALID_NODE_KEY;

	bool operator<(const BPQNode &other) const {
		return pri < other.pri;
	}

	bool operator>(const BPQNode &other) const {
		return pri > other.pri;
	}

	bool operator==(const BPQNode &other) const {
		return this->gnode == other.gnode;
	}
};

class BetterPriorityQueue : public priority_queue<BPQNode, vector<BPQNode>, greater<BPQNode>> {
public:
	bool Contains(BPQNode d) const;
	bool Update(BPQNode d);
	string ToString() const;
	static string BPQNodeToString(BPQNode n);
};

#endif
