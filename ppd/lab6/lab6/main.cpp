//
//  main.cpp
//  lab6
//
//  Created by Gabriel Goteciuc on 19/11/2019.
//  Copyright © 2019 Gabriel Goteciuc. All rights reserved.
//

#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <vector>
#include "ProducerComsumerQueue.h"
#define MAXN 16
#define NO_THREADS 8

template< class ForwardIt, class T >
void fill(ForwardIt first, ForwardIt last, const T& value)
{
    for (; first != last; ++first) {
        *first = value;
    }
}

int a[MAXN], b[MAXN], c[2 * MAXN];
std::vector<int> kar_a, kar_b;
std::vector<int> sol(2 * MAXN - 1);

void nSqueredMultiplication() {
    for (int i = 0; i < MAXN; ++i) {
        for (int j = 0; j < MAXN; ++j) {
            c[i + j] += a[i] * b[j];
        }
    }
}

void mul(int id) {
    for (int i = id; i < 2 * MAXN; i += NO_THREADS) {
        for (int j = 0; j <= std::min(i, MAXN); ++j) {
            int y = i - j;
            if (y < MAXN) {
                c[i] += a[j] * b[y];
            }
        }
    }
}

void nSquaredParalel() {
    std::thread threads[NO_THREADS];
    
    for (int i = 0; i < NO_THREADS; ++i) {
        threads[i] = std::thread(mul, i);
    }
    
    for (int i = 0; i < NO_THREADS; ++i) {
        threads[i].join();
    }
}

void karatsuba(const std::vector <int> &a, const std::vector <int> &b, std::vector <int> &sol)
{
    if(a.size() == 1 && b.size() == 1) {
      sol[0] = a[0] * b[0];
      return;
    }
    unsigned long long half = a.size() / 2;
    // first part
    std::vector <int> a_lo(a.begin(), a.begin() + half);
    std::vector <int> a_hi(a.begin() + half, a.end());
    std::vector <int> b_lo(b.begin(), b.begin() + half);
    std::vector <int> b_hi(b.begin() + half, b.end());
    std::vector <int> lo(a_lo.size() + b_lo.size() - 1);
    std::vector <int> hi(a_hi.size() + b_hi.size() - 1);
    karatsuba(a_lo, b_lo, lo);
    karatsuba(a_hi, b_hi, hi);
    // copy first part
    for(int i = 0; i < lo.size(); ++ i) {
      sol[i] += lo[i];
    }
    // middle
    for(int i = 0; i < a_hi.size(); ++ i) {
      a_lo[i] += a_hi[i];
      b_lo[i] += b_hi[i];
    }
    std::vector <int> mid(a_lo.size() + b_lo.size() - 1);
    karatsuba(a_lo, b_lo, mid);
    for(int i = 0; i < mid.size(); ++ i) {
      sol[i + half] += mid[i] - lo[i] - hi[i];
    }
    for(int i = 0; i < hi.size(); ++ i) {
      sol[i + 2 * half] += hi[i];
    }
}
std::atomic<int> T{0};

void karatsuba_paralel(const std::vector <int> &a, const std::vector <int> &b, std::vector <int> &sol) {
  if(a.size() == 1 && b.size() == 1) {
    sol[0] = a[0] * b[0];
    return;
  }
  unsigned long long half = a.size() / 2;
  // first part
  std::vector <int> a_lo(a.begin(), a.begin() + half);
  std::vector <int> a_hi(a.begin() + half, a.end());
  std::vector <int> b_lo(b.begin(), b.begin() + half);
  std::vector <int> b_hi(b.begin() + half, b.end());
  std::vector <int> lo(a_lo.size() + b_lo.size());
  std::vector <int> hi(a_hi.size() + b_hi.size());
  std::vector <std::thread> th;
  T += 2;
  if (T < NO_THREADS) {
    th.push_back(std::thread([&a_lo, &b_lo, &lo](){karatsuba_paralel(a_lo, b_lo, lo);}));
    th.push_back(std::thread([&a_hi, &b_hi, &hi](){karatsuba_paralel(a_hi, b_hi, hi);}));
  } else {
    karatsuba_paralel(a_lo, b_lo, lo);
    karatsuba_paralel(a_hi, b_hi, hi);
  }

  std::vector <int> a_lo2(a_lo);
  std::vector <int> b_lo2(b_lo);
  for(int i = 0; i < a_hi.size(); ++ i) {
    a_lo2[i] += a_hi[i];
    b_lo2[i] += b_hi[i];
  }
  std::vector <int> mid(a_lo2.size() + b_lo2.size() - 1);
  T += 1;
  if (T < NO_THREADS) {
    th.push_back(std::thread([&a_lo2, &b_lo2, &mid](){karatsuba_paralel(a_lo2, b_lo2, mid);}));
  } else {
    karatsuba_paralel(a_lo2, b_lo2, mid);
  }
  // wait for threads to finish
  T -= (int)th.size();
  for(int i = 0; i < th.size(); ++ i) {
    th[i].join();
  }
  // copy first part
  for(int i = 0; i < lo.size(); ++ i) {
    sol[i] += lo[i];
  }
  for(int i = 0; i < mid.size(); ++ i) {
      sol[i + half] += mid[i] - lo[i] - hi[i];
  }
  for(int i = 0; i < hi.size(); ++ i) {
    sol[i + 2 * half] += hi[i];
  }
}


int main() {
    
    for (int i = 0; i < MAXN; ++i) {
        a[i] = b[i] = 1;
        kar_a.push_back(1);
        kar_b.push_back(1);
    }
    
    //nSqueredMultiplication();
    //nSquaredParalel();
    //karatsuba(kar_a, kar_b, sol);
    karatsuba_paralel(kar_a, kar_b, sol);
    
    for (int i = 0;i < 2 * MAXN; ++i) {
        std::cout <<sol[i] <<" ";
    }
    
    return 0;
}
