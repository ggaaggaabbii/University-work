//
//  main.cpp
//  lab7_2
//
//  Created by Gabriel Goteciuc on 01/12/2019.
//  Copyright © 2019 Gabriel Goteciuc. All rights reserved.
//

#include <iostream>
#include <thread>
#include "ProducerComsumerQueue.h"
#define MAXN 2048
#define LENGTH 1000

int numbers[MAXN][LENGTH];
ProducerConsumerQueue<int> pcq[MAXN];

void handleLeaf(int id) {
    int a, b, t = 0;
    pcq[id + MAXN / 2 - 1].enqueue(LENGTH);
    for (int i = 0; i < LENGTH; ++i) {
        a = numbers[2 * id][i];
        b = numbers[2 * id + 1][i];
        pcq[id + MAXN / 2 - 1].enqueue((a + b + t) % 10);
        t = (a + b + t) / 10;
    }
    pcq[id + MAXN / 2 - 1].enqueue(t);
}

void handleNonLeaf(int id, int rez[], int &t) {
    int a, b, len;
    pcq[2 * id + 1].dequeue(len);
    pcq[2 * id + 2].dequeue(len);
    ++len;
    pcq[id].enqueue(len);

    for (int i = 0; i < len; ++i) {
        pcq[2 * id + 1].dequeue(a);
        pcq[2 * id + 2].dequeue(b);
        pcq[id].enqueue((a + b + t) % 10);
        if (id == 0) {
            rez[i] = (a + b + t) % 10;
        }
        t = (a + b + t) / 10;
    }
    pcq[id].enqueue(t);
}

void printResult(int rez[], int t) {
    int i = LENGTH + MAXN - 1;
    for (; i >= 0; --i) {
        if (rez[i] != 0) {
            break;
        }
    }
    for (; i >= 0; --i) {
        std::cout << rez[i];
    }
    std::cout << "\n";
}

void worker(int id) {
    int *rez = new int[id == 0 ? (LENGTH + MAXN) : 1];
    for (int i = 0; i < (id == 0 ? (LENGTH + MAXN) : 1); ++i) {
        rez[i] = 0;
    }
    int t = 0;
    
    if (id >= MAXN / 2 - 1) {
        handleLeaf(id - MAXN / 2 + 1);
    } else {
        handleNonLeaf(id, rez, t);
    }
    
    if (id == 0) {
        printResult(rez, t);
    }
    
    delete[] rez;
}

std::thread threads[MAXN];

int main(int argc, const char * argv[]) {
    
    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j < LENGTH; ++j) {
            numbers[i][j] = 1;
        }
    }
   
    for (int i = 0; i < MAXN; ++i) {
        threads[i] = std::thread(worker, i);
    }
    for (int i = 0; i < MAXN; ++i) {
        threads[i].join();
    }
    
    return 0;
}
