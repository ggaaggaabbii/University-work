#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

#include <bits/stdc++.h>
#include <exception>

class CustomException: public std::exception {

  private:
    std::string exceptionText;

  public:
    CustomException();
    CustomException(std::string eT): exceptionText{eT} {}
    virtual const char* what() const throw() {
        return exceptionText.c_str();
    }
};

#endif // CUSTOMEXCEPTION_H
