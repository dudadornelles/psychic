# psychic

Python-Powered C Unit Testing Library.
* Recursively finds all test_*.c files
* Assumes any function name that starts with "test_" to be a test
* Automagically adds the needed headers, you can just go ahead and write assertions
* 

## Getting Started

I swear I looked for them but all C Unit testing libraries didn't cut for me. I wanted to do something like this:

```sh
$ pip install psychic
$ cat test_example.c
void test_sum() {
        assert_equals_int(1+1, 2);
}

void test_string_comparison() {
        assert_equals_str("abc", "abc");
}
$ psychic
        
..

2 tests run, 0 failures, 2 assertions.
```
And that's pretty much how psychic works.

## Assertions
```c
void assert_true(int r);
void assert_false(int r);
void assert_null(void *p);
void assert_equals_int(int a, int b);
void assert_equals_str(char *a, char *b);
void assert_equals_char(char a, char b);
void assert_equals_float(float a, float b);
void assert_equals_double(double a, double b);
```

## Options
--cargs= : adds arguments to the C compiler (a common one will be -I for passing user library paths)
