#include <stdio.h>
#include <stdlib.h>

#define SHIFT_VAL 47

void shift_xor_encrypt(FILE *in, FILE *out, const unsigned char *key, size_t keylen) {
    size_t i = 0;
    int ch;
    while ((ch = fgetc(in)) != EOF) {
        unsigned char shifted = (ch + SHIFT_VAL) % 256;
        fputc(shifted ^ key[i % keylen], out);
        i++;
    }
}

int main() {
    const char *input_file = "final_encrypt.out";
    const char *output_file = "encrypted_a.out_L88";

    unsigned char key[] = {0xAB, 0x13, 0x6D, 0xE8, 0x22, 0x4C, 0x7F, 0x99};

    size_t keylen = sizeof(key);

    FILE *fin = fopen(input_file, "rb");
    FILE *fout = fopen(output_file, "wb");

    if (!fin || !fout) {
        perror("File error");
        return 1;
    }

    shift_xor_encrypt(fin, fout, key, keylen);

    fclose(fin);
    fclose(fout);

    printf("Shift+XOR encryption done: %s -> %s\n", input_file, output_file);
    return 0;
}

