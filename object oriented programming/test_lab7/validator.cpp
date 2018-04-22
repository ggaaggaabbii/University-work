#include "validator.h"

Validator::Validator()
{
}

bool Validator::validate(std::string& i, std::string& t, std::string& a, std::string& d,
                         std::string& h)
{
    if (isS(i) && isInt(i) && isS(t) && isS(a) && isS(d) && isInt(d) && isS(h) && isD(h)) {
        if (atof(h.c_str()) >= 0 && atof(h.c_str()) <= 100)
        { return true; }
    }

    throw std::string{"Invalid song"};
}

bool Validator::isInt(std::string& s)
{
    for (auto it : s) {
        if (it < '0' || it > '9') {
            return false;
        }
    }

    return true;
}

bool Validator::isD(std::string& s)
{
    int pos = 0;
    int c = 0;

    for (auto it : s) {
        if (it == ',') {
            if (pos == 0 || c == 1) {
                return false;
            }

            c = 1;
        } else if (it < '0' || it > '9') {
            return false;
        }

        ++pos;
    }

    return true;
}

bool Validator::isS(std::string& s)
{
    return s != "";
}
