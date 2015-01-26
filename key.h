typedef struct Key {
    char *filename;
    FILE *file;
    char *data;
    size_t length;
} Key;

Key generate_key(size_t length);
