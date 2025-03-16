#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Super_Vector.h"

void DisplayVector(const SuperVector<float>& vector)
{
    for (int i = 0; i < vector.Size(); ++i)
    {
        std::cout << vector[i] << " ";
    }
}

int main()
{
    SuperVector<double> vector = {1,2,3,4,5};
    SuperVector<short> vector_1(5);
    
    std::cout << vector++ << "\n";
    vector.PushBack(17.2);
    std::cout << ++vector << "\n";
    vector.Remove(1);
    std::cout << vector;

    return 0;
}
