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

std::vector<uint8_t> nkf_convert(const std::vector<uint8_t>& input,
                                 const std::string& options) {
    swiftnkf_ibuf = input;
    swiftnkf_iitr = swiftnkf_ibuf.begin();
    swiftnkf_obuf = std::vector<uint8_t>();

    exec_nkf(reinterpret_cast<unsigned char *>(const_cast<char *>(options.c_str())));

    return swiftnkf_obuf;
}
