#include "../include/Validator.h"

Validator::Validator()
{
}

bool Validator::isleapyear(int year)
{
    return ((!(year % 4) && (year % 100)) || !(year % 400));
}

bool Validator::valid_date(int year, int month, int day)
{
    int monthlen[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (!year || !month || !day || month > 12)
    { return 0; }

    if (isleapyear(year) && month == 2)
    { monthlen[1]++; }

    if (day > monthlen[month - 1])
    { return 0; }

    return 1;
}

bool Validator::validateNumber(std::string& s)
{
    for (auto it : s) {
        if (it < '0' || it > '9')
        { return false; }
    }

    return true;
}

bool Validator::validateInput(std::string& title, std::string& genre,
                              std::string& releaseDate, std::string& likes, std::string& link)
{
    if (title == "" || releaseDate == "" || genre == "" || link == "" || likes == "")
    { return false; }

    if (releaseDate.length() != 10) { return false; }

    int y, m, d;
    std::string year = releaseDate.substr(0, 4), day = releaseDate.substr(8, 2);
    std::string month = releaseDate.substr(5, 2);

    if (validateNumber(year) == false || validateNumber(month) == false ||
            validateNumber(day) == false) {
        return false;
    }

    std::string s;
    s = releaseDate.substr(0, 4);
    y = stoi(s);
    s = releaseDate.substr(5, 7);
    m = stoi(s);
    s = releaseDate.substr(8, 10);
    d = stoi(s);

    if (valid_date(y, m, d) == false) { return false; }

    if (releaseDate[4] != '-' || releaseDate[7] != '-') { return false; }

    if (validateNumber(likes) == false) { return false; }

    return true;
}
