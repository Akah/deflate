#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define SUCCESS "\x1B[32m[SUCCESS]\x1B[0m"
#define FAILURE "\x1B[1m\x1B[31m[FAILURE]\x1B[0m"
#define WARNING "\x1B[1m\x1B[33m[WARNING]\x1B[0m"

#define __check(name) test(#name, &name)

void result();

void test(char* name, bool(*test)(void));

void run_tests();

#endif
