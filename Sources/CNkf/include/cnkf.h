#pragma once

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

unsigned char * nkf_convert(const unsigned char *in_buf,
                            int in_size,
                            unsigned char *opts_buf_nullterminated,
                            int *out_size);

#ifdef __cplusplus
}
#endif
