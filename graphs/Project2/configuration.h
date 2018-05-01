#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;
class configuration {
  private:
    short conf[4][4];

  public:
    configuration() {}
    configuration(unsigned long long);
    configuration(short[4][4]);
    configuration(std::string);
    bool operator<(const configuration c) const;
    bool operator==(configuration c) const;
    unsigned long long getHash();
    short* operator[](int n);
    std::vector<configuration> neighbours();
    friend std::ostream& operator<<(std::ostream& output, const configuration& m ) {
        for (short i = 0; i < 4; ++i) {
            for (short j = 0; j < 4; ++j) {
                output << m.conf[i][j] << " ";
            }

            output << "\n";
        }

        return output;
    }
};

namespace std {
template <>
struct hash<configuration> {
    size_t operator()(configuration k) const {
        // Compute individual hash values for two data members and combine them using XOR and bit shifting
        return (hash<unsigned long long>()(k.getHash()));
    }
};
}

#endif // CONFIGURATION_H
