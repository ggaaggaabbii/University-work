#include "ui.h"


ui::ui()
{
}

void ui::printMenu()
{
    std::cout << "0. Exit\n";
    std::cout << "1. Connected Components\n";
    std::cout << "2. Strongly Connected Components\n";
    std::cout << "3. Biconnected Components\n";
    std::cout << "4. Wolf, Goat, Cabbage problem\n";
    std::cout << "5. 15 Puzzle\n";
}

void ui::conComp()
{
    Graph g;
    std::string s;
    std::cout << "file: ";
    std::getline(std::cin, s);
    readGraphUndir(s, g);
    std::unordered_map<int, int> rez = connectedComp(g);

    for (auto it : rez) {
        std::cout << it.first << ":" << it.second << "\n";
    }
}

void ui::readGraphUndir(std::string s, Graph& g)
{
    int n, m, x, y;

    if (s == "") {
        return;
    }

    std::ifstream f(s);
    f >> n >> m;

    for (int i = 0; i < n; ++i) {
        g.addVertex(i);
    }

    while (m--) {
        f >> x >> y;
        g.addEdge(x, y);
        g.addEdge(y, x);
    }
}

void ui::readGraphDir(std::string s, Graph& g)
{
    int n, m, x, y;

    if (s == "") {
        return;
    }

    std::ifstream f(s);
    f >> n >> m;

    for (int i = 0; i < n; ++i) {
        g.addVertex(i);
    }

    while (m--) {
        f >> x >> y;
        g.addEdge(x, y);
    }
}

void ui::strConComp()
{
    Graph g;
    std::string s;
    std::cout << "file: ";
    std::getline(std::cin, s);
    readGraphDir(s, g);
    std::unordered_map<int, int> rez = stronglyConnectedComponents(g);

    for (auto it : rez) {
        std::cout << it.first << ":" << it.second << "\n";
    }
}

void ui::biConComp()
{
    Graph g;
    std::string s;
    std::cout << "file: ";
    std::getline(std::cin, s);
    readGraphDir(s, g);
    std::vector<std::vector<int> >rez = biconnectedComponents(g);

    for (auto it : rez) {
        for (auto it2 : it) {
            std::cout << it2 << " ";
        }

        std::cout << "\n";
    }
}

void ui::WGC()
{
    std::vector<int> rez = wolfGoatCabbageProblem();

    for (auto it : rez) {
        if (!(it & (1 << 3))) { std::cout << "W"; }

        if (!(it & (1 << 2))) { std::cout << "G"; }

        if (!(it & (1 << 1))) { std::cout << "C"; }

        if (!(it & (1 << 0))) { std::cout << "B"; }

        std::cout << "-";

        if (it & (1 << 3)) { std::cout << "W"; }

        if (it & (1 << 2)) { std::cout << "G"; }

        if (it & (1 << 1)) { std::cout << "C"; }

        if (it & (1 << 0)) { std::cout << "B"; }

        std::cout << "\n";
    }
}

void ui::Puzzle15()
{
    std::string s;
    std::cout << "Give the file containing the initial configuration: ";
    std::getline(std::cin, s);
    std::ifstream f(s);
    short initConf[4][4];

    for (short i = 0; i < 4; ++i) {
        for (short j = 0; j < 4; ++j) {
            f >> initConf[i][j];
        }
    }

    f.close();
    configuration c{initConf};
    std::vector<configuration> rez = solve15Puzzle(c);
    std::ofstream g("solution.out");

    for (auto it : rez) {
        g << it << "\n";
    }

    g.close();
    system("pluma solution.out");
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
                conComp();
            } else if (cmd == "2") {
                strConComp();
            } else if (cmd == "3") {
                biConComp();
            } else if (cmd == "4") {
                WGC();
            } else if (cmd == "5") {
                Puzzle15();
            }
        } catch (std::string& s) {
            std::cout << s << "\n";
        }
    }
}
