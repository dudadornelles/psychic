# psychic

Python-Powered C Unit Testing Library

## Getting Started

Install `psychic`:

```sh
$ pip install psychic
```

Write a test:

```c
void test_sum() {
        assert_equals_int(1+1, 2);
}

void test_string_comparison() {
        assert_equals_str("abc", "abc");
}
```
       
Run:

```sh
$ cd <folder with tests>
$ psychic
        
..

2 tests run, 0 failures, 2 assertions.
Tests ran in 0.000011 secs
```

