#include <iostream>
#include "myvector.h"

int main()
{
    MyVector<int> a;
    a = { 1, 2, 3 };
    a.pop_back();
    a.push_back(4);
    a.insert(2, 3);
    a.resize(6);
    a.resize(3);
    a.erase(1);

    for (unsigned int i = 0; i < a.size(); ++i)
        std::cout << a[i] << std::endl;
}
