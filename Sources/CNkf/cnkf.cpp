#include "cnkf.h"
#include "nkf_wrapper.h"

#include <string>
#include <vector>

static std::vector<unsigned char> swiftnkf_ibuf;
static std::vector<unsigned char>::iterator swiftnkf_iitr;
static std::vector<unsigned char> swiftnkf_obuf;

extern "C" {
    int swiftnkf_getc(FILE *f) {
        if (swiftnkf_iitr == swiftnkf_ibuf.end()) {
            return EOF;
        }

        return *(swiftnkf_iitr++);
    }
    
    int swiftnkf_ungetc(int c, FILE *f) {
        if (swiftnkf_iitr == swiftnkf_ibuf.begin()) {
            return EOF;
        }

        *(--swiftnkf_iitr) = c;
        return c;
    }
    
    void swiftnkf_putchar(int c) {
        swiftnkf_obuf.push_back(static_cast<unsigned char>(c));
    }
}

unsigned char * nkf_convert(const unsigned char *in_buf,
                            int in_size,
                            unsigned char *opts_buf_nullterminated,
                            int *out_size) {
    swiftnkf_ibuf.assign(in_buf, in_buf + in_size);
    swiftnkf_iitr = swiftnkf_ibuf.begin();
    swiftnkf_obuf = {};

    exec_nkf(opts_buf_nullterminated);

    *out_size = static_cast<int>(swiftnkf_obuf.size());
    return swiftnkf_obuf.data();
}
