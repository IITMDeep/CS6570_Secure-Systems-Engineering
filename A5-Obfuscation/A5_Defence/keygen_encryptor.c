// generate_key_header.c
#include <stdio.h>
#include <stdint.h>

int main() {
    uint8_t key[16] = {0xbe, 0xa0, 0x5f, 0xcd, 0x0a, 0x3f, 0x59, 0x60, 0x01, 0xe3, 0xe7, 0x71, 0x3b, 0xad, 0xc7, 0x76};

    uint8_t xor1 = 0x69;
    uint8_t xor2 = 0x3C;
    uint8_t xor3 = 0xA5;

    for (int i = 0; i < 16; i++) {
        key[i] ^= xor1;
        key[i] ^= xor2;
        key[i] ^= xor3;
    }

    FILE *fp = fopen("embedded_key.h", "w");
    if (!fp) return 1;

    fprintf(fp, "#ifndef EMBEDDED_KEY_H\n#define EMBEDDED_KEY_H\n\n");
    fprintf(fp, "static const unsigned char embedded_key[16] = {");
    for (int i = 0; i < 16; ++i) {
        fprintf(fp, "0x%02X", key[i]);
        if (i < 15) fprintf(fp, ", ");
    }
    fprintf(fp, "};\n\n#endif\n");

    fclose(fp);
    return 0;
}

