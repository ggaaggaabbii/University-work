//
//  main.cpp
//  lab4
//
//  Created by Gabriel Goteciuc on 03/11/2019.
//  Copyright © 2019 Gabriel Goteciuc. All rights reserved.
//

#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include "ProducerConsumerQueue.h"

#define MAT_SIZE 100
#define THREAD_NUMBER 8
int a[MAT_SIZE][MAT_SIZE], b[MAT_SIZE][MAT_SIZE], c[MAT_SIZE][MAT_SIZE];
int d[MAT_SIZE][MAT_SIZE], e[MAT_SIZE][MAT_SIZE];

ProducerConsumerQueue<std::pair<int, int>> prod1Q, prod2Q;

int visitedLines[MAT_SIZE];
std::mutex mtx;

void product1(const std::pair<int, int> &currentPosition) {
    int s = 0;
    for (int i = 0; i < MAT_SIZE; ++i) {
        s += a[currentPosition.first][i] * b[i][currentPosition.second];
    }
    c[currentPosition.first][currentPosition.second] = s;
    
}

void product2(const std::pair<int, int> &currentPosition) {
    int s = 0;
    for (int i = 0; i < MAT_SIZE; ++i) {
        s += c[currentPosition.first][i] * d[i][currentPosition.second];
    }
    e[currentPosition.first][currentPosition.second] = s;
}

bool done() {
    int s = 0;
    mtx.lock();
    for (int i = 0; i < MAT_SIZE; ++i) {
        s += visitedLines[i];
    }
    mtx.unlock();
    return s == (MAT_SIZE * MAT_SIZE);
}

void prod1Worker() {
    std::pair<int, int> currentPosition;
    while (!prod1Q.dequeue(currentPosition)) {
        product1(currentPosition);
        mtx.lock();
        ++visitedLines[currentPosition.first];
        if (visitedLines[currentPosition.first] == MAT_SIZE) {
            mtx.unlock();
            for (int i = 0; i < MAT_SIZE; ++i) {
                prod2Q.enqueue(std::make_pair(currentPosition.first, i));
            }
        } else {
            mtx.unlock();
        }
    }
    
    if (done()) {
        prod2Q.close();
    }
}

void prod2Worker() {
    std::pair<int, int> currentPosition;
    while (!prod2Q.dequeue(currentPosition)) {
        product2(currentPosition);
    }
}

std::thread threads[THREAD_NUMBER];

int main() {
    for (int i = 0; i < MAT_SIZE; ++i) {
        for (int j = 0; j < MAT_SIZE; ++j) {
            a[i][j] = b[i][j] = d[i][j] = 1;
        }
    }
    
    for (int i = 0; i < THREAD_NUMBER / 2; ++i) {
        threads[i] = std::thread(prod1Worker);
    }
    for (int i = THREAD_NUMBER / 2; i < THREAD_NUMBER; ++i) {
        threads[i] = std::thread(prod2Worker);
    }
    
    for (int i = 0; i < MAT_SIZE; ++i) {
        for (int j = 0; j < MAT_SIZE; ++j) {
            prod1Q.enqueue(std::make_pair(i, j));
        }
    }
    prod1Q.close();
    
    for (int i = 0; i < THREAD_NUMBER; ++i) {
        threads[i].join();
    }
    
    for (int i = 0; i < MAT_SIZE; ++i) {
        for (int j = 0; j < MAT_SIZE; ++j) {
            std::cout << e[i][j] << " ";
        }
        std::cout << "\n";
    }
    
    return 0;
}
