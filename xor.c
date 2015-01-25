#include <stdio.h>

char* xor_op(FILE *input, FILE *output, char *key, size_t length){
    int i = 0, c;
    while ((c = fgetc(input)) != EOF){
        if (i > length - 1){
            i = 0;
        }
        fputc(c ^ key[i], output);
        i++;
    }
    fclose(input);
    fclose(output);
}
