#include "userinterface.h"

UserInterface::UserInterface(std::string fi): fileName{fi}
{
    if (fileName != "") {
        int n, m, x, y, c;
        std::ifstream f(fileName);
        f >> n >> m;
        Graph g{n};
        this->G = g;

        while (m--) {
            f >> x >> y >> c;
            this->G.addEdge(x, y, c);
        }
    }
}

void UserInterface::start()
{
    std::string command;

    while (true) {
        printMenu();
        std::getline(std::cin, command);

        if (command == "0") {
            break;
        } else if (command == "1") {
            G.printGraph();
        } else if (command == "2") {
            printEdges();
        } else if (command == "3") {
            checkEdge();
        } else if (command == "4") {
            getInOutDegree();
        } else if (command == "5") {
            printInbound();
        } else if (command == "6") {
            printOutbound();
        } else if (command == "7") {
            printEdge();
        } else if (command == "8") {
            modifyEdge();
        } else if (command == "9") {
            deleteEdge();
        } else if (command == "10") {
            deleteVertex();
        } else if (command == "11") {
            addVertex();
        } else if (command == "12") {
            addEdge();
        }
    }
}

void UserInterface::printMenu()
{
    std::cout << "Menu:\n";
    std::cout << "0. Exit\n";
    std::cout << "1. Print Graph\n";
    std::cout << "2. Print vertices\n";
    std::cout << "3. Check edge\n";
    std::cout << "4. Get in/out degree of a vertex\n";
    std::cout << "5. Print inbound of a vertex\n";
    std::cout << "6. Print outbound of a vertex\n";
    std::cout << "7. Print edge by id\n";
    std::cout << "8. Modify edge\n";
    std::cout << "9. Delete edge\n";
    std::cout << "10. Delete vertex\n";
    std::cout << "11. Add vertex\n";
    std::cout << "12. Add edge\n";
}

void UserInterface::printEdges()
{
    for (auto it : G.parseX()) {
        std::cout << it << " ";
    }

    std::cout << "\n";
}

void UserInterface::checkEdge()
{
    int x, y;
    std::cout << "Give the endpoints of the edge:\n";
    std::cin >> x >> y;
    std::cin.get();
    int e = G.isEdge(x, y);

    if (e == -1) {
        std::cout << "There is no edge between " << x << " and " << y << "\n";
    } else {
        std::cout << "The edge id is " << e << "\n";
    }
}

void UserInterface::getInOutDegree()
{
    int node;
    std::cout << "Give the node:\n";
    std::cin >> node;
    std::cin.get();
    int in = G.getInDegree(node);

    if (in == -1) {
        std::cout << "The given number is not a vertex in the graph...\n";
        return;
    }

    std::cout << "Indegree of " << node << " is:" << in;
    std::cout << "; outdegree is: " << G.getOutDegree(node) << "\n";
}

void UserInterface::printInbound()
{
    int node;
    std::cout << "Give the node:\n";
    std::cin >> node;
    std::cin.get();
    int in = G.getInDegree(node);

    if (in == -1) {
        std::cout << "The given number is not a vertex in the graph...\n";
        return;
    }

    if (in == 0) {
        std::cout << "No inbound edges\n";
        return;
    }

    for (auto it : G.parseNIn(node)) {
        std::cout << it << " ";
    }

    std::cout << "\n";
}

void UserInterface::printOutbound()
{
    int node;
    std::cout << "Give the node:\n";
    std::cin >> node;
    std::cin.get();
    int out = G.getOutDegree(node);

    if (out == -1) {
        std::cout << "The given number is not a vertex in the graph...\n";
        return;
    }

    if (out == 0) {
        std::cout << "No outbound edges\n";
        return;
    }

    for (auto it : G.parseNOut(node)) {
        std::cout << it << " ";
    }

    std::cout << "\n";
}

void UserInterface::printEdge()
{
    int edge;
    std::cout << "Give the edge:\n";
    std::cin >> edge;
    std::cin.get();
    std::tuple<int, int, int> t = G.getEdge(edge);

    if (std::get<0>(t) == -1) {
        std::cout << "There is no such edge\n";
        return;
    }

    std::cout << "Endpoints: " << std::get<0>(t) << ", " << std::get<1>(t);
    std::cout << ", Cost: " << std::get<2>(t) << "\n";
}

void UserInterface::modifyEdge()
{
    int edge;
    std::cout << "Give the edge:\n";
    std::cin >> edge;
    std::tuple<int, int, int> t = G.getEdge(edge);

    if (std::get<0>(t) == -1) {
        std::cout << "There is no such edge\n";
        return;
    }

    int newVal;
    std::cout << "Give the new cost:\n";
    std::cin >> newVal;
    std::cin.get();
    G.updateEdge(edge, newVal);
}

void UserInterface::deleteEdge()
{
    int x, y;
    std::cout << "Give the endpoints of the edge:\n";
    std::cin >> x >> y;
    std::cin.get();

    if (G.deleteEdge(x, y)) {
        return;
    }

    std::cout << "There is no edge between " << x << " and " << y << "\n";
}

void UserInterface::deleteVertex()
{
    int node;
    std::cout << "Give the node:\n";
    std::cin >> node;
    std::cin.get();
    int out = G.getOutDegree(node);

    if (out == -1) {
        std::cout << "The given number is not a vertex in the graph...\n";
        return;
    }

    G.deleteNode(node);
}

void UserInterface::addVertex()
{
    int node;
    std::cout << "Give the node:\n";
    std::cin >> node;
    std::cin.get();

    if (!G.addVertex(node)) {
        std::cout << node << " is already a vertex in the graph\n";
    }
}

void UserInterface::addEdge()
{
    int x, y, z;
    std::cout << "Give the endpoints of the edge and the cost:\n";
    std::cin >> x >> y >> z;
    std::cin.get();

    if (!G.addEdge(x, y, z)) {
        std::cout << "The edge already exists\n";
    }
}
