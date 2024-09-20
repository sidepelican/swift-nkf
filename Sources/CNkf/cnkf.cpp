#include "cnkf.h"
#include "nkf_wrapper.h"

#include <string>
#include <vector>

static std::vector<uint8_t> swiftnkf_ibuf;
static std::vector<uint8_t>::iterator swiftnkf_iitr;
static std::vector<uint8_t> swiftnkf_obuf;

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
        swiftnkf_obuf.push_back(static_cast<uint8_t>(c));
    }
}

unsigned char * nkf_convert(const unsigned char *in_buf,
                            int in_size,
                            unsigned char *opts_buf_nullterminated,
                            int *out_size) {
    swiftnkf_ibuf.assign(in_buf, in_buf + in_size);
    swiftnkf_iitr = swiftnkf_ibuf.begin();
    swiftnkf_obuf = std::vector<uint8_t>();

    exec_nkf(opts_buf_nullterminated);

    *out_size = static_cast<int>(swiftnkf_obuf.size());
    return swiftnkf_obuf.data();
}
