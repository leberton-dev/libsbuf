#include "sbuf/sbuf.h"
#include <ctype.h>

int sbuf_remove_char(t_sbuf *sb, size_t idx)
{
	for (size_t j = idx; j < sb->len; j++)
		sb->data[j] = sb->data[j + 1];
	sb->len--;
	return (EXIT_SUCCESS);
}

int sbuf_trim_left(t_sbuf *sb)
{
	while (isspace(sb->data[0]))
		sbuf_remove_char(sb, 0);
	return (EXIT_SUCCESS);
}

int sbuf_trim_right(t_sbuf *sb)
{
	while (isspace(sb->data[sb->len - 1]))
		sbuf_remove_char(sb, sb->len - 1);
	return (EXIT_SUCCESS);
}

int sbuf_trim(t_sbuf *sbuf)
{
	int err;

	err = sbuf_trim_left(sbuf);
	if (err != EXIT_SUCCESS)
		return (EXIT_FAILURE);

	err = sbuf_trim_right(sbuf);
	if (err != EXIT_SUCCESS)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
