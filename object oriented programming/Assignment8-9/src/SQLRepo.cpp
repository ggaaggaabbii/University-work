#include "include/SQLRepo.h"
#include "include/CustomException.h"
#include "stdio.h"

std::vector<Movie> g_tmp;

static int callback(void*, int , char** argv, char** )
{
    Movie M{argv[0], argv[1], argv[2], atoi(argv[3]), argv[4]};
    g_tmp.push_back(M);
    return 0;
}

static int callback2(void*, int argc, char** argv, char** azColName )
{
    int i;

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

SQLRepo::SQLRepo(const std::string& database)
{

    this->database = database;
    char* zErrMsg;
    const char* data = "Callback function called";
    int rc = sqlite3_open(database.c_str(), &db);

    if (rc) {
        throw CustomException{std::string{"could not open the database"}};
    }

    std::string sql = "CREATE TABLE IF NOT EXISTS MOVIES("  \
                      "TITLE            TEXT    NOT NULL," \
                      "GENRE            TEXT    NOT NULL," \
                      "RELEASE_DATE     TEXT    NOT NULL," \
                      "NUMBER_OF_LIKES  INT     NOT NULL," \
                      "LINK             TEXT    NOT NULL );";
    rc = sqlite3_exec(db, sql.c_str(), callback2, 0, &zErrMsg);
    sql = "SELECT * from MOVIES";
    rc = sqlite3_exec(db, sql.c_str(), callback, (void*)data, &zErrMsg);
    movieList = g_tmp;
    g_tmp.clear();
}

SQLRepo::~SQLRepo()
{
    sqlite3_close(db);
}

bool SQLRepo::addMovie(const Movie& M)
{
    Repository::addMovie(M);
    char* zErrMsg;
    std::string sql = "INSERT INTO MOVIES(TITLE, GENRE, RELEASE_DATE, NUMBER_OF_LIKES, LINK) " \
                      "VALUES ('" + M.getTitle() + "', '" + M.getGenre() + "', '" + M.getReleaseDate() + "', " +
                      std::to_string(M.getNumberOfLikes()) + ", '" + M.getLink() + "');";

    int rc = sqlite3_exec(db, sql.c_str(), callback2, 0, &zErrMsg);

    if ( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);

    }

    return true;
}

bool SQLRepo::deleteMovie(const std::string& title, const std::string& releaseDate)
{
    Repository::deleteMovie(title, releaseDate);
    char* zErrMsg;
    std::string sql = "DELETE from MOVIES where TITLE = '" + title + "' AND RELEASE_DATE = '" +
                      releaseDate + "';";

    int rc = sqlite3_exec(db, sql.c_str(), callback2, 0, &zErrMsg);

    if ( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);

    }

    return true;
}

bool SQLRepo::updateMovie(const std::string& title, const std::string& releaseDate,
                          const Movie& M)
{
    Repository::updateMovie(title, releaseDate, M);
    char* zErrMsg;
    std::string sql = "UPDATE MOVIES SET TITLE = '" + M.getTitle() + "', GENRE = '" + M.getGenre()
                      + "', RELEASE_DATE = '" + M.getReleaseDate() + "', NUMBER_OF_LIKES = " + std::to_string(
                          M.getNumberOfLikes())
                      + ", LINK = '" + M.getLink() + "' where TITLE='" + title + "' AND RELEASE_DATE='" + releaseDate +
                      "';";

    int rc = sqlite3_exec(db, sql.c_str(), callback2, 0, &zErrMsg);

    if ( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);

    }

    return true;
}
