
void test_assert_true() 
{
        assert_true(1+1 == 2);
}

void test_assert_true_fail() 
{
        assert_true(1+1 == 3);
}

void test_assert_equals_int() 
{
        assert_equals_int(1, 1);
}

void test_assert_equals_int_fail() 
{
        assert_equals_int(1, 2);
}

void test_assert_equals_str() 
{
        assert_equals_str("abc", "abc");
}

void test_assert_equals_str_fail() 
{
        assert_equals_str("abc", "def");
}

void test_assert_null() 
{
        char *c = NULL;
        assert_null(c);
}

void test_assert_null_fail()
{
        char *c = malloc(sizeof(char));
        assert_null(c);
}

