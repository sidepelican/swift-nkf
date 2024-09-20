#include "cnkf.h"

#include <setjmp.h>

static int swiftnkf_getc(FILE *f);
static int swiftnkf_ungetc(int c, FILE *f);
static void swiftnkf_putchar(int c);

#define BUFFER_STRETCH 2

#undef getc
#define getc(f) \
swiftnkf_getc(f)
#undef ungetc
#define ungetc(c,f) \
swiftnkf_ungetc(c,f)
#undef putchar
#define putchar(c) \
swiftnkf_putchar(c)

#undef TRUE
#undef FALSE

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshorten-64-to-32"

#define PERL_XS 1
#include "config.h"
#include "utf8tbl.c"
#include "nkf.c"

#pragma clang diagnostic pop

static unsigned char *swiftnkf_ibuf;
static unsigned char *swiftnkf_obuf;
static unsigned char *swiftnkf_iptr;
static unsigned char *swiftnkf_optr;
static int swiftnkf_isize;
static int swiftnkf_osize;
static int swiftnkf_icount;
static int swiftnkf_ocount;

static jmp_buf panic;

static int swiftnkf_getc(FILE *f) {
    if (swiftnkf_icount >= swiftnkf_isize) return EOF;

    unsigned char c = *swiftnkf_iptr++;
    swiftnkf_icount++;
    return (int)c;
}

static int swiftnkf_ungetc(int c, FILE *f) {
    if (swiftnkf_icount--) {
        *(--swiftnkf_iptr) = c;
        return c;
    } else {
        return EOF;
    }
}

static void swiftnkf_putchar(int c) {
    if (swiftnkf_ocount--) {
        *swiftnkf_optr++ = c;
    } else {
        size_t size      = swiftnkf_osize * BUFFER_STRETCH;
        unsigned char *p = (unsigned char *)realloc(swiftnkf_obuf, size + 1);

        if (swiftnkf_obuf == NULL){
            longjmp(panic, 1);
        }

        swiftnkf_obuf   = p;
        swiftnkf_optr   = swiftnkf_obuf + swiftnkf_osize;
        swiftnkf_ocount = swiftnkf_osize;
        swiftnkf_osize  = (int)size;

        *swiftnkf_optr++ = c;
        swiftnkf_ocount--;
    }
}

//__attribute__((constructor))
//static void init() {
//    reinit();
//}

unsigned char * nkf_convert(unsigned char const *in_buf,
                            int in_size,
                            unsigned char *opts_buf_nullterminated,
                            int *out_size)
{
    swiftnkf_isize = in_size + 1;
    swiftnkf_osize = in_size * BUFFER_STRETCH;
    swiftnkf_obuf  = (unsigned char *)malloc(swiftnkf_osize + 1);

    if (swiftnkf_obuf == NULL) {
        // failed to allocate memory
        return NULL;
    }

    swiftnkf_obuf[0]    = '\0';
    swiftnkf_ocount     = swiftnkf_osize;
    swiftnkf_optr       = swiftnkf_obuf;
    swiftnkf_icount     = 0;
    swiftnkf_ibuf       = (unsigned char*)in_buf;
    swiftnkf_iptr       = swiftnkf_ibuf;

    if (setjmp(panic) == 0) {
        reinit();
        options(opts_buf_nullterminated);
        kanji_convert(NULL);
    } else {
        // failed to allocate memory
        free(swiftnkf_obuf);
        return NULL;
    }

    *swiftnkf_optr = 0;
    *out_size = (int)(swiftnkf_optr - swiftnkf_obuf);

    return swiftnkf_obuf;
}
