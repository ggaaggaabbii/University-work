#include <bits/stdc++.h>
#include "graph.h"
#define pb push_back
#define mp make_pair
#define sec second
#define fir first
#define INF 1000000000

using namespace std;

long long totalCost = 0;

int getRoot(vector<int>& v, int node) {
	int root = node;

	while (node != -1) {
		root = node;
		node = v[node];
	}

	return root;
}

void setNewRoot(vector<int>&v, int root, int node) {
	int newNode;

	while (node != root && node != -1) {
		newNode = v[node];
		v[node] = root;
		node = newNode;
	}
}

bool sameComp(vector<int>& v, int node1, int node2) {
	int root1 = getRoot(v, node1);
	int root2 = getRoot(v, node2);

	setNewRoot(v, root1, node1);
	setNewRoot(v, root1, node2);

	return root1 == root2;
}

void kruskal(Graph &g, Graph &resultAPM, vector<pair<int, pair<int, int> > > v) {
	vector<int> comp;
	for (int i = 0; i < g.getNumberOfVertices(); ++i) {
		comp.push_back(-1);
	}

	for (auto it : v) {
		if (sameComp(comp, it.sec.fir, it.sec.sec)) {
			continue;
		}
		resultAPM.addEdge(it.sec.fir, it.sec.sec, it.fir);
		resultAPM.addEdge(it.sec.sec, it.sec.fir, it.fir);
	}
}

void dfs(int node, Graph& g, unordered_map<int, int>& lvl, int &maxLvl, int &maxLvlNode) {
	for (auto it : g.parseNOut(node)) {
		if (lvl.find(it) == lvl.end()) {
			lvl[it] = lvl[node] + 1;
			if (lvl[it] > maxLvl) {
				maxLvl = lvl[it];
				maxLvlNode = it;
			}
			dfs(it, g, lvl, maxLvl, maxLvlNode);
		}
	}
}

pair<int, pair<int, int> >getLongestPath(Graph& g) {
	unordered_map<int, int> lvl1;
	unordered_map<int, int> lvl2;
	int maxLvl = 0;
	int head;
	for (auto it : g.parseX()) {
		if (lvl1.find(it) == lvl1.end()) {
			lvl1[it] = 1;
			dfs(it, g, lvl1, maxLvl, head);
		}
	}
	maxLvl = 0;
	int tail = head;
	lvl2[tail] = 1;
	dfs(tail, g, lvl2, maxLvl, head);
	return pair<int, pair<int, int> > {maxLvl, {head, tail}};
}

void dfs2(int node, Graph& g, unordered_map<int, int> &viz) {
	cout << node << "->";
	viz[node] = 1;
	for (auto it : g.parseNOut(node)) {
		if (viz.find(it) == viz.end()) {
			totalCost += g.getCost(node, it);
			dfs2(it, g, viz);
		}
	}
}

void printCycle(Graph& g, int head, int tail) {
	unordered_map<int, int>viz;
	cout << tail << "\n";
	dfs2(head, g, viz);
	cout << head << "\n";
}

void dfs3(int node, Graph& g, unordered_map<int, int>&viz, int head) {

	cout << node << "->";
	viz[node] = 1;
	for (auto it : g.parseNOut(node)) {
		if (viz.find(it) == viz.end()) {
			totalCost += 2 * g.getCost(node, it);
			dfs3(it, g, viz, head);
			cout << node;
			if (node == head && (int)viz.size() == g.getNumberOfVertices()) {
				return;
			}
			cout << "->";
		}
	}
}

void printAPM(Graph& g) {
	unordered_map<int, int>viz;
	for (auto it : g.parseX()) {
		if (viz.find(it) == viz.end()) {
			dfs3(it, g, viz, it);
		}
	}
	cout << "\n";
}

int main(int ac, char** av) {
	if (ac < 2) {
		cout << "Usage: .exe [file]\n";
		return 0;
	}

	ifstream f(av[1]);

	int n, m, x, y, c;
	f >> n >> m;
	Graph g{n};
	Graph resultAPM{n};
	vector<pair<int, pair<int, int> > > v;

	while (m--) {
		f >> x >> y >> c;
		g.addEdge(x, y, c);
		g.addEdge(y, x, c);
		v.pb(mp(c, mp(x, y)));
	}

	sort(v.begin(), v.end());

	kruskal(g, resultAPM, v);
	pair<int, pair<int, int> >cycle = getLongestPath(resultAPM);
	if (cycle.fir == n && g.isEdge(cycle.sec.fir, cycle.sec.sec) != -1) {
		resultAPM.addEdge(cycle.sec.fir, cycle.sec.sec,
		                  g.getCost(cycle.sec.fir, cycle.sec.sec));
		printCycle(resultAPM, cycle.sec.fir, cycle.sec.sec);
		totalCost += g.getCost(cycle.sec.fir, cycle.sec.sec);
	} else {
		printAPM(resultAPM);
	}
	cout << totalCost << "\n";
	f.close();
	return 0;
}