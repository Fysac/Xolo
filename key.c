#include <stdio.h>
#include <stdlib.h>
#include "key.h"

Key generate_key(size_t length){
    Key key = {"KEYFILE", NULL, calloc(length, sizeof(char)), length};
    FILE *urandom = fopen("/dev/urandom", "r");
    fread(key.data, sizeof(char), key.length, urandom);
    return key;
}

Key read_key(FILE* file){
    int i = 0;
    while (fgetc(key.file) != EOF){
        i++;
    }
    key.length = i;
    key.data = calloc(key.length, sizeof(char));
    i = 0;

    fseek(key.file, 0, SEEK_SET);
    while ((key.data[i] = fgetc(key.file)) != EOF){
        i++;
    }
}
