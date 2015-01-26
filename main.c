#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "key.h"
#include "xor.h"

#define DEFAULT_KEY_LENGTH 100

void print_usage(void);

void print_usage(){
    fprintf(stderr, "usage: xolo [OPTIONS] <input file> <output file>\n");
    fprintf(stderr, "-h, --help\t\t\tShow usage.\n");
    fprintf(stderr, "-d, --decrypt=KEYFILE\t\tDecrypt using specified key file.\n");
    fprintf(stderr, "-l, --key-length=NUMBER\t\tForce encryption key length, in bytes. Defaults\n\t\t\t\tto 100.\n");
}

int main(int argc, char *argv[]){
    Key key = {NULL, NULL, NULL, DEFAULT_KEY_LENGTH};
    char *input_name, *output_name;
    FILE *input = NULL, *output = NULL;
    int option;

    if (argc < 2){
        print_usage();
        return EXIT_FAILURE;
    }

    while ((option = getopt(argc, argv, "hd:l:")) != -1) {
        switch (option) {
            // Help
            case 'h':
                print_usage();
                return EXIT_SUCCESS;

            // Decrypt
            case 'd':
                key.filename = optarg;
                key.file = fopen(key.filename, "r");

                if (key.file == NULL){
                    fprintf(stderr, "%s: keyfile not found\n", key.filename);
                    print_usage();
                    return EXIT_FAILURE;
                }
                printf("keyfile: %s\n", key.filename);
                break;

            // Force key length
            case 'l':
                key.length = atoi(optarg);
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
    if (key.file == NULL){
        key = generate_key(key.length);
        key.file = fopen(key.filename, "w");
        fwrite(key.data, sizeof(char), key.length, key.file);
        printf("encrypting: %s\nkeyfile: %s (length %lu)\noutput: %s\n", input_name, key.filename, key.length, output_name);
    }

    // Decrypt mode
    else {
        key = read_key(key.file);
        printf("decrypting: %s\nkeyfile: %s (length %lu)\noutput: %s\n", input_name, key.filename, key.length, output_name);
    }

    xor_op(input, output, key);
    return EXIT_SUCCESS;
}
