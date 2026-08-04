#include "sbuf/sbuf_internal.h"

#include <stdlib.h>

static int sbuf_need_grow(t_sbuf *sb, size_t extra)
{
	return (sb->len + extra >= sb->cap);
}

static int sbuf_grow(t_sbuf *sb, size_t extra)
{
	char *tmp;

	while (extra >= sb->cap / 2)
		sb->cap *= 2;

	tmp = realloc(sb->data, sb->cap);
	if (!tmp)
		return (EXIT_FAILURE);

	sb->data = tmp;
	return (EXIT_SUCCESS);
}

int sbuf_ensure_cap(t_sbuf *sb, size_t extra)
{
	int err;

	if (sbuf_need_grow(sb, extra))
	{
		err = sbuf_grow(sb, extra);
		if (err != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
