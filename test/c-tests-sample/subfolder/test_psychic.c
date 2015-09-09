int expected;

void setup() {
        expected = 2;
}

void test_assert_true_r() 
{
        assert_true(1+1 == expected);
        expected = 10;
}

void test_assert_equals_int_r() 
{
        assert_equals_int(2, expected);
}

