#include <bits/stdc++.h>
#include "repository.h"
#include "controller.h"
#include "userinterface.h"
#include "assert.h"

void test()
{
    Song s{1, "a", "a", 2, 3};
    Repository r{};
    Controller c{&r};
    r.add(s);

    try {
        r.add(s);
        assert (false);
    } catch (std::string s) {
        assert(true);
    }
}

int main()
{
    Repository r{};
    Controller c{&r};
    Song s{1, "a", "a", 2, 3};
    r.add(s);
    Song s2{2, "b", "b", 20, 13};
    r.add(s2);
    Song s3{3, "c", "c", 12, 34};
    r.add(s3);
    Song s4{4, "d", "d", 32, 342};
    r.add(s4);
    Song s5{5, "e", "e", 52, 23};
    r.add(s5);
    Validator v{};
    UserInterface u{&c, &v};
    test();
    u.start();
    return 0;
}
