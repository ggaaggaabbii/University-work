//
//  main.cpp
//  lab8
//
//  Created by Gabriel Goteciuc on 01/12/2019.
//  Copyright © 2019 Gabriel Goteciuc. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <thread>
#define MAXN 20
int n, m;
std::ifstream f("input.in");

std::vector<int> G[MAXN];
bool check[(1<<MAXN)+10][MAXN];

std::atomic<bool> found;
std::mutex mtx;
std::vector<int> solution;

void initialize() {
    int a, b, c;
    f >> n;
    f >> m;
    while (m--) {
        f >> a >> b >> c;
        G[a].push_back(b);
    }
}

void checkSol(int start, const std::vector<int> &perm) {
    if (std::find(G[0].begin(), G[0].end(), start) == G[0].end()) {
        return;
    }
    if (std::find(G[start].begin(), G[start].end(), perm[0]) == G[start].end()) {
        return;
    }
    for (int i = 0; i < perm.size() - 1; ++i) {
        if (std::find(G[perm[i]].begin(), G[perm[i]].end(), perm[i + 1]) == G[perm[i]].end()) {
            return;
        }
    }
    found = true;
    mtx.lock();
    solution.clear();
    solution.push_back(0);
    solution.push_back(start);
    for (auto it:perm) {
        solution.push_back(it);
    }
    mtx.unlock();
}

void worker(int id) {
    std::vector<int> perm;
    
    for (int i = 1; i < n; ++i) {
        if (i == id) {
            continue;
        }
        perm.push_back(i);
    }
    
    do {
        checkSol(id, perm);
    } while (std::next_permutation(perm.begin(), perm.end()));
}

std::thread threads[MAXN];

void solve() {
    for (int i = 1; i < n; ++i) {
        threads[i] = std::thread(worker, i);
    }
    for (int i = 1; i < n; ++i) {
        threads[i].join();
    }
}

int main(int argc, const char * argv[]) {
    found = false;
    initialize();
    solve();
    if (!found) {
        std::cout << "No cycle\n";
        return 0;
    }
    for (auto it:solution) {
        std::cout << it << " ";
    }
    std::cout << "\n";
    return 0;
}
