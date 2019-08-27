// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <iostream>

#include "Fraction.h"

using namespace std;

int main()
{
    Fraction f1(0,1);
    Fraction f2(3,4);
    cout << "Is " << f1 << " > " << f2 << "?: " << (f1 > f2) << endl;

    if (f1)
        cout << f1 << " is true\n";
    else
        cout << f1 << " is false\n";
    return 0;
}
