#define DEFAULT_KEY_LENGTH 1024

char* generate_random_key(char *key, size_t len);
char* read_key_from_file(FILE *f, size_t len);
