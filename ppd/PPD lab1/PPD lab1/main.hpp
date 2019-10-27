//
//  main.hpp
//  PPD lab1
//
//  Created by Gabriel Goteciuc on 12/10/2019.
//  Copyright © 2019 Gabriel Goteciuc. All rights reserved.
//

#ifndef main_hpp
#define main_hpp

#include <iostream>
#include <fstream>
#include <mutex>
#include <time.h>
#include <stdlib.h>
#include <thread>
#include <vector>
#include<pthread.h>
#include<unistd.h>
#include <algorithm>

#define MAX_PRODUCTS 100007
#define MAX_AMOUNT 1000000

struct PRODUCT {
    int id;
    int amount;
    int price;
    std::mutex mtx;
};

struct MARKET {
    int balance;
    PRODUCT products[MAX_PRODUCTS];
    std::mutex mtx;
};

struct BILL {
    std::vector<std::pair<int, int>> orders;
};

#endif /* main_hpp */
