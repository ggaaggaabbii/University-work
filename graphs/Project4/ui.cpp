#include "ui.h"

ui::ui()
{

}

void printMenu()
{
    std::cout << "0. Exit\n";
    std::cout << "1. Scheduler\n";
    std::cout << "2. Build tree from preorder and postorder lists\n";
    std::cout << "3. Number of paths between 2 vertices\n";
    std::cout << "4. Number of paths of min cost\n";
}

void ui::start()
{
    std::string cmd;

    while (true) {
        try {
            printMenu();
            std::getline(std::cin, cmd);

            if (cmd == "0") {
                break;

            } else if (cmd == "1") {
                schedule();

            } else if (cmd == "2") {
                buildTree();

            } else if (cmd == "3") {
                distinctPaths();

            } else if (cmd == "4") {
                distMin();
            }

        } catch (std::string& s) {
            std::cout << s;
        }
    }
}

void ui::schedule()
{
    std::string fileName;
    std::unordered_map<int, int> duration;
    std::cout << "file:";
    std::getline(std::cin, fileName);
    std::ifstream f(fileName);
    int n, m, x;
    f >> n;
    Graph g{n};

    for (int i = 0; i < n; ++i) {
        f >> duration[i];
    }

    for (int i = 0; i < n; ++i) {
        f >> m;

        while (m--) {
            f >> x;
            g.addEdge(x, i, 0);
        }
    }

    std::unordered_map<std::string, std::unordered_map<int, int>> result = scheduler(g, duration);

    for (auto it : result) {
        std::cout << it.first << ":\n";

        for (auto it2 : it.second) {
            std::cout << it2.first << " :" << it2.second << ", ";
        }

        std::cout << "\n";
    }

    std::vector<int> critic = getCritic(result, g);

    std::cout << "Critical activities: ";

    for (auto it : critic) {
        std::cout << it << " ";
    }

    std::cout << "\n";
}

void ui::distinctPaths()
{
    std::string fileName;
    std::cout << "file:";
    std::getline(std::cin, fileName);
    std::ifstream f(fileName);
    int n, m, x, y, start, end;
    f >> n >> m;
    Graph g{n};

    while (m--) {
        f >> x >> y;
        g.addEdge(x, y, 0);
    }

    std::cout << "Give endpoints:\n";
    std::cin >> start >> end;
    std::cin.get();

    std::cout << nOPaths(g, start, end) << "\n";
}

void ui::distMin()
{
    std::string fileName;
    std::cout << "file:";
    std::getline(std::cin, fileName);
    std::ifstream f(fileName);
    int n, m, x, y, start, end, c;
    f >> n >> m;
    Graph g{n};

    while (m--) {
        f >> x >> y >> c;
        g.addEdge(x, y, c);
    }

    std::cout << "Give endpoints:\n";
    std::cin >> start >> end;
    std::cin.get();

    std::cout << nOMinPaths(g, start, end) << "\n";
}

void ui::buildTree()
{
    std::vector<int>preorder;
    std::vector<int>postorder;
    std::string fileName;
    std::cout << "file:";
    std::getline(std::cin, fileName);
    std::ifstream f(fileName);
    int n, x;
    f >> n;

    for (int i = 0; i < n; ++i) {
        f >> x;
        preorder.push_back(x);
    }

    for (int i = 0; i < n; ++i) {
        f >> x;
        postorder.push_back(x);
    }

    Graph g{n};
    buildTreeFromPrePost(g, preorder, postorder);
    g.printGraph();
}
