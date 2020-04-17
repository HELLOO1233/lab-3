#include <iostream>
#include "C:\Users\Kirill\Desktop\Программирование\2-й сем\laba32\laba32\histogram.h"
#include <cassert>

void test_positive()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}
void test_1()
{
    double min = 0;
    double max = 0;
    find_minmax({-1, -7, -10}, min, max);
    assert(min == -10);
    assert(max == -1);
}

void test_2()
{
    double min = 0;
    double max = 0;
    find_minmax({4, 4, 4}, min, max);
    assert(min == 4);
    assert(max == 4);
}

void test_3()
{
    double min = 0;
    double max = 0;
    find_minmax({5}, min, max);
    assert(min == 5);
    assert(max == 5);
}

void test_4()
{
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}

int main()
{
    test_positive();
    test_1();
    test_2();
    test_3();
    test_4();
}
