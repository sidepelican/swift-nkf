#pragma once

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

int swiftnkf_getc(FILE *f);
int swiftnkf_ungetc(int c, FILE *f);
void swiftnkf_putchar(int c);

void exec_nkf(unsigned char *opts);

#ifdef __cplusplus
}
#endif

