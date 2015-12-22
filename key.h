#define DEFAULT_KEY_LENGTH 1024

/* Generate random key with data from OS CSPRNG.
 * char *key: Key buffer to fill
 * size_t len: Length of key buffer
 * Returns: Randomly generated key buffer
 */
char* generate_random_key(char *key, size_t len);

/* Read key from file.
 * FILE *f: File to read
 * size_t len: Size of file
 * Returns: Key read from file
 */
char* read_key_from_file(FILE *f, size_t len);
