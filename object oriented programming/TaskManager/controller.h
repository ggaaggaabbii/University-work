#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QWidget>
#include <bits/stdc++.h>
#include "repository.h"
#include "task.h"

class Controller: public QWidget {
        Q_OBJECT
    private:
        Repository repo;
    signals:
        void sendUpdate();
    public:
        Controller();
        Controller(const Controller& c) {
            repo = c.repo;
        }
        Controller(const Repository& r): repo{r} {}
        ~Controller();
        std::vector<Task> getSortedTasks() {
            std::vector<Task>v = repo.getTasks();
            std::sort(v.begin(), v.end(), [](Task & a, Task & b) {return a.getStatus() < b.getStatus();});
            return v;
        }
        void addTask(std::string desc) {
            if (desc == "") {
                return;
            }

            repo.addTask(Task{desc, -1, 0});
            emit sendUpdate();
        }
        Task getTaskFromInd(int item) {
            std::vector<Task>v = repo.getTasks();

            if (item < 0 || item >= v.size()) {
                return Task{};
            }

            std::sort(v.begin(), v.end(), [](Task & a, Task & b) {return a.getStatus() < b.getStatus();});
            return v[item];
        }
        void remTask(int item) {
            repo.remTask(getTaskFromInd(item));
            emit sendUpdate();
        }

        void workOnTask(int item, int id) {
            repo.workOnTask(getTaskFromInd(item), id);
            emit sendUpdate();
        }
        void workOnTask2(int item, int id) {
            repo.workOnTask2(getTaskFromInd(item), id);
            emit sendUpdate();
        }

};

#endif // CONTROLLER_H
