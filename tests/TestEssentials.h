/**
 * @file TestEssentials.h
 * @author Haneen Mahdin (haneenmahdin@gmail.com)
 * @brief This file holds up the headers, definitions, and functions to run unit-tests.
 * @version 1.0
 * @date 2022-02-07
 * 
 * @copyright Copyright (c) 2022 Haneen Mahdin
 * 
 */

#define TEST_ESSENTIALS_H

#ifndef TEST_ESSENTIALS_H
    #define TEST_ESSENTIALS_H
#endif

#include <iostream>

typedef enum {
    success,
    failure,
    null // should never happen in a test
} ASSERT_VALUE;

/**
 * @brief Run tests for a integer value
 * 
 * @param testName 
 * @param initialValue 
 * @param expectValue 
 * @return ASSERT_VALUE 
 */
ASSERT_VALUE expect_int(const std::string testName, int initialValue, int expectValue) {
    if (initialValue == expectValue)
    {
        printf("Succeeded: 🟢🟢🟢🟢\nTest Name: %s\nExpected Value: %d\nIntial value: %d\n\n", testName.c_str(), expectValue, initialValue);

        return success;
    } else {
        printf("Failed: 🛑🛑🛑🛑\nTest Name: %s\nExpected Value: %d\nIntial value: %d\n\n", testName.c_str(), expectValue, initialValue);

        return failure;
    }

    return null; // nothing
}