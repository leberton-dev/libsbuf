#include "sbuf/sbuf.h"

#include <stdlib.h>
#include <string.h>

t_sbuf *sbuf_new(char *str)
{
	t_sbuf *sb;
	size_t  len;

	sb = malloc(sizeof(t_sbuf));
	if (!sb)
		return (NULL);

	sb->cap = 64;
	len = strlen(str);
	while (len >= sb->cap / 2)
		sb->cap *= 2;

	sb->data = malloc(sizeof(char) * sb->cap);
	if (!sb->data)
	{
		free(sb);
		return (NULL);
	}

	sb->len = 0;
	while (sb->len < str[sb->len])
	{
		sb->data[sb->len] = str[sb->len];
		sb->len++;
	}
	sb->data[sb->len] = '\0';

	return (sb);
}
