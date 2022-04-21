// VectorTemplate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "units.h"
#include "tests_common.h"

enum class my_units
{
    czk,
    beer,
    coffee,
    absinth,
    pizza,
    chip,
    baguette,
    _count
};

using czk = basic_unit<my_units, my_units::czk>;
using beer = basic_unit<my_units, my_units::beer>;
using coffee = basic_unit<my_units, my_units::coffee>;
using absinth = basic_unit<my_units, my_units::absinth>;
using pizza = basic_unit<my_units, my_units::pizza>;
using chip = basic_unit<my_units, my_units::chip>;
using baguette = basic_unit<my_units, my_units::baguette>;

using beer_price = divided_unit<beer, czk>;

int main()
{
    // It can't be possible to combine together units from different systems
    // (even with the same enum size)

    /*std::cout << std::is_same<
        typename unit_traits<second>::enum_type,
        typename unit_traits<metre>::enum_type
    >::value << std::endl;

    std::cout << std::is_same<
        typename unit_traits<czk>::enum_type,
        typename unit_traits<beer>::enum_type
    >::value << std::endl;

    std::cout << std::is_same<
        typename unit_traits<second>::enum_type,
        typename unit_traits<beer>::enum_type
    >::value << std::endl;

    std::cout << std::is_same<
        typename unit_traits<metre_per_second>::enum_type,
        typename unit_traits<beer_price>::enum_type
    >::value << std::endl;
    
    std::cout << is_addable<quantity<czk>, quantity<second>>::value << std::endl;
    std::cout << is_subtractable<quantity<czk>, quantity<second>>::value << std::endl;
    std::cout << is_multipliable<quantity<czk>, quantity<second>>::value << std::endl;*/
    std::cout << is_divisible<quantity<czk>, quantity<second>>::value << std::endl;
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
