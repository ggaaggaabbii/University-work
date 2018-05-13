#include "solvefunctions.h"
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

std::unordered_map<int, int> connectedComp(Graph& g)
{
    std::unordered_map<int, int> componentOfVerices;
    int currentComponent = 0;

    for (auto it : g.parseX()) {
        if (componentOfVerices.find(it) == componentOfVerices.end()) {
            componentOfVerices[it] = currentComponent++;
            bfs(g, it, componentOfVerices);
        }
    }

    return componentOfVerices;
}

void bfs(Graph& g, int node, std::unordered_map<int, int>& components)
{
    std::queue<int> q;
    q.push(node);

    while (q.size()) {
        node = q.front();
        q.pop();

        for (auto it : g.parseNOut(node)) {
            if (components.find(it) == components.end()) {
                components[it] = components[node];
                q.push(it);
            }
        }
    }
}

std::unordered_map<int, int> stronglyConnectedComponents(Graph& g)
{
    std::unordered_map<int, int> componentOfVerices;
    std::unordered_map<int, int> Index;
    std::stack<int> s;
    bool onStack[g.getNumberOfVertices()];
    int currentComponent = 0, nextcomp = 0;

    for (auto it : g.parseX()) {
        Index[it] = 0;
        onStack[it] = true;
    }

    for (auto it : g.parseX()) {
        if (!Index[it]) {
            dfs(g, it, componentOfVerices, Index, onStack, currentComponent, s, nextcomp);
        }
    }

    return componentOfVerices;
}

void dfs(Graph& g, int node, std::unordered_map<int, int>& comp, std::unordered_map<int, int>& ind,
         bool* onStack, int& currentComp, std::stack<int>& s, int& nextcomp)
{
    ind[node] = currentComp;
    comp[node] = currentComp;
    onStack[node] = true;
    s.push(node);
    ++currentComp;

    for (auto it : g.parseNOut(node)) {
        if (!ind[it]) {
            dfs(g, it, comp, ind, onStack, currentComp, s, nextcomp);
            comp[node] = std::min(comp[node], comp[it]);
        } else if (onStack[it]) {
            comp[node] = std::min(comp[node], ind[it]);
        }
    }

    if (ind[node] == comp[node]) {
        int y;

        do {
            y = s.top();
            s.pop();
            comp[y] = nextcomp;
            onStack[y] = false;
        } while (y != node);

        ++nextcomp;
    }
}


std::vector<std::vector<int> > biconnectedComponents(Graph& g)
{
    std::vector<std::vector<int> >result;
    std::stack<std::pair<int, int> >s;
    std::unordered_map<int, int>niv, low;
    bool viz[g.getNumberOfVertices() + 2];

    for (int i = 0; i <= g.getNumberOfVertices(); ++i) {
        viz[i] = false;
    }

    for (int i = 0; i < g.getNumberOfVertices(); ++i) {
        if (!viz[i]) {
            dfs2(g, i, 0, viz, niv, low, s, result);
        }
    }

    { return result; }
}

void dfs2(Graph& g, int node, int lvl, bool* viz, std::unordered_map<int, int>& niv,
          std::unordered_map<int, int>& low, std::stack<std::pair<int, int> >& s,
          std::vector<std::vector<int> >& rez)
{
    niv[node] = low[node] = lvl;
    viz[node] = true;

    for (auto it : g.parseNOut(node)) {
        if (!viz[it]) {
            s.push({node, it});
            dfs2(g, it, lvl + 1, viz, niv, low, s, rez);
            low[node] = std::min(low[node], low[it]);

            if (low[it] >= niv[node]) {
                int a, b;
                rez.push_back(std::vector<int>());

                do {
                    a = s.top().first;
                    b  = s.top().second;
                    s.pop();
                    rez.back().push_back(b);
                } while (a != node || b != it);

                rez.back().push_back(node);
            }
        } else {
            low[node] = std::min(low[node], niv[it]);
        }
    }
}

std::vector<int> getNextConf(int node)
{
    std::vector<int> r;
    std::vector<int> sameAsBoat;

    for (int i = 1; i <= 3; ++i) {
        if ((node & (1 << i) >> i) == (node & 1)) {
            sameAsBoat.push_back(i);
        }
    }

    for (auto it : sameAsBoat) {
        r.push_back(node ^ (1 << it) ^ 1);
    }

    r.push_back(node ^ 1);
    return r;
}

bool valid(int node)
{
    std::vector<int> ones, zeros;

    for (int i = 0; i < 4; ++i) {
        if ((node & 1)) {
            ones.push_back(i);
        } else {
            zeros.push_back(i);
        }

        node >>= 1;
    }

    if (std::find(zeros.begin(), zeros.end(), 3) != zeros.end() &&
            std::find(zeros.begin(), zeros.end(), 2) != zeros.end() &&
            std::find(ones.begin(), ones.end(), 0) != ones.end()) {
        return false;
    }

    if (std::find(zeros.begin(), zeros.end(), 2) != zeros.end() &&
            std::find(zeros.begin(), zeros.end(), 1) != zeros.end() &&
            std::find(ones.begin(), ones.end(), 0) != ones.end()) {
        return false;
    }

    if (std::find(ones.begin(), ones.end(), 3) != ones.end() &&
            std::find(ones.begin(), ones.end(), 2) != ones.end() &&
            std::find(zeros.begin(), zeros.end(), 0) != zeros.end()) {
        return false;
    }

    if (std::find(ones.begin(), ones.end(), 2) != ones.end() &&
            std::find(ones.begin(), ones.end(), 1) != ones.end() &&
            std::find(zeros.begin(), zeros.end(), 0) != zeros.end()) {
        return false;
    }

    return true;
}

std::vector<int> wolfGoatCabbageProblem()
{
    Graph g;
    g.addVertex(0);
    int node;
    std::queue<int> q;
    std::vector<int> result;
    bool viz[(1 << 4)];
    int father[(1 << 4)];
    father[0] = -1;
    q.push(0);

    for (int i = 0; i < (1 << 4); ++i) {
        viz[i] = false;
    }

    while (q.size()) {
        node = q.front();
        viz[node] = true;
        q.pop();

        for (auto it : getNextConf(node)) {
            if (!viz[it] && valid(it)) {
                father[it] = node;
                g.addVertex(it);
                g.addEdge(it, node);
                g.addEdge(node, it);
                q.push(it);
            }
        }
    }

    node = 15;

    while (father[node] != -1) {
        result.push_back(node);
        node = father[node];
    }

    result.push_back(0);
    std::reverse(result.begin(), result.end());
    return result;
}

bool solvable(configuration conf)
{
    std::vector<short> v;
    int sum = 0, posX = 0;

    for (short i = 0; i < 4; ++i) {
        for (short j = 0; j < 4; ++j) {
            v.push_back(conf[i][j]);

            if (conf[i][j] == 0) {
                posX = i;
                v.pop_back();
            }
        }
    }

    for (short i = 0 ; i < 15; ++i) {
        for (short j = i + 1; j < 15; ++j) {
            if (v[i] > v[j])
            { ++sum; }
        }
    }

    if ((posX == 0 || posX == 2) && (sum & 1))
    { return true; }

    if ((posX == 1 || posX == 3) && (!(sum & 1)))
    { return true; }

    return false;
}

int heuristic(configuration c)
{
    short row[] = {3, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3};
    short col[] = {3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2};
    short r = 0;

    for (short i = 0; i < 4; i++) {
        for (short j = 0; j < 4; j++) {
            if (c[i][j] != 0)
            { r += abs(row[c[i][j]] - i) + abs(col[c[i][j]] - j); }
        }
    }

    return r;
}

void buildSol(configuration in, configuration fin,
              std::unordered_map<unsigned long long, unsigned long long>& fathers,
              std::vector<configuration>& result)
{
    while (!(fin == in)) {
        result.push_back(fin);
        fin = configuration{fathers[fin.getHash()]};
    }

    result.push_back(in);
    std::reverse(result.begin(), result.end());
}

std::vector<configuration> solve15Puzzle(configuration initialConfiguration)
{
    //instead of unsigned long long, __int128 should be used for proper hashing, but we run out of memory faster
    //that's why i used unsigned long long, just for demonstration purposes
    std::vector<configuration>result;
    std::unordered_map<unsigned long long, bool>viz;
    std::unordered_map<unsigned long long, unsigned long long> father;
    std::priority_queue<std::pair<unsigned long long, unsigned long long> >PQ;
    std::unordered_map<unsigned long long, unsigned long long>cost;
    configuration finalState{"final"};

    if (!solvable(initialConfiguration)) {
        throw std::string{"The puzzle is unsolvable!"};
    }

    cost[initialConfiguration.getHash()] = 0;
    PQ.push({-heuristic(initialConfiguration), initialConfiguration.getHash()});

    while (PQ.size()) {
        auto node = configuration{PQ.top().second};
        viz[node.getHash()] = true;
        PQ.pop();

        if (node == finalState) {
            buildSol(initialConfiguration, finalState, father, result);
            break;
        }

        for (auto it : node.neighbours()) {
            if (viz.find(it.getHash()) == viz.end() && (cost.find(it.getHash()) == cost.end() ||
                                                        cost[node.getHash()] + 1 < cost[it.getHash()])) {
                father[it.getHash()] = node.getHash();
                cost[it.getHash()] = cost[node.getHash()] + 1;
                PQ.push(std::make_pair(-(cost[it.getHash()] + heuristic(it)), it.getHash()));
            }
        }
    }

    return result;
}
