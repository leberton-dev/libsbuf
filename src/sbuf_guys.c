#include "sbuf/sbuf.h"
#include <strings.h>

void sb_reset(t_sbuf *sb)
{
	sb_free(sb);
	sb = sbuf_new("");
}

void sb_free(t_sbuf *sb)
{
	free(sb->data);
	free(sb);
}
