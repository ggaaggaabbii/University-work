#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <bits/stdc++.h>

class Validator {
  public:
    Validator();
    /*
    static functions used for validation of data
    */
    bool isleapyear(int year);
    bool valid_date(int year, int month, int day);
    bool validateNumber(std::string&);
    bool validateInput(std::string&, std::string&, std::string&,
                       std::string&, std::string&);
};

#endif // VALIDATOR_H
