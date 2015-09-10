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

void assert(int b)
{
    assert_true(b);
}

void assert_true(int b) 
{
    pc_total_assertions++;
    if (!b) {
        fprintf(pc_error_messages, "\nError in test %s :", pc_current_test_name);
        fprintf(pc_error_messages, "\n\tAssertion Failure.");
        pc_current_test_failed = 1;
    } 
}

void assert_false(int b) 
{
    pc_total_assertions++;
    if (b) {
        fprintf(pc_error_messages, "\nError in test %s :", pc_current_test_name);
        fprintf(pc_error_messages, "\n\tAssertion Failure.");
        pc_fail();
    } 
}

void assert_null(void *p)
{
    pc_total_assertions++;
    if (p != 0)
    {
        fprintf(pc_error_messages, "\nError in test %s :", pc_current_test_name);
        fprintf(pc_error_messages, "\n\tAssertion Failure.");
        pc_fail();
    }
}

void assert_not_null(void *p)
{
    pc_total_assertions++;
    if (p == 0)
    {
        fprintf(pc_error_messages, "\nError in test %s :", pc_current_test_name);
        fprintf(pc_error_messages, "\n\tAssertion Failure.");
        pc_fail();
    }
}

void assert_equals_str(char *a, char *b) 
{
    pc_total_assertions++;
    if (strcmp(a, b) != 0) 
    {
        fprintf(pc_error_messages, "\nError in test %s :", pc_current_test_name);
        fprintf(pc_error_messages, "\n\tExpected %s to equals %s", a, b);
        pc_fail();
    }
}

void assert_not_equals_str(char *a, char *b)
{
    pc_total_assertions++;
    if (strcmp(a, b) == 0) 
    {
        fprintf(pc_error_messages, "\nError in test %s :", pc_current_test_name);
        fprintf(pc_error_messages, "\n\tExpected %s to not equals %s", a, b);
        pc_fail();
    }
}

void assert_equals_int(int a, int b) 
{
    pc_total_assertions++;
    if (a != b) 
    {
        pc_fail();
        fprintf(pc_error_messages, "\nError in test %s :", pc_current_test_name);
        fprintf(pc_error_messages, "\n\tExpected %i to equals %i", a, b);
    }
}

void assert_not_equals_int(int a, int b)
{
    pc_total_assertions++;
    if (a == b) 
    {
        pc_fail();
        fprintf(pc_error_messages, "\nError in test %s :", pc_current_test_name);
        fprintf(pc_error_messages, "\n\tExpected %i to not equals %i", a, b);
    }
}

void assert_equals_float(float a, float b)
{
    pc_total_assertions++;
    if (a != b) 
    {
        fprintf(pc_error_messages, "\nError in test %s :", pc_current_test_name);
        fprintf(pc_error_messages, "\n\tExpected %f to equals %f", a, b);
        pc_fail();
    }
}

void assert_not_equals_float(float a, float b)
{
    pc_total_assertions++;
    if (a != b) 
    {
        fprintf(pc_error_messages, "\nError in test %s :", pc_current_test_name);
        fprintf(pc_error_messages, "\n\tExpected %f to not equals %f", a, b);
        pc_fail();
    }
}

void assert_equals_double(double a, double b)
{
    pc_total_assertions++;
    if (a != b) 
    {
        fprintf(pc_error_messages, "\nError in test %s :", pc_current_test_name);
        fprintf(pc_error_messages, "\n\tExpected %f to equals %f", a, b);
        pc_fail();
    }

}

void assert_not_equals_double(double a, double b)
{
    pc_total_assertions++;
    if (a == b) 
    {
        fprintf(pc_error_messages, "\nError in test %s :", pc_current_test_name);
        fprintf(pc_error_messages, "\n\tExpected %f to not equals %f", a, b);
        pc_fail();
    }
}

