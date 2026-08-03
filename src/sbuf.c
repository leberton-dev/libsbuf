#include "sbuf/sbuf.h"

#include <stdlib.h>
#include <string.h>

static int _resize(t_sbuf *sb, size_t l)
{
	while (l >= sb->cap / 2)
		sb->cap *= 2;
	if (!sb)
		sb->data = calloc(sb->cap, sizeof(char));
	else
		sb = realloc(sb, sizeof(t_sbuf) * sb->cap);
	if (!sb)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int _sbuf_is_resize_needed(t_sbuf *sb, const char *s)
{
	return (sb->len + strlen(s) >= sb->cap);
}

static int _sbuf_append_string(t_sbuf *sb, const char *s)
{
	int err;

	if (!s)
	{
		sb->data[0] = '\0';
		return (EXIT_SUCCESS);
	}

	if (_sbuf_is_resize_needed(sb, s))
	{
		err = _resize(sb, strlen(s));
		if (err != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}

	while (*s != '\0')
	{
		sb->data[sb->len] = *s;
		sb->len++;
		s++;
	}
	sb->data[sb->len] = '\0';

	return (EXIT_SUCCESS);
}

t_sbuf *sbuf_new(char *str)
{
	t_sbuf *sb;
	size_t  len;

	sb = malloc(sizeof(t_sbuf));
	if (!sb)
		return (NULL);

	sb->cap = 64;
	if (str)
	{
		len = strlen(str);
		while (len >= sb->cap / 2)
			sb->cap *= 2;
	}

	sb->data = calloc(sb->cap, sizeof(char));
	if (!sb->data)
	{
		free(sb);
		return (NULL);
	}

	sb->len = 0;
	_sbuf_append_string(sb, str);

	return (sb);
}
