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

static int sbuf_grow(t_sbuf *sb, size_t extra)
{
	while (extra >= sb->cap / 2)
		sb->cap *= 2;

	if (!sb)
		sb->data = calloc(sb->cap, sizeof(char));
	else
		sb = realloc(sb, sizeof(t_sbuf) * sb->cap);

	if (!sb)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}

static int sbuf_need_grow(t_sbuf *sb, size_t extra)
{
	return (sb->len + extra >= sb->cap);
}

static int sbuf_clear(t_sbuf *sb)
{
	sb->data[0] = '\0';
	sb->len = 0;
	return (EXIT_SUCCESS);
}

static int sbuf_ensure_cap(t_sbuf *sb, size_t extra)
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

static int sbuf_copy_in(t_sbuf *sb, const char *s, size_t len)
{
	memcpy(sb->data + sb->len, s, len);
	sb->len += len;
	sb->data[sb->len] = '\0';
	return (EXIT_SUCCESS);
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
