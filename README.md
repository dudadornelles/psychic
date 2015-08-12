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

# psychic

Python-Powered C Unit Testing Library

## Options

        --cargs= : adds arguments to the C compiler (a common one will be -I for passing user library paths)
