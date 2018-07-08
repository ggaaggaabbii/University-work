#ifndef TASK_H
#define TASK_H
#include <bits/stdc++.h>

class Task {
    private:
        std::string descr;
        int idProg;
        std::string status;
    public:
        Task();
        Task(const std::string& d, int i, int s): descr{d}, idProg{i} {
            if (s == 0) {
                status = "open";

            } else if (s == 1) {
                status = "in progress";

            } else {
                status = "closed";
            }
        }
        std::string getStatus() {
            return status;
        }
        std::string getStr() {
            return descr + " " + status;
        }
        bool operator ==(Task& other) {
            return idProg == other.idProg && descr == other.descr && status == other.status;
        }
        void setStatus(const std::string& stat) {
            status = stat;
        }
        int getId() {
            return idProg;
        }
        void setProg(int i) {
            idProg = i;
        }
        std::string getDesc() {
            return descr;
        }
        int getProg() {
            return idProg;
        }
};

#endif // TASK_H
