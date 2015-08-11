#ifndef PCTEST_S

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

int failures = 0;
int assertions;
int success;

void pc_succeed() {
        printf(".");
}

void pc_fail() {
        printf("F");
}

void assert_true(int r) {
        if (r) {
                pc_succeed();
        } else {
                pc_fail();
        }
}

void assert_equals_int(int a, int b) {
        if (a == b) {
                pc_succeed();
        } else {
                pc_fail();
        }
}
#define PCTEST_S
#endif
