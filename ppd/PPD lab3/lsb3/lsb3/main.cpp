//
//  main.cpp
//  lsb3
//
//  Created by Gabriel Goteciuc on 28/10/2019.
//  Copyright © 2019 Gabriel Goteciuc. All rights reserved.
//

#include <stdlib.h>
#include <iostream>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <chrono>
#include "ctpl-stl.h"

using namespace std::chrono;

#define MAT_DIM 840

int steps, a[MAT_DIM][MAT_DIM], b[MAT_DIM][MAT_DIM], c[MAT_DIM][MAT_DIM];

void product(int x, int y) {
    int currentX = x, currentY = y;
    for(int i = 0; i < steps; ++i) {
        int sum = 0;
        for (int j = 0; j < MAT_DIM; ++j) {
            sum += a[currentX][j] * b[j][currentY];
        }
        
        c[currentX][currentY] = sum;
        
        currentY++;
        if (currentY == MAT_DIM) {
            currentX++;
            currentY = 0;
        }
    }
}

void computeSum(int x, int y) {
    int currentX = x;
    int currentY = y;
    for (int i = 0; i < steps; i++) {
        c[currentX][currentY] = a[currentX][currentY] + b[currentX][currentY];

        currentY++;

        if (currentY == MAT_DIM) {
            currentY = 0;
            currentX++;
        }
    }
}

double  runThreadPool(int t) {
    int currentX = 0, currentY = 0;
    int cellsPerThread = MAT_DIM * MAT_DIM / t;
    steps = cellsPerThread;
    
    
    for(int i = 0; i < MAT_DIM; ++i) {
        for (int j = 0; j < MAT_DIM; ++j) {
            a[i][j] = 1;
            b[i][j] = 2;
        }
    }
    
    auto start = high_resolution_clock::now();
    
    {
        ctpl::thread_pool p(t);

        for (int i = 0; i < t; i++) {
            p.push([currentX, currentY](int id){product(currentX, currentY);});
            currentX += (currentY + cellsPerThread) / MAT_DIM;
            currentY = (currentY+ cellsPerThread) % MAT_DIM;
        }
    }
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    return duration.count() / (CLOCKS_PER_SEC / 1000);
    
}

double runAsync(int t) {
    int currentX = 0, currentY = 0;
    int cellsPerThread = MAT_DIM * MAT_DIM / t;
    steps = cellsPerThread;
    
    for(int i = 0; i < MAT_DIM; ++i) {
        for (int j = 0; j < MAT_DIM; ++j) {
            a[i][j] = 1;
            b[i][j] = 2;
        }
    }
    
    auto start = high_resolution_clock::now();
    
    {
        std::future<void> a[t];
        for (int i = 0; i < t; i++) {
            a[i] = std::async(computeSum, currentX, currentY);
            
            currentX += (currentY + cellsPerThread) / MAT_DIM;
            currentY = (currentY + cellsPerThread) % MAT_DIM;
        }
    }
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    return duration.count() / (CLOCKS_PER_SEC / 1000);

}

int main(int argc, const char * argv[]) {
    for (int i = 1;  i <= 8; ++i) {
        int s = 0;
        
        for (int j = 0; j < 25; ++j) {
            s += runThreadPool(i);
        }
        std::cout << s / 25 << "\n";
    }
        
    return 0;
}
