#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <bits/stdc++.h>
#include "programmer.h"
#include "task.h"

class Repository {
    private:
        std::vector<Programmer> progs;
        std::vector<Task> tasks;
    public:
        Repository(const std::string& file);
        ~Repository();
        Repository();
        std::vector<Programmer> getProg() {return progs;}
        std::vector<Task>getTasks() {return tasks;}
        void addTask(Task t) {
            tasks.push_back(t);
            writeToFile();

        }
        void remTask(Task t) {
            for (int i = 0; i < tasks.size(); ++i) {
                if (tasks[i] == t) {
                    tasks[i] = tasks[tasks.size() - 1];
                    tasks.pop_back();
                    writeToFile();
                    return;
                }
            }
        }
        void workOnTask(Task t, int id) {
            for (int i = 0; i < tasks.size(); ++i) {
                if (tasks[i] == t) {
                    if (tasks[i].getStatus() == "open") {
                        tasks[i].setStatus("in progress");
                        tasks[i].setProg(id);
                    }

                    writeToFile();
                    return;
                }
            }
        }
        void workOnTask2(Task t, int id) {
            for (int i = 0; i < tasks.size(); ++i) {
                if (tasks[i] == t) {
                    if (tasks[i].getStatus() == "in progress") {
                        tasks[i].setStatus("closed");
                    }

                    writeToFile();
                    return;
                }
            }
        }
        void writeToFile() {
            std::ofstream g("tasks.txt");

            for (auto it : tasks) {
                g << it.getDesc() << ",";

                if (it.getStatus() == "open") {
                    g << 0;

                } else if (it.getStatus() == "in progress") {
                    g << 1;

                } else {
                    g << 2;
                }

                g << ",";
                g << it.getProg();
                g << "\n";
            }

            g.close();
        }
};

#endif // REPOSITORY_H
