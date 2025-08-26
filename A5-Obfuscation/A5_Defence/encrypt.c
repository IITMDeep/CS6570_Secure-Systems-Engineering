#include <stdio.h>
#include <stdlib.h>

void xor_process(FILE *in, FILE *out, const unsigned char *key, size_t keylen) {
    size_t i = 0;
    int ch;
    while ((ch = fgetc(in)) != EOF) {
        fputc(ch ^ key[i % keylen], out);
        i++;
    }
}

int main() {
    const char *input_file = "a.out";
    const char *output_file = "encrypted_a.out";

    // Constant hexadecimal key
    unsigned char key[] = {0x6A, 0x2F, 0x9C, 0x41, 0x88, 0x3D, 0x17, 0xB2};
    size_t keylen = sizeof(key);

    FILE *fin = fopen(input_file, "rb");
    FILE *fout = fopen(output_file, "wb");

    if (!fin || !fout) {
        perror("File error");
        return 1;
    }

    xor_process(fin, fout, key, keylen);

    fclose(fin);
    fclose(fout);

    printf("Encryption done: %s -> %s\n", input_file, output_file);
    return 0;
}

