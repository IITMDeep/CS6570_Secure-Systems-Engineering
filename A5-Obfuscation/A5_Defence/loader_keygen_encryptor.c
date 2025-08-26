// generate_key_header.c
#include <stdio.h>
#include <stdint.h>

int main() {
    uint8_t key[8] = {0x6A, 0x2F, 0x9C, 0x41, 0x88, 0x3D, 0x17, 0xB2};

    uint8_t xor1 = 0x69;
    uint8_t xor2 = 0xA1;
    uint8_t xor3 = 0x6D;

    for (int i = 0; i < 8; i++) {
        key[i] ^= xor1;
        key[i] ^= xor2;
        key[i] ^= xor3;
    }

    FILE *fp = fopen("embedded_loader_key.h", "w");
    if (!fp) return 1;

    fprintf(fp, "#ifndef EMBEDDED_KEY_H\n#define EMBEDDED_KEY_H\n\n");
    fprintf(fp, "static const unsigned char embedded_key[16] = {");
    for (int i = 0; i < 8; ++i) {
        fprintf(fp, "0x%02X", key[i]);
        if (i < 8) fprintf(fp, ", ");
    }
    fprintf(fp, "};\n\n#endif\n");

    fclose(fp);
    return 0;
}

