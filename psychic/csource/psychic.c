#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "psychic_share.h"

int pc_total_assertions;

void pc_fail() {
        pc_current_test_failed = 1;
}

void assert_true(int r) 
{
        pc_total_assertions++;
        if (!r) {
                pc_fail();
        } 
}

void assert_equals_str(char *a, char *b) 
{
        pc_total_assertions++;
        if (strcmp(a, b) != 0) 
        {
                pc_fail();
        }

}

void assert_equals_int(int a, int b) 
{
        pc_total_assertions++;
        if (a != b) 
        {
                pc_fail();
        }
}

