#include <stdio.h>
#include <stdlib.h>

char* generate_key(size_t length){
    char *key = calloc(length, sizeof(char));
    FILE *urandom = fopen("/dev/urandom", "r");
    fread(key, sizeof(char), length, urandom);
    return key;
}
