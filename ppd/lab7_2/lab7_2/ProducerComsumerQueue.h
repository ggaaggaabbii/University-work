//
//  ProducerConsumerQueue.h
//  lab4
//
//  Created by Gabriel Goteciuc on 03/11/2019.
//  Copyright © 2019 Gabriel Goteciuc. All rights reserved.
//

#ifndef ProducerConsumerQueue_h
#define ProducerConsumerQueue_h

#include <queue>

template<typename T>
class ProducerConsumerQueue{
public:
    
    void enqueue(T val) {
        std::unique_lock<std::mutex> lock(mtx);
        q.push(val);
        cv.notify_one();
    }
    
    bool dequeue(T& val) {
        std::unique_lock<std::mutex> lock(mtx);
        
        while (true) {
            if (!q.empty()) {
                val = q.front();
                q.pop();
                return false;
            }
            if (isClosed) {
                return true;
            }
            cv.wait(lock);
        }
    }
    
    void close() {
        std::unique_lock<std::mutex> lock(mtx);
        isClosed = true;
        cv.notify_all();
    }
    
private:
    std::queue<T> q;
    std::mutex mtx;
    std::condition_variable cv;
    bool isClosed = false;
};

#endif /* ProducerConsumerQueue_h */
