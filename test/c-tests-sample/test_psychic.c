
void test_assertions ()
{
        char *c;

        assert(1+1 == 2);
        assert(1+1 == 3);

        assert_true(1+1 == 2);
        assert_true(1+1 == 3);

        assert_false(1+1 == 3);
        assert_false(1+1 == 2);
        
        assert_equals_int(1, 1);
        assert_equals_int(1, 2);

        assert_not_equals_int(1, 2);
        assert_not_equals_int(1, 1);
        
        assert_equals_int(1, 1);
        assert_equals_int(1, 2);

        assert_not_equals_int(1, 2);
        assert_not_equals_int(1, 1);

        assert_equals_str("abc", "abc");
        assert_equals_str("abc", "def");

        assert_not_equals_str("abc", "def");
        assert_not_equals_str("abc", "abc");

        c = NULL;
        assert_null(c);
        c = malloc(sizeof(char));
        assert_null(c);

        c = malloc(sizeof(char));
        assert_not_null(c);
        c = NULL;
        assert_not_null(c);

        assert_equals_float(2.0, 2.0);
        assert_equals_float(2.0, 2.1);

        assert_not_equals_float(2.0, 2.1);
        assert_not_equals_float(2.0, 2.0);

        assert_equals_double(2.0, 2.0);
        assert_equals_double(2.0, 2.1);

        assert_not_equals_double(2.0, 2.1);
        assert_not_equals_double(2.0, 2.0);
}

