#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "key.h"
#include "xor.h"

void print_usage();

void print_usage(char *prog){
    printf("usage: %s [options] <input> <output>\n", prog);
    printf("-h\tShow usage\n");
    printf("-k\tUse existing key (default: generate random key)\n");
    printf("-b\tGenerate this many bytes for key (default: 1024)\n");
}

int main(int argc, char *argv[]){
    char *key;
    FILE *kf;
    size_t len = DEFAULT_KEY_LENGTH;

    char opt;
    while ((opt = getopt(argc, argv, "hk:b:")) != -1) {
        switch (opt) {
            // -h: help
            case 'h':
                print_usage(argv[0]);
                return EXIT_SUCCESS;

            // -k: use existing key
            case 'k':
                kf = fopen(optarg, "r");
                if (kf == NULL){
                    fprintf(stderr, "%s: key not found\n", optarg);
                    return EXIT_FAILURE;
                }

                fseek(kf, 0, SEEK_END);
                len = ftell(kf);
                rewind(kf);

                printf("using key: %s\n", optarg);
                key = read_key_from_file(kf, len);
                fclose(kf);
                break;

            // -b: key length in bytes
            case 'b':
                len = atoi(optarg);
                break;

            default:
                fprintf("unrecognized option: -%c. use -h for help.", opt);
                return EXIT_FAILURE;
        }
    }

    FILE *in = fopen(argv[optind], "r");
    FILE *out = fopen(argv[optind + 1], "w");
    if (in == NULL){
        fprintf(stderr, "%s: file not found\n", argv[optind]);
        return EXIT_FAILURE;
    }

    // Encrypt mode
    if (kf == NULL){
        key = generate_random_key(key, len);

        printf("key for %s:\n%s", argv[optind + 1], key);
        fwrite(key, 1, len, kf);
        printf("encrypting: %s\nkey: %s (length %luB)\noutput: %s\n", argv[optind], fname, len, argv[optind + 1]);
    }

    // Decrypt mode
    else {
        fseek(kf, 0, SEEK_END);
        key = read_key_from_file(kf, len);

        printf("decrypting: %s\nkey: %s (length %luB)\noutput: %s\n", argv[optind], key.filename, len, argv[optind + 1]);
    }
    fclose(kf);

    xor_crypt(in, out, key, len);
    
    fclose(in);
    fclose(out);
    return EXIT_SUCCESS;
}
