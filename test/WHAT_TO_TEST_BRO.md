## WHAT SHOULD I TEST

### FOR sbuf_new
#### INPUT
- [x] empty string accepted
- [x] null accepted
- [x] normal (Hello World!) works
- [ ] string longer than base cap accepted
- [ ] string of exactly 31 chars accepted (just under grow boundary)
- [ ] string of exactly 32 chars accepted (grow boundary)
- [ ] string of exactly 63 chars accepted (just under grow boundary)
- [ ] string of exactly 64 chars accepted (grow boundary)

#### OUTPUT
- [x] updates correctly
- [ ] `t_sbuf.data` contains input string on empty string
- [ ] `t_sbuf.data` contains input string on null (`""`)
- [ ] `t_sbuf.data` contains input string on normal string
- [ ] `t_sbuf.data` contains input string on longer than base cap string
- [ ] `t_sbuf.len` is the correct length on empty string (0)
- [ ] `t_sbuf.len` is the correct length on null (0)
- [ ] `t_sbuf.len` is the correct length on normal string
- [ ] `t_sbuf.len` is the correct length on longer than base cap string
- [ ] `t_sbuf.cap` is the correct size on empty string (64)
- [ ] `t_sbuf.cap` is the correct size on on null (64)
- [ ] `t_sbuf.cap` is the correct size on normal string (64)
- [ ] `t_sbuf.cap` is 64 for a 31 char string (no grow yet)
- [ ] `t_sbuf.cap` is 128 for a 32 char string (grow triggered)
- [ ] `t_sbuf.cap` is 128 for a 63 char string (no second grow yet)
- [ ] `t_sbuf.cap` is 256 for a 64 char string (second grow triggered)

#### RETURN VALUE
- [ ] returns non-`NULL` on empty string
- [ ] returns non-`NULL` on null
- [ ] returns non-`NULL` on normal string
- [ ] returns non-`NULL` on longer than base cap string
- [ ] returns `NULL` on allocation failure

### For sbuf_append
#### INPUT
- [ ] empty string accepted
- [ ] null accepted
- [ ] normal (Hello World!) works
- [ ] string longer than `t_sbuf.cap` accepted
- [ ] string where `len + strlen(s) == cap - 1` accepted (no grow boundary)
- [ ] string where `len + strlen(s) == cap` accepted (grow boundary)
- [ ] two successive appends on the same `t_sbuf` accepted

#### OUTPUT
- [ ] `t_sbuf.data` has nothing appended on empty string
- [ ] `t_sbuf.data` has nothing appended on null
- [ ] `t_sbuf.data` contains input string appended on normal string
- [ ] `t_sbuf.data` contains input string appended on longer than `t_sbuf.cap` string
- [ ] `t_sbuf.data` contains both strings in order after two successive appends
- [ ] `t_sbuf.len`  has not changed on empty string
- [ ] `t_sbuf.len`  has not changed on null
- [ ] `t_sbuf.len`  changed and growed of strlen normal string
- [ ] `t_sbuf.len`  changed and growed of strlen longer than `t_sbuf.cap` string
- [ ] `t_sbuf.len`  accumulates correctly across two successive appends
- [ ] `t_sbuf.cap`  has not changed on empty string
- [ ] `t_sbuf.cap`  has not changed on null
- [ ] `t_sbuf.cap`  has not changed on normal string
- [ ] `t_sbuf.cap`  growed because of string longer than `t_sbuf.cap`
- [ ] `t_sbuf.cap`  has not changed when `len + strlen(s) == cap - 1`
- [ ] `t_sbuf.cap`  growed when `len + strlen(s) == cap`
- [ ] `t_sbuf.cap`  growed correctly on a second append on a non-empty buffer

#### RETURN VALUE
- [ ] returns `EXIT_SUCCESS` on empty string
- [ ] returns `EXIT_SUCCESS` on null
- [ ] returns `EXIT_SUCCESS` on normal string
- [ ] returns `EXIT_SUCCESS` on longer than `t_sbuf.cap` string
- [ ] returns `EXIT_FAILURE` on allocation failure

### FOR sbuf_append_len
#### INPUT
- [ ] null `s` accepted
- [ ] `n == 0` with non-null `s` accepted (no-op, no crash)
- [ ] normal string with matching `n` accepted
- [ ] `s` containing an embedded `\0` byte before `n` accepted
- [ ] `n` longer than `t_sbuf.cap` accepted

#### OUTPUT
- [ ] `t_sbuf.data` has nothing appended on null `s`
- [ ] `t_sbuf.data` has nothing appended on `n == 0`
- [ ] `t_sbuf.data` contains first `n` bytes of `s` appended on normal case
- [ ] `t_sbuf.data` contains the embedded `\0` byte appended, not truncated at it
- [ ] `t_sbuf.data` contains `n` bytes appended when `n` longer than `t_sbuf.cap`
- [ ] `t_sbuf.len`  has not changed on null `s`
- [ ] `t_sbuf.len`  has not changed on `n == 0`
- [ ] `t_sbuf.len`  grew by `n` on normal case
- [ ] `t_sbuf.len`  grew by `n` (not `strlen`) on embedded-`\0` case
- [ ] `t_sbuf.len`  grew by `n` when `n` longer than `t_sbuf.cap`
- [ ] `t_sbuf.cap`  has not changed on null `s`
- [ ] `t_sbuf.cap`  has not changed on `n == 0`
- [ ] `t_sbuf.cap`  has not changed on normal case
- [ ] `t_sbuf.cap`  growed when `n` longer than `t_sbuf.cap`

#### RETURN VALUE
- [ ] returns `EXIT_SUCCESS` on null `s`
- [ ] returns `EXIT_FAILURE` on `n == 0`
- [ ] returns `EXIT_SUCCESS` on normal case
- [ ] returns `EXIT_SUCCESS` on `n` longer than `t_sbuf.cap`

### FOR sbuf_append_char
#### INPUT
- [ ] normal char (e.g. `'a'`) accepted
- [ ] `'\0'` char accepted
- [ ] char appended right at the `t_sbuf.cap` boundary (triggers grow) accepted

#### OUTPUT
- [ ] `t_sbuf.data` has the char appended at position `len`
- [ ] `t_sbuf.data` is still null-terminated after append (`data[len] == '\0'`) — **check closely: `sbuf_append_char` (`src/sbuf_append.c:55-64`) never writes a terminator, unlike the other append functions**
- [ ] `t_sbuf.len`  incremented by 1
- [ ] `t_sbuf.cap`  has not changed when below the grow boundary
- [ ] `t_sbuf.cap`  growed when appended right at the boundary

#### RETURN VALUE
- [ ] returns `EXIT_SUCCESS` on normal char
- [ ] returns `EXIT_FAILURE` on allocation failure

### FOR sb_free
#### INPUT
- [ ] valid `t_sbuf*` with content accepted, no crash
- [ ] valid `t_sbuf*` on an empty buffer accepted, no crash
- [ ] no memory leak after free (check with valgrind/ASan)
- [ ] `NULL` sbuf pointer — **currently crashes: no null-check before `sb->data` (`src/sbuf_guys.c:10-14`)**

### FOR sb_reset
#### INPUT
- [ ] valid `t_sbuf*` with content accepted, no crash

#### OUTPUT
- [ ] `t_sbuf.data` is emptied (`""`) after reset — **currently fails: `sb_reset` only reassigns its local copy of `sb` (`src/sbuf_guys.c:4-8`), the caller's pointer keeps pointing at freed memory**
- [ ] `t_sbuf.len` is 0 after reset
- [ ] `t_sbuf.cap` is back to base cap (64) after reset
- [ ] no memory leak after reset (old buffer freed, new buffer reachable from caller)

### FOR sbuf_trim_left
#### INPUT
- [ ] empty buffer (`len == 0`) accepted, no crash
- [ ] string with no leading whitespace accepted
- [ ] string with leading whitespace accepted
- [ ] string that is entirely whitespace accepted
- [ ] string containing a non-ASCII / high-bit byte accepted — `isspace` is called on a plain `char` (`src/sbuf_trim.c:14`), UB risk if the byte is negative

#### OUTPUT
- [ ] `t_sbuf.data` unchanged on empty buffer
- [ ] `t_sbuf.data` unchanged when no leading whitespace
- [ ] `t_sbuf.data` has leading whitespace removed, rest preserved
- [ ] `t_sbuf.data` is empty when string is entirely whitespace
- [ ] `t_sbuf.len`  unchanged on empty buffer
- [ ] `t_sbuf.len`  unchanged when no leading whitespace
- [ ] `t_sbuf.len`  reduced by the count of leading whitespace chars removed
- [ ] `t_sbuf.len`  is 0 when string is entirely whitespace
- [ ] `t_sbuf.cap`  never changes (trim never grows/shrinks cap)

#### RETURN VALUE
- [ ] returns `EXIT_SUCCESS` in every case (no failure path currently exists)

### FOR sbuf_trim_right
#### INPUT
- [ ] empty buffer (`len == 0`) accepted — **currently crashes: `sb->len - 1` underflows since `len` is `size_t` (`src/sbuf_trim.c:21`)**
- [ ] string with no trailing whitespace accepted
- [ ] string with trailing whitespace accepted
- [ ] string that is entirely whitespace accepted

#### OUTPUT
- [ ] `t_sbuf.data` unchanged when no trailing whitespace
- [ ] `t_sbuf.data` has trailing whitespace removed, rest preserved
- [ ] `t_sbuf.data` is empty when string is entirely whitespace
- [ ] `t_sbuf.len`  unchanged when no trailing whitespace
- [ ] `t_sbuf.len`  reduced by the count of trailing whitespace chars removed
- [ ] `t_sbuf.len`  is 0 when string is entirely whitespace
- [ ] `t_sbuf.cap`  never changes

#### RETURN VALUE
- [ ] returns `EXIT_SUCCESS` in every case (no failure path currently exists)

### FOR sbuf_trim
#### INPUT
- [ ] empty buffer accepted — inherits the `sbuf_trim_right` underflow bug above
- [ ] string with leading and trailing whitespace accepted
- [ ] string with whitespace only in the middle accepted (should NOT be removed)
- [ ] string that is entirely whitespace accepted

#### OUTPUT
- [ ] `t_sbuf.data` has both leading and trailing whitespace removed
- [ ] `t_sbuf.data` preserves internal whitespace (only edges trimmed)
- [ ] `t_sbuf.data` is empty when string is entirely whitespace
- [ ] `t_sbuf.len`  reflects the combined removal of leading + trailing whitespace

#### RETURN VALUE
- [ ] returns `EXIT_SUCCESS` on the success path
- [ ] propagates `EXIT_FAILURE` if `sbuf_trim_left`/`sbuf_trim_right` fail (currently unreachable, both always return `EXIT_SUCCESS`)

