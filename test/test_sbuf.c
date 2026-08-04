#include "sbuf/sbuf.h"
#include <criterion/assert.h>
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/logging.h>

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

Test(sbuf_new, cap_updates_correctly)
{
	t_sbuf *sb;

	sb = sbuf_new("Hello World!Hello World!Hello W");
	cr_assert_eq(sb->cap, 64);
	sb = sbuf_new("Hello World!Hello World!Hello Wo");
	cr_assert_eq(sb->cap, 128);
	sb = sbuf_new("Hello World!Hello World!Hello WoHello World!Hello "
	              "World!Hello W");
	cr_assert_eq(sb->cap, 128);
	sb = sbuf_new("Hello World!Hello World!Hello WoHello World!Hello "
	              "World!Hello Wo");
	cr_assert_eq(sb->cap, 256);
}

// === sbuf_append ===

Test(sbuf_append, appends_string)
{
	t_sbuf *sb;
	int     err;

	sb = sbuf_new("Hello");
	err = sbuf_append(sb, " World!");
	cr_assert_eq(err, 0);
	cr_assert_str_eq(sb->data, "Hello World!");
}
