#include "ui.h"
#include "graph.h"
#include "solvefunction.h"

ui::ui()
{

}

void ui::start()
{
    std::string command;

    while (true) {
        try {
            printMenu();
            std::getline(std::cin, command);

            if (command == "0") {
                break;

            } else if (command == "1") {
                lowestCostWalk();

            } else if (command == "2") {
                nrOfMinWalks();

            } else if (command == "3") {
                nrOfDistWalks();

            } else if (command == "4") {
                bridgePass();
            }

        } catch (std::string& s) {
            std::cout << s << "\n";
        }
    }
}

void ui::printMenu()
{
    std::cout << "0. Exit\n";
    std::cout << "1. Lowest cost walk\n";
    std::cout << "2. Number of distinct minimum cost walks\n";
    std::cout << "3. Number of distinct walks\n";
    std::cout << "4. Bridge and torch problem\n";
}

void ui::lowestCostWalk()
{
    std::string file;
    std::cout << "file: ";
    std::getline(std::cin, file);
    std::ifstream f(file);

    int n, m, x, y, c;
    f >> n >> m;
    Graph g{n};

    while (m--) {
        f >> x >> y >> c;
        g.addEdge(x, y, c);
    }

    std::cout << "Give the endpoints: ";
    std::cin >> x >> y;
    std::cin.get();
    std::cout << lowestLengthWalk(g, x, y) << "\n";

}

void ui::nrOfMinWalks()
{
    std::string file;
    std::cout << "file: ";
    std::getline(std::cin, file);
    std::ifstream f(file);

    int n, m, x, y, c;
    f >> n >> m;
    Graph g{n};

    while (m--) {
        f >> x >> y >> c;
        g.addEdge(x, y, c);
    }

    std::cout << "Give the endpoints: ";
    std::cin >> x >> y;
    std::cin.get();
    std::cout << numberOfDistinctMinimumCostWalks(g, x, y) << "\n";
}

void ui::nrOfDistWalks()
{
    std::string file;
    std::cout << "file: ";
    std::getline(std::cin, file);
    std::ifstream f(file);

    int n, m, x, y, c;
    f >> n >> m;
    Graph g{n};

    while (m--) {
        f >> x >> y >> c;
        g.addEdge(x, y, c);
    }

    std::cout << "Give the endpoints: ";
    std::cin >> x >> y;
    std::cin.get();
    std::cout << numberOfDistinctWalks(g, x, y) << "\n";
}

void ui::bridgePass()
{
    std::string file;
    std::cout << "file: ";
    std::getline(std::cin, file);
    std::ifstream f(file);
    std::vector<int> people;

    int n, x;
    f >> n;

    for (int i = 1; i <= n; ++i) {
        f >> x;
        people.push_back(x);
    }

    bridgeAndTorchProblem(people);
}


