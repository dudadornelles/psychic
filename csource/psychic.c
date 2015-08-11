#ifndef ECTEST_S

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

void ec_succeed() {
        printf("success\n");
}

void ec_fail() {
        printf("assertion error\n");
}

void assert_true(int r) {
        r ? ec_succeed() : ec_fail();
}
#define ECTEST_S
#endif
