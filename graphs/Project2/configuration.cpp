#include "configuration.h"

configuration::configuration(unsigned long long h)
{
    std::vector<short> v;

    for (short i = 0; i < 16; ++i) {
        v.push_back((short)(h % 16));
        h /= 16;
    }

    int pos = 0;

    for (short i = 0; i < 4; ++i) {
        for (short j = 0; j < 4; ++j) {
            conf[i][j] = v[pos++];
        }
    }
}

configuration::configuration(short conf[4][4])
{
    for (short i = 0; i < 4; ++i) {
        for (short j = 0; j < 4; ++j) {
            this->conf[i][j] = conf[i][j];
        }
    }
}

configuration::configuration(std::string s)
{
    if (s == "final") {
        int count = 1;

        for (short i = 0; i < 4; ++i) {
            for (short j = 0; j < 4; ++j) {
                conf[i][j] = count++;
            }
        }

        conf[3][3] = 0;
    }
}

bool configuration::operator<(const configuration) const
{
    return true;
}

bool configuration::operator==(configuration c) const
{
    for (short i = 0; i < 4; ++i) {
        for (short j = 0; j < 4; ++j) {
            if (conf[i][j] != c[i][j]) {
                return false;
            }
        }
    }

    return true;
}

unsigned long long configuration::getHash()
{
    unsigned long long sum = 0, pow = 1;
    std::vector<short> v;

    for (short i = 0; i < 4; ++i) {
        for (short j = 0; j < 4; ++j) {
            v.push_back(conf[i][j]);
        }
    }

    for (auto it : v) {
        sum += pow * it;
        pow *= 16;
    }

    //std::cout << sum << "\n";
    return sum;
}

short* configuration::operator[](int n)
{
    return conf[n];
}

std::vector<configuration> configuration::neighbours()
{
    std::vector<configuration> neigh;
    short posX = 0, posY = 0, tmp[4][4];
    short x[] = {-1, 0, 1, 0}, y[] = {0, -1, 0, 1};

    for (short i = 0; i < 4; ++i) {
        for (short j = 0; j < 4; ++j) {
            tmp[i][j] = conf[i][j];

            if (tmp[i][j] == 0) {
                posX = i;
                posY = j;
            }
        }
    }

    for (short i = 0 ; i < 4; ++i) {
        if (posX + x[i] >= 0 && posX + x[i] <= 3 && posY + y[i] >= 0 && posY + y[i] <= 3) {
            std::swap(tmp[posX][posY], tmp[posX + x[i]][posY + y[i]]);
            neigh.push_back(configuration{tmp});
            std::swap(tmp[posX][posY], tmp[posX + x[i]][posY + y[i]]);
        }
    }

    return neigh;
}
