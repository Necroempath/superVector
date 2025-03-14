#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Super_Vector.h"

void DisplayVector(const SuperVector& vector)
{
    for (int i = 0; i < vector.Size(); ++i)
    {
        std::cout << vector[i] << " ";
    }
}

int main()
{
    SuperVector vector(5);
    SuperVector vector_1(7);

    vector_1[0] = 9;
    vector_1[1] = 3;
    vector_1[2] = 4;
    vector_1[3] = -1;
    vector_1[4] = 8;
    vector[0] = 10;
    vector[1] = 6;
    vector[2] = 7;
    vector[3] = 0;
    vector[4] = -11;

    
 /*   vector_1--;*/
    std::cout << vector++ << "\n";
    vector.PushBack(7.1);
    std::cout << ++vector << "\n";
    vector.Remove(1);
    std::cout << vector;
    //CANNOT OVERLOAD ISTREAM>>
    return 0;
}
