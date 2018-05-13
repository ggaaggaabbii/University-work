#include "solvefunction.h"
#define INF 1000000000

void checkForNegCic(int dest, std::unordered_map<int, int>& father)
{
    std::unordered_map<int, int> viz;
    int x = dest;

    while (x != -1) {
        if (viz.find(x) != viz.end()) {
            std::string s = "Negative cicle detected";
            throw s;
        }

        viz[x] = 1;
        x = father[x];
    }
}

int lowestLengthWalk(Graph& g, int source, int dest)
{
    int n = g.getNumberOfVertices();
    std::unordered_map<int, int> dp[n + 1];
    std::unordered_map<int, int> father;


    for (auto it : g.parseX()) {
        dp[0][it] = INF;
    }

    dp[0][source] = 0;
    father[source] = -1;

    for (int i = 1; i <= n; ++i) {
        for (auto x : g.parseX()) {
            dp[i][x] = dp[i - 1][x];

            for (auto y : g.parseNIn(x)) {

                if (dp[i - 1][y] + std::get<2>(g.getEdge(g.isEdge(y, x))) < dp[i][x]) {
                    dp[i][x] = dp[i - 1][y] + std::get<2>(g.getEdge(g.isEdge(y, x)));
                    father[x] = y;
                }
            }

            if (father.find(x) != father.end()) {
                checkForNegCic(x, father);
            }
        }
    }

    if (father.find(dest) == father.end()) {
        std::string s = "No walk found";
        throw s;
    }

    return dp[n - 1][dest];
}

int numberOfDistinctMinimumCostWalks(Graph& g, int source, int dest)
{
    std::unordered_map<int, int> cost;
    std::unordered_map<int, int> distinctWalks;
    std::priority_queue<std::pair<int, int> > PQ;
    cost[source] = 0;
    distinctWalks[source] = 1;
    PQ.push({0, source});

    while (PQ.size()) {
        int node = PQ.top().second;
        PQ.pop();

        for (auto it : g.parseNOut(node)) {
            if (cost.find(it) == cost.end() ||
                    cost[node] + std::get<2>(g.getEdge(g.isEdge(node, it))) < cost[it]) {
                cost[it] = cost[node] + std::get<2>(g.getEdge(g.isEdge(node, it)));
                distinctWalks[it] = distinctWalks[node];
                PQ.push({ -cost[it], it});

            } else if (cost[node] + std::get<2>(g.getEdge(g.isEdge(node, it))) == cost[it]) {
                distinctWalks[it] += distinctWalks[node];
                PQ.push({ -cost[it], it});
            }
        }
    }

    if (distinctWalks.find(dest) == distinctWalks.end()) {
        std::string s = "No walk found";
        throw s;
    }

    return distinctWalks[dest];
}

void dfs(Graph& g, int node, std::vector<int>& topSort, std::unordered_map<int, int>& viz)
{
    viz[node] = 1;

    for (auto it : g.parseNOut(node)) {
        if (!viz[it]) {
            dfs(g, it, topSort, viz);
        }
    }

    topSort.push_back(node);
}

int numberOfDistinctWalks(Graph& g, int source, int dest)
{
    std::vector<int> topSort;
    std::unordered_map<int, int> distWalks;
    std::unordered_map<int, int> viz;

    for (auto it : g.parseX()) {
        distWalks[it] = 0;

        if (viz.find(it) == viz.end()) {
            dfs(g, it, topSort, viz);
        }
    }

    std::reverse(topSort.begin(), topSort.end());
    distWalks[source] = 1;

    for (auto x : topSort) {
        for (auto y : g.parseNIn(x)) {
            distWalks[x] += distWalks[y];
        }
    }

    return distWalks[dest];
}

std::vector<std::pair<int, int> > getNextConf(int node, std::vector<int>& people)
{
    std::vector<int>zero, one;
    int aux = node;

    for (int i = 0; i < (int)(people.size()); ++i) {
        if (aux & 1) {
            one.push_back(i);

        } else {
            zero.push_back(i);
        }

        aux /= 2;
    }

    std::vector<std::pair<int, int> >res;

    if (aux == 1) {
        aux = node;
        aux ^= (1 << (people.size()));

        for (auto it : one) {
            aux ^= (1 << it);
            res.push_back({aux, people[it]});
            aux ^= (1 << it);
        }

        for (int i = 0; i < (int)(one.size()); ++i) {
            for (int j = i + 1; j < (int)(one.size()); ++j) {
                aux ^= (1 << one[i]);
                aux ^= (1 << one[j]);
                res.push_back({aux, std::max(people[one[i]], people[one[j]])});
                aux ^= (1 << one[j]);
                aux ^= (1 << one[i]);
            }
        }

    } else {
        aux = node;
        aux ^= (1 << (people.size()));

        for (auto it : zero) {
            aux ^= (1 << it);
            res.push_back({aux, people[it]});
            aux ^= (1 << it);
        }

        for (int i = 0; i < (int)(zero.size()); ++i) {
            for (int j = i + 1; j < (int)(zero.size()); ++j) {
                aux ^= (1 << zero[i]);
                aux ^= (1 << zero[j]);
                res.push_back({aux, std::max(people[zero[i]], people[zero[j]])});
                aux ^= (1 << zero[j]);
                aux ^= (1 << zero[i]);
            }
        }
    }

    return res;
}

void printConf(int node, int size)
{
    std::vector<int>zero, one;

    for (int i = 0; i < size; ++i) {
        if (node & 1) {
            one.push_back(i);

        } else {
            zero.push_back(i);
        }

        node /= 2;
    }

    for (auto it : zero) {
        std::cout << it << " ";
    }

    if (node == 1) {
        std::cout << " - T ";

    } else {
        std::cout << "T - ";
    }

    for (auto it : one) {
        std::cout << it << " ";
    }

    std::cout << "\n";
}

void printSol(std::unordered_map<int, int>& father, int conf, int size)
{
    if (conf == 0) {
        printConf(conf, size);
        return;
    }

    printSol(father, father[conf], size);
    printConf(conf, size);
}

void bridgeAndTorchProblem(std::vector<int>& people)
{
    std::unordered_map<int, int>cost;
    std::unordered_map<int, int>father;
    std::priority_queue<std::pair<int, int> >PQ;
    int finalConf = (1 << (people.size() + 1)) - 1;
    cost[0] = 0;
    PQ.push({0, 0});

    while (PQ.size()) {
        int node = PQ.top().second;
        PQ.pop();
        //std::cout << node << ":\n";

        if (node == finalConf)
        { break; }

        for (auto it : getNextConf(node, people)) {
            //std::cout << it.first << " ";

            if (cost.find(it.first) == cost.end() || cost[node] + it.second < cost[it.first]) {
                cost[it.first] = cost[node] + it.second;
                father[it.first] = node;
                PQ.push({ -cost[it.first], it.first});
            }
        }

        //std::cout << "\n";
    }

    printSol(father, finalConf, people.size());
}
