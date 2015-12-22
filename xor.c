#include <stdio.h>
#include "xor.h"

void xor_crypt(FILE *in, FILE *out, char *key, size_t len){
    int i, c;
    for (i = 0; (c = fgetc(in)) != EOF; i++){
        if (i == len){
            i = 0;
        }
        fputc(key[i] ^ c, out);
    }
}
