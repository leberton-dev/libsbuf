#ifndef SBUF_H
#define SBUF_H

#include <stdlib.h>

typedef struct s_sbuf
{
	char  *data; // buffer - always null-terminated
	size_t len;  // data length
	size_t cap;  // allocated length
} t_sbuf;

t_sbuf *sbuf_new(char *str);
int     sbuf_append(t_sbuf *sb, const char *s);
int     sbuf_append_len(t_sbuf *sb, const char *s, size_t n);
int     sbuf_append_char(t_sbuf *sb, char c);
int     sbuf_append_fmt(t_sbuf *sb, const char *fmt, ...);
void    sb_reset(t_sbuf *sb);
void    sb_free(t_sbuf *sb);

#endif
