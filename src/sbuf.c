#include "sbuf/sbuf.h"

#include <stdlib.h>
#include <string.h>

static size_t _sbuf_initial_cap(const char *str)
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

static t_sbuf *_sbuf_alloc(size_t cap)
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

static int _resize(t_sbuf *sb, size_t extra)
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

static int _sbuf_is_resize_needed(t_sbuf *sb, size_t len)
{
	return (sb->len + len >= sb->cap);
}

static int _sbuf_clear(t_sbuf *sb)
{
	sb->data[0] = '\0';
	sb->len = 0;
	return (EXIT_SUCCESS);
}

static int _sbuf_ensure_cap(t_sbuf *sb, size_t extra)
{
	int err;

	if (_sbuf_is_resize_needed(sb, extra))
	{
		err = _resize(sb, extra);
		if (err != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int _sbuf_copy_in(t_sbuf *sb, const char *s, size_t len)
{
	memcpy(sb->data + sb->len, s, len);
	sb->len += len;
	sb->data[sb->len] = '\0';
	return (EXIT_SUCCESS);
}

static int _sbuf_append_string(t_sbuf *sb, const char *s)
{
	size_t len;

	if (!s)
		return (_sbuf_clear(sb));

	len = strlen(s);
	if (_sbuf_ensure_cap(sb, len) != EXIT_SUCCESS)
		return (EXIT_FAILURE);

	if (_sbuf_copy_in(sb, s, len) != EXIT_SUCCESS)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}

t_sbuf *sbuf_new(char *str)
{
	t_sbuf *sb;

	sb = _sbuf_alloc(_sbuf_initial_cap(str));
	if (!sb)
		return (NULL);
	_sbuf_append_string(sb, str);
	return (sb);
}
