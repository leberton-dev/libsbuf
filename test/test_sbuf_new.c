#include "sbuf/sbuf.h"
#include <criterion/assert.h>
#include <criterion/criterion.h>

Test(sbuf_new_input, empty_string_accepted)
{
	cr_assert_not_null(sbuf_new(""));
}

Test(sbuf_new_input, null_accepted)
{
	cr_assert_not_null(sbuf_new(NULL));
}

Test(sbuf_new_input, hello_world_string_accepted)
{
	cr_assert_not_null(sbuf_new("Hello World"));
}

Test(sbuf_new_input, string_longer_than_base_cap_accepted)
{
	cr_assert_not_null(sbuf_new("Hello World!Hello World!Hello World!Hello "
	                            "World!Hello World!Hello World!"));
}

Test(sbuf_new_input, string_of_exactly_31_chars_accepted)
{
	cr_assert_not_null(sbuf_new("this_is_line_with_31_characters"));
}

Test(sbuf_new_input, string_of_exactly_32_chars_accepted)
{
	cr_assert_not_null(sbuf_new("this_is_line_with_32_characters_"));
}

Test(sbuf_new_input, string_of_exactly_63_chars_accepted)
{
	cr_assert_not_null(sbuf_new("this_is_line_with_32_characters_this_is_line_"
	                            "with_31_characters"));
}

Test(sbuf_new_input, string_of_exactly_64_chars_accepted)
{
	cr_assert_not_null(sbuf_new("this_is_line_with_32_characters_this_is_line_"
	                            "with_32_characters_"));
}

Test(sbuf_new_output, data_contains_empty_string_on_empty_string)
{
	t_sbuf *sb = sbuf_new("");
	cr_assert_str_eq(sb->data, "");
}

Test(sbuf_new_output, data_contains_empty_string_on_null)
{
	t_sbuf *sb = sbuf_new(NULL);
	cr_assert_str_eq(sb->data, "");
}

Test(sbuf_new_output, data_contains_same_as_input)
{
	char   *s = "Hello World!";
	t_sbuf *sb = sbuf_new(s);
	cr_assert_str_eq(sb->data, s);
}

Test(sbuf_new_output, data_contains_same_as_input_longer_than_cap)
{
	char *s = "this_is_line_with_32_characters_this_is_line_with_32_characters_"
	          "plus_cap";
	t_sbuf *sb = sbuf_new(s);
	cr_assert_str_eq(sb->data, s);
}

Test(sbuf_new_output, len_is_zero_on_empty_string)
{
	t_sbuf *sb = sbuf_new("");
	cr_assert_eq(sb->len, 0);
}

Test(sbuf_new_output, len_is_zero_on_null)
{
	t_sbuf *sb = sbuf_new(NULL);
	cr_assert_eq(sb->len, 0);
}

Test(sbuf_new_output, len_is_length_of_input_string)
{
	char   *s = "Hello World!";
	size_t  len = strlen(s);
	t_sbuf *sb = sbuf_new(s);
	cr_assert_eq(sb->len, len);
}

Test(sbuf_new_output, len_is_length_of_input_string_long_than_cap)
{
	char *s = "this_is_line_with_32_characters_this_is_line_with_32_characters_"
	          "plus_cap";
	size_t  len = strlen(s);
	t_sbuf *sb = sbuf_new(s);
	cr_assert_eq(sb->len, len);
}
