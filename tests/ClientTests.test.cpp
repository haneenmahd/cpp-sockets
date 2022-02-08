#include <iostream>
#include "TestEssentials.h"

int main()
{
    expect_int("Test 1", 240, 2);
    expect_int("Test 2", 20, 20);
    expect_string("Test 3", "Hello", "Hell");
    expect_bool("Test 4", true, false);
    expect_float("Test 5", 4.3, 4.3222);
    
    return 0;
}