#include "sbuf/sbuf.h"
#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>

Test(sbuf_new, empty_string_as_input)
{
	t_sbuf *sb;

	sb = sbuf_new("");
	cr_assert_not_null(sb);
	cr_assert_eq(sb->cap, 64);
	cr_assert_str_eq(sb->data, "");
	cr_assert_eq(sb->len, 0);
}

Test(sbuf_new, null_as_input)
{
	t_sbuf *sb;

	sb = sbuf_new(NULL);
	cr_assert_not_null(sb);
	cr_assert_eq(sb->cap, 64);
	cr_assert_str_eq(sb->data, "");
	cr_assert_eq(sb->len, 0);
}

Test(sbuf_new, normal_string_as_input)
{
	t_sbuf *sb;

	sb = sbuf_new("Hello World!");
	cr_assert_not_null(sb);
	cr_assert_eq(sb->cap, 64);
	cr_assert_str_eq(sb->data, "Hello World!");
	cr_assert_eq(sb->len, strlen("Hello World!"));
}
