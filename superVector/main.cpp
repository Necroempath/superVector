#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Super_Vector.h"

int main()
{
    SuperVector vector{ 1,2,3,4,5 };
    SuperVector vector_1{ 3, -1, 1, 2 };
    vector += vector_1;
    std::cin >> vector_1;
    vector.PushBack(6);
    vector.Remove(3);
    vector.Insert(3, 16);
    vector.Pop();
    vector + vector_1;
    vector += vector_1;
    std::cout << vector;
}
