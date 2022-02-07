#include <iostream>
#include "TestEssentials.h"

int main()
{
    expect_int("Test 1", 240, 2);
    expect_int("Test 2", 20, 20);
    return 0;
}