#include "sbuf/sbuf.h"
#include <criterion/assert.h>
#include <criterion/criterion.h>

Test(sbuf_trim_left, trims_str_starting_with_whitespaces)
{
	t_sbuf *sb;
	int     err;

	sb = sbuf_new("   Hello World!");
	err = sbuf_trim_left(sb);
	cr_assert_eq(err, 0);
	cr_assert_str_eq(sb->data, "Hello World!");
	cr_assert_eq(sb->len, strlen("Hello World!"));
}

Test(sbuf_trim_right, trims_str_ending_with_whitespaces)
{
	t_sbuf *sb;
	int     err;

	sb = sbuf_new("Hello World!     ");
	err = sbuf_trim_right(sb);
	cr_assert_eq(err, 0);
	cr_assert_str_eq(sb->data, "Hello World!");
	cr_assert_eq(sb->len, strlen("Hello World!"));
}
