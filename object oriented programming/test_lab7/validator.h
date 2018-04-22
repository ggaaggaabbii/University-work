#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <bits/stdc++.h>

class Validator {
  public:
    Validator();
    bool validate(std::string&, std::string&, std::string&, std::string&, std::string&);
    bool isInt(std::string&);
    bool isD(std::string&);
    bool isS(std::string&);
};

#endif // VALIDATOR_H
