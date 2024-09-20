#pragma once

#include <stdio.h>

unsigned char * nkf_convert(unsigned char const *in_buf,
                            int in_size,
                            unsigned char *opts_buf_nullterminated,
                            int *out_size);
