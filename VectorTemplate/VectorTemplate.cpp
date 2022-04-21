// VectorTemplate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "units.h"
#include "tests_common.h"



int main()
{
    // It can't be possible to combine together units from different systems
    // (even with the same enum size)

    std::cout << std::is_same<
        multiplied_unit<metre, metre, metre>,
        multiplied_unit<metre, multiplied_unit<metre, metre>>
    >::value << std::endl;

    std::cout << std::is_same<
        multiplied_unit<metre, metre, metre>,
        multiplied_unit<multiplied_unit<metre, metre>, metre>
    >::value << std::endl;


    using newton_direct =
        divided_unit<
        multiplied_unit<kilogram, metre>,
        multiplied_unit<second, second>
        >;

    using newton_indirect =
        multiplied_unit<
        kilogram,
        divided_unit<
        divided_unit<metre, second>,
        second
        >
        >;

    std::cout << std::is_same<newton_direct, newton_indirect>::value << std::endl;

    using scalar = divided_unit<second, second>;

    std::cout << std::is_same<
        multiplied_unit<metre, scalar>,
        multiplied_unit<metre>
    >::value << std::endl;

    std::cout << std::is_same<
        multiplied_unit<metre, scalar>,
        multiplied_unit<scalar, metre>
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
