/* XOR-encrypt or decrypt file with provided key.
 * FILE *in: Input file
 * FILE *out: Output file
 * char *key: Key buffer
 * size_t len: Length of key buffer
*/
void xor_crypt(FILE *in, FILE *out, char *key, size_t len);
