//
//  main.cpp
//  PPD lab2
//
//  Created by Gabriel Goteciuc on 20/10/2019.
//  Copyright © 2019 Gabriel Goteciuc. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <thread>
#include <queue>
#define MAXN 1000
#define MAX_THREADS 2

std::ifstream f("input.in");

int a[MAXN][MAXN], b[MAXN][MAXN], c[MAXN][MAXN];
int n, m, p, r, type;

std::queue<std::pair<int, int>> q;
std::thread threads[MAX_THREADS];

void product(int id) {
    int sum;
    
    for (int i = id; i < n; i += MAX_THREADS){
        for (int j = 0; j < r; ++j) {
            sum = 0;
            for (int k = 0; k < p; ++k) {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }
}

void computeSum(int id) {
    for (int i = id; i < n; i += MAX_THREADS) {
        for (int j = 0; j < m; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}

void worker(int id, int op) {
    if (op == 2) {
        product(id);
    } else {
        computeSum(id);
    }
}

int main() {
    f >> type;
    f >> n >> m >> p >> r;
        
    if (type == 1 && n != p && m != r) {
        return 1;
    }
    
    if (type == 2 && m != p) {
        return 1;
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            f >> a[i][j];
        }
    }
    
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < r; ++j) {
            f >> b[i][j];
        }
    }
    
    for (int i = 0; i < MAX_THREADS; ++i) {
        threads[i] = std::thread(worker, i, type);
    }
    
    for (int i = 0; i < MAX_THREADS; ++i) {
        threads[i].join();
    }
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < r; ++j) {
            std::cout << c[i][j] << " ";
        }
        std::cout << "\n";
    }
    
    return 0;
}
