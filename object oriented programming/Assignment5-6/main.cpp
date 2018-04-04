#include <bits/stdc++.h>
#include "include/DynamicVector.h"
#include "include/Repository.h"
#include "include/uiAdmin.h"
#include "include/uiUser.h"
#include "include/Controller.h"
#include "include/Movie.h"
#include "include/WatchList.h"
#define pb push_back
#define mp make_pair
#define sec second
#define fir first
#define INF 1000000000

int main()
{
    {
        std::string u;
        std::string pass;
        Repository r{"data.db"};
        WatchList w{};
        Controller c{r, w};
        uiAdmin uA{c};
        uiUser uU{c};

        while (true) {
            std::cout << "Select access mode (Admin/User):\n";
            std::getline(std::cin, u);

            if (u == "Admin") {
                std::cout << "Introduce the password:\n";
                std::getline(std::cin, pass);

                if (pass == "parola") {
                    uA.start();
                    break;
                }
            } else if (u == "User") {
                uU.start();
                break;
            }
        }
    }
    return 0;
}
