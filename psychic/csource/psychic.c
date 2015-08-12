#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "./psychic_share.h"

int pc_total_assertions;

void pc_fail() {
        pc_current_test_failed = 1;
}

void assert_true(int r) {
        pc_total_assertions++;
        if (!r) {
            pc_fail();
        } 
}

void assert_equals_int(int a, int b) {
        pc_total_assertions++;
        if (a != b) {
            pc_fail();
        }
}

