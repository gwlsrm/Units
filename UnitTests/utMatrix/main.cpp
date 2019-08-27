// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <iostream>
#include "gwmatrix.h"

using namespace std;

int main()
{
    DoubleMatrix m(3, 3);
    for (int i=0; i<3; ++i)
        for (int j=0; j<3; ++j)
            m(i,j) = i-j;
    return 0;
}
