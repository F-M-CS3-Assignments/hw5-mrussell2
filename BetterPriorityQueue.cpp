#include "BetterPriorityQueue.h"
#include <sstream>

// Check if the queue contains the given BPQNode (by node ID)
bool BetterPriorityQueue::Contains(BPQNode d) const {
	for (const BPQNode& cur : this->c) {
		if (cur == d) return true;
	}
	return false;
}

// Update the priority of a BPQNode (if it's lower), rebuild heap
bool BetterPriorityQueue::Update(BPQNode d) {
	bool flag = false;
	vector<BPQNode> items;

	for (size_t i = 0; i < this->c.size(); ++i) {
		BPQNode cur = this->c.at(i);

		if ((cur == d) && (d.pri < cur.pri)) {
			cur.pri = d.pri;
			flag = true;
		}

		items.push_back(cur);
	}

	this->c.clear(); // Clear the binary heap

	for (size_t i = 0; i < items.size(); ++i) {
		this->push(items.at(i)); // Rebuild the heap
	}

	return flag;
}

// Return string like [(1, pri: 0), (2, pri: 1), ...]
string BetterPriorityQueue::ToString() const {
	stringstream ss;
	ss << "[";
	for (size_t i = 0; i < this->c.size(); ++i) {
		ss << BPQNodeToString(this->c[i]);
		if (i != this->c.size() - 1) ss << ", ";
	}
	ss << "]";
	return ss.str();
}

// Static method to represent a BPQNode as a string
string BetterPriorityQueue::BPQNodeToString(BPQNode n) {
	return "(" + to_string(n.gnode) + ", pri: " + to_string(n.pri) + ")";
}
