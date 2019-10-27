//
//  main.cpp
//  PPD lab1
//
//  Created by Gabriel Goteciuc on 12/10/2019.
//  Copyright © 2019 Gabriel Goteciuc. All rights reserved.
//

#include "main.hpp"

MARKET m;
std::mutex historyMtx;

int noOfThreads;

std::vector<BILL> bills;

void runCheck(int threadId) {
    int sum = 0;

    for (int i = 0; i < MAX_PRODUCTS; ++i) {
        m.products[i].mtx.lock();
    }
    
    m.mtx.lock();
    historyMtx.lock();
    
    for (int i = 0; i < bills.size(); ++i) {
        for (auto it:bills[i].orders) {
            sum += m.products[it.first].price * it.second;
        }
    }
    
    if (sum != m.balance) {
        std::cout << "Error in balance\n";
    } else {
        std::cout << "Balance " << m.balance << " is correct\n";
    }
    
    m.mtx.unlock();
    
    for (int i = 0; i < MAX_PRODUCTS; ++i) {
        m.products[i].mtx.unlock();
    }
    
    historyMtx.unlock();
    
}

void processBill(int threadId) {
    int sum = 0;
    std::vector<std::pair<int, int>> orders;
    
    for (int i = 0; i < 4; ++i) {
        int product = rand() % MAX_PRODUCTS;
        int ok = 0;
        
        while (!ok) {
            ok = 1;
            for (int j = 0; j < i; ++j) {
                if (orders[j].first == product) {
                    product = rand() % MAX_PRODUCTS;
                    ok = 0;
                    break;
                }
            }
        }
        
        int quantity = rand() % 5;
        
        orders.push_back(std::make_pair(product, quantity));
    }
    
    std::sort(orders.begin(), orders.end());
    /*
    std::cout << threadId << " start\n";
    
    for (auto it:orders) {
        std::cout <<  threadId << " " <<it.first << "\n";
    }
    */
    std::sort(orders.begin(), orders.end());
    for (auto it:orders) {
        m.products[it.first].mtx.lock();
    }
    
    for (auto it:orders) {
        sum += m.products[it.first].price * it.second;
        m.products[it.first].amount -= it.second;
    }
    
    m.mtx.lock();
    historyMtx.lock();
    for (auto it:orders) {
        m.products[it.first].mtx.unlock();
    }
    
    bills.push_back(BILL());
    for (int i = 0; i < 4; ++i) {
            bills.back().orders.push_back(orders[i]);
    }
    historyMtx.unlock();
    
    m.balance += sum;
    
    m.mtx.unlock();
}

void worker(int threadId) {
    for (int i = 0; i < 4000; ++i) {
        if (rand() % 10000 == 1) {
            runCheck(threadId);
            continue;
        }
        
        processBill(threadId);
    }
}

std::thread threads[100];

int main() {
    noOfThreads = 25;
    
    srand ((unsigned)time(NULL));
    
    for (int i = 0; i < MAX_PRODUCTS; ++i) {
        m.products[i].amount = MAX_AMOUNT;
        m.products[i].id = i;
        m.products[i].price = rand() % 10 + 1;
    }
    
    for (int i = 0; i < noOfThreads; ++i) {
        threads[i] = std::thread (worker, i);
    }
    
    for (int i = 0; i < noOfThreads; ++i) {
        threads[i].join();
    }
    
    runCheck(0);
    
    return 0;
}
