#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "key.h"
#include "xor.h"

void print_usage(void);

int main(int argc, char *argv[]){
    char *input_name, *output_name, *keyfile_name = "KEYFILE";
    FILE *input = NULL, *output = NULL, *keyfile = NULL;
    char *key;
    size_t length = 100;
    int option;

    if (argc < 2){
        print_usage();
        return EXIT_FAILURE;
    }

    while ((option = getopt(argc, argv, "hd:l:")) != -1) {
        switch (option) {
            case 'h':
                print_usage();
                return EXIT_SUCCESS;
            case 'd':
                keyfile_name = optarg;
                keyfile = fopen(keyfile_name, "r");

                if (keyfile == NULL){
                    fprintf(stderr, "%s: keyfile not found\n", keyfile_name);
                    print_usage();
                    return EXIT_FAILURE;
                }
                break;
            case 'l':
                length = atoi(optarg);
                break;
            default:
                print_usage();
                return EXIT_FAILURE;
        }
    }

    input_name = argv[optind];
    output_name = argv[optind + 1];

    input = fopen(input_name, "r");
    if (input == NULL){
        fprintf(stderr, "%s: file not found\n", input_name);
        print_usage();
        return EXIT_FAILURE;
    }
    output = fopen(output_name, "w");

    // Encrypt mode
    if (keyfile == NULL){
        key = generate_key(length);
        keyfile = fopen(keyfile_name, "w");
        fwrite(key, sizeof(char), length, keyfile);
        printf("encrypting: %s\nkeyfile: %s (length %lu)\noutput: %s\n", input_name, keyfile_name, length, output_name);
    }

    // Decrypt mode
    else {
        int i = 0;
        while (fgetc(keyfile) != EOF){
            i++;
        }
        length = i;
        key = calloc(length, sizeof(char));
        i = 0;

        fseek(keyfile, 0, SEEK_SET);
        while ((key[i] = fgetc(keyfile)) != EOF){
            i++;
        }
        printf("decrypting: %s\nkeyfile: %s (length %lu)\noutput: %s\n", input_name, keyfile_name, length, output_name);
    }

    xor_op(input, output, key, length);
    return EXIT_SUCCESS;
}

void print_usage(){
    fprintf(stderr, "usage: xolo [OPTIONS] <input file> <output file>\n");
    fprintf(stderr, "-h, --help\t\t\tShow usage.\n");
    fprintf(stderr, "-d, --decrypt=KEYFILE\t\tDecrypt using specified key file.\n");
    fprintf(stderr, "-l, --key-length=NUMBER\t\tForce encryption key length, in bytes. Defaults\n\t\t\t\tto 100.\n");
}
