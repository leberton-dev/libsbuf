#ifndef SBUF_INTERNAL_H
#define SBUF_INTERNAL_H

#include "sbuf/sbuf.h"

int sbuf_ensure_cap(t_sbuf *sb, size_t extra);

#endif
