#include "cnkf.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshorten-64-to-32"

#include "config.h"
#include "utf8tbl.c"
#include "nkf.c"

#pragma clang diagnostic pop

void aa() {
    kanji_convert(NULL);
}

void hello(void) {
//    kanji_convert(NULL);
    printf("hello, world\n");
}
