#include "solver.h"

bool checkDag(int node, Graph& g, std::unordered_map<int, int>& viz,
              std::unordered_map<int, int>& onPath)
{
    viz[node] = 1;
    onPath[node] = 1;

    for (auto it : g.parseNOut(node)) {
        if (viz.find(it) == viz.end()) {
            if (!checkDag(it, g, viz, onPath))
            { return false; }
        }

        if (onPath.find(it) != onPath.end())
        { return false; }
    }

    onPath.erase(node);
    return true;
}

bool isDAG(Graph& g)
{
    std::unordered_map<int, int> viz;
    std::unordered_map<int, int> onPath;

    for (auto it : g.parseX()) {
        if (viz.find(it) == viz.end()) {
            if (!checkDag(it, g, viz, onPath))
            { return false; }
        }
    }

    return true;
}

void dfs(int node, Graph& g, std::unordered_map<int, int>& viz, std::vector<int>& tSort)
{
    viz[node] = 1;

    for (auto it : g.parseNOut(node)) {
        if (viz.find(it) == viz.end()) {
            dfs(it, g, viz, tSort);
        }
    }

    tSort.push_back(node);
}

std::vector<int> topSort(Graph& g)
{
    if (!isDAG(g)) {
        throw std::string{"Not a DAG\n"};
    }

    std::unordered_map<int, int>viz;
    std::vector<int> tSort;

    for (auto it : g.parseX()) {
        if (viz.find(it) == viz.end()) {
            dfs(it, g, viz, tSort);
        }
    }

    std::reverse(tSort.begin(), tSort.end());
    return tSort;
}

std::unordered_map<std::string, std::unordered_map<int, int> > scheduler(Graph& g,
                                                                         std::unordered_map<int, int>& duration)
{
    std::unordered_map<int, int> earliest;
    std::unordered_map<int, int> latest;
    std::vector<int> tops = topSort(g);
    int maxT = 0;

    for (auto it : tops) {
        earliest[it] = 0;

        for (auto y : g.parseNIn(it)) {
            earliest[it] = std::max(earliest[it], earliest[y] + duration[y]);
        }

        maxT = std::max(maxT, earliest[it] + duration[it]);
    }

    std::reverse(tops.begin(), tops.end());

    for (auto it : tops) {
        latest[it] = maxT - duration[it];

        for (auto y : g.parseNOut(it)) {
            latest[it] = std::min(latest[it], latest[y] - duration[it]);
        }
    }

    std::unordered_map<std::string, std::unordered_map<int, int>>result;
    result["Earliest Start:"] = earliest;
    result["Latest Start:"] = latest;
    return result;
}
std::vector<int> getCritic(std::unordered_map < std::string, std::unordered_map<int, int>>& s,
                           Graph& g)
{
    std::vector<int> critical;

    for (auto it : g.parseX()) {
        if (s["Earliest Start:"][it] == s["Latest Start:"][it]) {
            critical.push_back(it);
        }
    }

    return critical;
}

int nOPaths(Graph& g, int source, int dest)
{
    if (!isDAG(g)) {
        throw std::string{"Not a DAG\n"};
    }

    std::vector<int> tops = topSort(g);
    std::unordered_map<int, int> dp;

    for (auto it : tops) {
        if (it == source) {
            dp[it] = 1;

        } else {
            dp[it] = 0;
        }

        for (auto x : g.parseNIn(it)) {
            dp[it] += dp[x];
        }
    }

    return dp[dest];
}

int nOMinPaths(Graph& g, int source, int dest)
{
    if (!isDAG(g)) {
        throw std::string{"Not a DAG\n"};
    }

    std::vector<int> tops = topSort(g);
    std::unordered_map<int, int> dp;
    std::unordered_map<int, int> cost;

    for (auto it : tops) {
        if (it == source) {
            dp[it] = 1;
            cost[it] = 0;

        } else {
            dp[it] = 0;
            cost[it] = INF;
        }

        for (auto x : g.parseNIn(it)) {
            if (cost[x] + g.getCost(x, it) < cost[it]) {
                cost[it] = cost[x] + g.getCost(x, it);
                dp[it] = dp[x];

            } else if (cost[x] + g.getCost(x, it) == cost[it]) {
                dp[it] += dp[x];
            }
        }
    }

    return dp[dest];
}

void buildTreeFromPrePost(Graph& g, std::vector<int>& pre, std::vector<int>& post)
{
    std::vector<int>indPre;
    std::vector<int>indPost;
    std::unordered_map<int, int>father;
    int currentNode = pre[0];

    for (int i = 0; i < g.getNumberOfVertices(); ++i) {
        indPre.push_back(0);
        indPost.push_back(0);
    }

    for (int i = 0; i < g.getNumberOfVertices(); ++i) {
        indPre[pre[i]] = i;
        indPost[post[i]] = i;
    }

    for (int i = 1; i < g.getNumberOfVertices(); ++i) {
        while (indPost[pre[i]] > indPost[currentNode]) {
            currentNode = father[currentNode];
        }

        g.addEdge(currentNode, pre[i], 0);
        father[pre[i]] = currentNode;
        currentNode = pre[i];
    }
}
