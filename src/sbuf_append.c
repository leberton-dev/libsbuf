#include "sbuf/sbuf_internal.h"

#include <stdlib.h>
#include <string.h>

static int sbuf_clear(t_sbuf *sb)
{
	sb->data[0] = '\0';
	sb->len = 0;
	return (EXIT_SUCCESS);
}

static int sbuf_copy_in(t_sbuf *sb, const char *s, size_t len)
{
	memcpy(sb->data + sb->len, s, len);
	sb->len += len;
	sb->data[sb->len] = '\0';
	return (EXIT_SUCCESS);
}

int sbuf_append(t_sbuf *sb, const char *s)
{
	size_t len;

	if (!s)
		return (sbuf_clear(sb));

	len = strlen(s);
	if (sbuf_ensure_cap(sb, len) != EXIT_SUCCESS)
		return (EXIT_FAILURE);

	if (sbuf_copy_in(sb, s, len) != EXIT_SUCCESS)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
