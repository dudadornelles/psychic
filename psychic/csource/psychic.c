#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "psychic.h"
#include "psychic_share.h"


int pc_total_assertions;
int pc_current_test_failed;
FILE* pc_error_messages;
char* pc_current_test_name;

void pc_fail() {
    pc_current_test_failed = 1;
}

void assert_true_r(int b, int line_number) 
{
    pc_total_assertions++;
    if (!b) {
        fprintf(pc_error_messages, "\nError in test %s:%d", pc_current_test_name, line_number);
        fprintf(pc_error_messages, "\n\tAssertion Failure.");
        pc_current_test_failed = 1;
    } 
}

void assert_false_r(int b, int line_number) 
{
    pc_total_assertions++;
    if (b) {
        fprintf(pc_error_messages, "\nError in test %s:%d", pc_current_test_name, line_number);
        fprintf(pc_error_messages, "\n\tAssertion Failure.");
        pc_fail();
    } 
}

void assert_null_r(void *p, int line_number)
{
    pc_total_assertions++;
    if (p != 0)
    {
        fprintf(pc_error_messages, "\nError in test %s:%d", pc_current_test_name, line_number);
        fprintf(pc_error_messages, "\n\tAssertion Failure.");
        pc_fail();
    }
}

void assert_not_null_r(void *p, int line_number)
{
    pc_total_assertions++;
    if (p == 0)
    {
        fprintf(pc_error_messages, "\nError in test %s:%d", pc_current_test_name, line_number);
        fprintf(pc_error_messages, "\n\tAssertion Failure.");
        pc_fail();
    }
}

void assert_equals_str_r(char *a, char *b, int line_number) 
{
    pc_total_assertions++;
    if (strcmp(a, b) != 0) 
    {
        fprintf(pc_error_messages, "\nError in test %s:%d", pc_current_test_name, line_number);
        fprintf(pc_error_messages, "\n\tExpected %s to equals %s", a, b);
        pc_fail();
    }
}

void assert_not_equals_str_r(char *a, char *b, int line_number)
{
    pc_total_assertions++;
    if (strcmp(a, b) == 0) 
    {
        fprintf(pc_error_messages, "\nError in test %s:%d", pc_current_test_name, line_number);
        fprintf(pc_error_messages, "\n\tExpected %s to not equals %s", a, b);
        pc_fail();
    }
}

void assert_equals_int_r(int a, int b, int line_number) 
{
    pc_total_assertions++;
    if (a != b) 
    {
        pc_fail();
        fprintf(pc_error_messages, "\nError in test %s:%d", pc_current_test_name, line_number);
        fprintf(pc_error_messages, "\n\tExpected %i to equals %i", a, b);
    }
}

void assert_not_equals_int_r(int a, int b, int line_number)
{
    pc_total_assertions++;
    if (a == b) 
    {
        pc_fail();
        fprintf(pc_error_messages, "\nError in test %s:%d", pc_current_test_name, line_number);
        fprintf(pc_error_messages, "\n\tExpected %i to not equals %i", a, b);
    }
}

void assert_equals_float_r(float a, float b, int line_number)
{
    pc_total_assertions++;
    if (a != b) 
    {
        fprintf(pc_error_messages, "\nError in test %s:%d", pc_current_test_name, line_number);
        fprintf(pc_error_messages, "\n\tExpected %f to equals %f", a, b);
        pc_fail();
    }
}

void assert_not_equals_float_r(float a, float b, int line_number)
{
    pc_total_assertions++;
    if (a != b) 
    {
        fprintf(pc_error_messages, "\nError in test %s:%d", pc_current_test_name, line_number);
        fprintf(pc_error_messages, "\n\tExpected %f to not equals %f", a, b);
        pc_fail();
    }
}

void assert_equals_double_r(double a, double b, int line_number)
{
    pc_total_assertions++;
    if (a != b) 
    {
        fprintf(pc_error_messages, "\nError in test %s:%d", pc_current_test_name, line_number);
        fprintf(pc_error_messages, "\n\tExpected %f to equals %f", a, b);
        pc_fail();
    }

}

void assert_not_equals_double_r(double a, double b, int line_number)
{
    pc_total_assertions++;
    if (a == b) 
    {
        fprintf(pc_error_messages, "\nError in test %s:%d", pc_current_test_name, line_number);
        fprintf(pc_error_messages, "\n\tExpected %f to not equals %f", a, b);
        pc_fail();
    }
}

