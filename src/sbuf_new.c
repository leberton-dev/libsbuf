#include "sbuf/sbuf.h"

#include <stdlib.h>
#include <string.h>

static size_t sbuf_initial_cap(const char *str)
{
	size_t cap;
	size_t len;

	cap = 64;
	if (!str)
		return (cap);

	len = strlen(str);
	while (len >= cap / 2)
		cap *= 2;
	return (cap);
}

static t_sbuf *sbuf_alloc(size_t cap)
{
	t_sbuf *sb;

	sb = malloc(sizeof(t_sbuf));
	if (!sb)
		return (NULL);

	sb->data = calloc(cap, sizeof(char));
	if (!sb->data)
	{
		free(sb);
		return (NULL);
	}

	sb->cap = cap;
	sb->len = 0;

	return (sb);
}

t_sbuf *sbuf_new(char *str)
{
	t_sbuf *sb;

	sb = sbuf_alloc(sbuf_initial_cap(str));
	if (!sb)
		return (NULL);
	sbuf_append(sb, str);
	return (sb);
}
