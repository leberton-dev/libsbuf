#include <stdio.h>

#include "sbuf/sbuf.h"

int main(void)
{
	t_sbuf *sb = sbuf_new("Hello world\n");
	printf(sb->data);

	return (0);
}
