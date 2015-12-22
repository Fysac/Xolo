#include <stdio.h>
#include <stdlib.h>
#include "key.h"

char* generate_random_key(char *key, size_t len){
    key = malloc(len);

    // *nix CSPRNG is /dev/urandom
    FILE *rng = fopen("/dev/urandom", "r");
    fread(key, 1, len, rng);
    return key;
}

char* read_key_from_file(FILE *f, size_t len){
    char *key = malloc(len);
    fread(key, 1, len, f);
    return key;
}
