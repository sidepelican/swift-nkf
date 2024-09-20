#include "nkf_wrapper.h"

#undef getc
#define getc(f) swiftnkf_getc(f)
#undef ungetc
#define ungetc(c,f) swiftnkf_ungetc(c,f)
#undef putchar
#define putchar(c) swiftnkf_putchar(c)

#undef TRUE
#undef FALSE

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshorten-64-to-32"

#define PERL_XS 1
#include "config.h"
#include "utf8tbl.c"
#include "nkf.c"

#pragma clang diagnostic pop

void exec_nkf(unsigned char *opts) {
    reinit();
    options(opts);
    kanji_convert(NULL);
}
