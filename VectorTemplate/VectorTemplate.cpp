// VectorTemplate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "units.h"
#include "tests_common.h"



int main()
{
    // Basic logic of quantity<...>

    quantity<second> t(4.2);
    quantity<second, int32_t> t_int32(42);

    quantity<metre> l(666);

    std::cout << t.value() << std::endl;
    std::cout << t_int32.value() << std::endl;

    std::cout << std::is_same<
        decltype(t.value()),
        double
    >::value << std::endl;

    std::cout << std::is_same<
        decltype(t_int32.value()),
        int32_t
    >::value << std::endl;

    std::cout << (t + t).value() << std::endl;
    std::cout << (t - t).value() << std::endl;
    std::cout << (l * t).value() << std::endl;
    std::cout << (l / t).value() << std::endl;

    std::cout << std::is_same<
        decltype(t + t),
        decltype(t)
    >::value << std::endl;

    std::cout << std::is_same<
        decltype(t - t),
        decltype(t)
    >::value << std::endl;

    std::cout << std::is_same<
        decltype(l* l* l),
        cubic_metre
    >::value << std::endl;

    std::cout << std::is_same<
        decltype(l / t),
        metre_per_second
    >::value << std::endl;

    // Different units, types or scalar are not implicitly convertible


    std::cout << std::is_convertible<
        decltype(l),
        decltype(t)
    >::value << std::endl;

    std::cout << std::is_convertible<
        decltype(t),
        decltype(t_int32)
    >::value << std::endl;

    std::cout << std::is_convertible<
        decltype(l.value()),
        decltype(l)
    >::value << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages    using r = unit_add<mole, mole>::type;
//r re;
//cubic_metre cb;
//metre_per_second mps;
//metre m;
//second s;
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
