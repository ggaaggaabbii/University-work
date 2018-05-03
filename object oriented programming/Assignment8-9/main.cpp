#include <bits/stdc++.h>
#include "include/Repository.h"
#include "include/uiAdmin.h"
#include "include/uiUser.h"
#include "include/Controller.h"
#include "include/Movie.h"
#include "include/WatchList.h"
#include "include/FileRepo.h"
#include "include/Validator.h"
#include "include/CSVWatchlist.h"
#include "include/HTMLWatchlist.h"
#include "include/SQLRepo.h"
#include <sqlite3.h>

int main()
{
    {
        std::string u;
        std::string pass;
        std::shared_ptr<Repository> repo;

        while (true) {
            std::cout << "Select the repo mode(file/db)\n";
            std::getline(std::cin, u);

            if (u == "file") {
                std::shared_ptr<Repository> fileRepo{new FileRepo{"data.db"}};
                repo = fileRepo;
                break;

            } else if (u == "db") {
                std::shared_ptr<Repository> fileRepo{new SQLRepo{"database.db"}};
                repo = fileRepo;
                break;
            }
        }

        std::shared_ptr<WatchList> watchList {new WatchList};
        Controller c{repo, watchList};
        Validator v{};
        uiAdmin uA{c, v};
        uiUser uU{c};

        while ( true ) {
            std::cout << "Select access mode (Admin/User):\n";
            std::getline ( std::cin, u );

            if ( u == "Admin" ) {
                std::cout << "Introduce the password:\n";
                std::getline ( std::cin, pass );

                if ( pass == "parola" ) {
                    uA.start();
                    break;
                }

            } else if ( u == "User" ) {
                while (true) {
                    std::cout << "Introduce the type of file(csv/html):\n";
                    std::getline( std::cin, u );

                    if ( u == "csv" ) {
                        c.setWatchList(std::shared_ptr <WatchList> {new CSVWatchlist{"watchlist.txt"}});
                        break;

                    } else if ( u == "html" ) {
                        c.setWatchList(std::shared_ptr<WatchList> {new HTMLWatchlist{"watchList.html"}});
                        break;
                    }
                }

                uU.start();
                break;
            }
        }
    }
    return 0;
}
