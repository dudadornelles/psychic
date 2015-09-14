#ifndef PSYCHIC_H
#define PSYCHIC_H

void assert(int r);

void assert_true_r(int a, int line_number);
#define assert_true(a)  (assert_true_r(a, __LINE__))
#define assert(a)  (assert_true_r(a, __LINE__))

void assert_false_r(int r, int line_number);
#define assert_false(a)  (assert_false_r(a, __LINE__))

void assert_null_r(void *p, int line_number);
#define assert_null(a)  (assert_null_r(a, __LINE__))

void assert_equals_int_r(int a, int b, int line_number);
#define assert_equals_int(a, b)  (assert_equals_int_r(a, b, __LINE__))

void assert_equals_str_r(char *a, char *b, int line_number);
#define assert_equals_str(a, b)  (assert_equals_str_r(a, b, __LINE__))

void assert_equals_char_r(char a, char b);
#define assert_equals_char(a, b) (assert_equals_char_r(a, b, __LINE__))

void assert_equals_float_r(float a, float b, int line_number);
#define assert_equals_float(a, b) (assert_equals_float_r(a, b, __LINE__))

void assert_equals_double_r(double a, double b, int line_number);
#define assert_equals_double(a, b) (assert_equals_double_r(a, b, __LINE__))

void assert_not_null_r(void *p, int line_number);
#define assert_not_null(p) (assert_not_null_r(p, __LINE__))

void assert_not_equals_int_r(int a, int b, int line_number);
#define assert_not_equals_int(a, b) (assert_not_equals_int_r(a, b, __LINE__))

void assert_not_equals_str_r(char *a, char *b, int line_number);
#define assert_not_equals_str(a, b)  (assert_not_equals_str_r(a, b, __LINE__))

void assert_not_equals_char_r(char a, char b, int line_number);
#define assert_not_equals_char(a, b)  (assert_not_equals_char_r(a, b, __LINE__))

void assert_not_equals_float_r(float a, float b, int line_number);
#define assert_not_equals_float(a, b)  (assert_not_equals_float_r(a, b, __LINE__))

void assert_not_equals_double_r(double a, double b, int line_number);
#define assert_not_equals_double(a, b)  (assert_not_equals_double_r(a, b, __LINE__))

#endif
