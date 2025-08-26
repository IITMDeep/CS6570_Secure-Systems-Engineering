#include <stdio.h>
#include <stdlib.h>

#define SHIFT_VAL 47
#define ROTATE_BITS 3

unsigned char rotate_left(unsigned char byte, int bits) {
    return ((byte << bits) | (byte >> (8 - bits))) & 0xFF;
}

void complex_encrypt(FILE *in, FILE *out, const unsigned char *key, size_t keylen) {
    size_t i = 0;
    int ch;

    while ((ch = fgetc(in)) != EOF) {
        unsigned char b = (unsigned char)ch;

        switch (i % 3) {
            case 0:
                b = rotate_left(b, ROTATE_BITS);
                b = (b + SHIFT_VAL) % 256;
                b ^= key[i % keylen];
                break;
            case 1:
                b = (b + SHIFT_VAL) % 256;
                b ^= key[i % keylen];
                b = rotate_left(b, ROTATE_BITS);
                break;
            case 2:
                b ^= key[i % keylen];
                b = rotate_left(b, ROTATE_BITS);
                b = (b + SHIFT_VAL) % 256;
                break;
        }

        fputc(b, out);
        i++;
    }
}

int main() {
    const char *input_file = "final_encrypt_L88.out";
    const char *output_file = "encrypted_a.out_L89";

    unsigned char key[] = {0x3E, 0x77, 0xC2, 0x91, 0xD4, 0x5A, 0xB8, 0x0F};

    size_t keylen = sizeof(key);

    FILE *fin = fopen(input_file, "rb");
    FILE *fout = fopen(output_file, "wb");

    if (!fin || !fout) {
        perror("File error");
        return 1;
    }

    complex_encrypt(fin, fout, key, keylen);

    fclose(fin);
    fclose(fout);

    printf("Multilayer encryption complete: %s -> %s\n", input_file, output_file);
    return 0;
}

