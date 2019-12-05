//
//  main.cpp
//  lab7
//
//  Created by Gabriel Goteciuc on 24/11/2019.
//  Copyright © 2019 Gabriel Goteciuc. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <thread>
#include <queue>
#include "ProducerComsumerQueue.h"

#define MAXN 10
#define NO_THREADS (std::min((MAXN / log2(MAXN) + 1), 1000))
#define NO_TASKS (MAXN / NO_THREADS + 1)

int log2(int n) {
    int i;
    for (i = 0; (1 << i) <= n; ++i) { }
    return i;
}

int s[MAXN];

void solve() {
    for (int i = 1; i < MAXN; ++i) {
        s[i] += s[i - 1];
    }
}

int main() {
    bool runParale = true;
    
    for (int i = 0; i < MAXN; ++i) {
        s[i] = 1;
    }
    
    if (runParale) {
    
        std::thread threads[NO_THREADS];
        ProducerConsumerQueue<int> pcq[NO_THREADS + 1];
        
        for (int i = 0; i < NO_THREADS; ++i) {
            threads[i] = std::thread([&](int id){
                int log = NO_TASKS;
                int startPos = id * log;
                int prev = 0;
                
                if (startPos >= MAXN) {
                    return;
                }
                
                for (int i = startPos + 1; i < std::min(MAXN, (id + 1) * log); ++i) {
                    s[i] += s[i - 1];
                }
                pcq[id].dequeue(prev);
                s[std::min(MAXN - 1, (id + 1) * log - 1)] += prev;
                pcq[id + 1].enqueue(s[std::min(MAXN - 1, (id + 1) * log - 1)]);
                pcq[id + 1].close();
                
                for (int i = startPos; i < std::min(MAXN - 1, (id + 1) * log - 1); ++i) {
                    s[i] += prev;
                }
            }, i);
        }
        
        pcq[0].enqueue(0);
        pcq[0].close();
        
        for (int i = 0; i < NO_THREADS; ++i) {
            threads[i].join();
        }
    } else {
        solve();
    }
    
    for (int i = 0; i < MAXN; ++i) {
        std::cout << s[i] << " ";
    }
    std::cout << "\n";
    
    return 0;
}
