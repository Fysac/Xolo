#include <stdio.h>
#include "key.h"

void xor_op(FILE *input, FILE *output, Key key){
    int i = 0, c;
    while ((c = fgetc(input)) != EOF){
        if (i > key.length - 1){
            i = 0;
        }
        fputc(c ^ key.data[i], output);
        i++;
    }
    fclose(input);
    fclose(output);
}
