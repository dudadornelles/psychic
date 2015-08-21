#ifndef PSYCHIC_H
#define PSYCHIC_H

void assert(int r);
void assert_true(int r);
void assert_false(int r);
void assert_null(void *p);
void assert_not_null(void *p);
void assert_equals_int(int a, int b);
void assert_equals_str(char *a, char *b);
void assert_equals_char(char a, char b);
void assert_equals_float(float a, float b);
void assert_equals_double(double a, double b);

#endif
