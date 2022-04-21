// VectorTemplate.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "units.h"

enum class si_units
{
    second,
    metre,
    kilogram,
    ampere,
    kelvin,
    mole,
    candela,
    _count
};

using second = basic_unit<si_units, si_units::second>;
using metre = basic_unit<si_units, si_units::metre>;
using kilogram = basic_unit<si_units, si_units::kilogram>;
using ampere = basic_unit<si_units, si_units::ampere>;
using kelvin = basic_unit<si_units, si_units::kelvin>;
using mole = basic_unit<si_units, si_units::mole>;
using candela = basic_unit<si_units, si_units::candela>;

int main()
{
    second s;
    metre m;
    kilogram k;
    ampere a;
    kelvin kv;
    mole mo;
    candela c;
    //using r = added_t<mole, candela>::type;
    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
