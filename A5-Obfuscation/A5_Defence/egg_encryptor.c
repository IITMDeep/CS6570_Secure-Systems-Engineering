#include <stdio.h>
#include <stdint.h>

void crow(uint8_t *row, uint8_t key) {
    volatile int maze = key ^ 0x3C;
    maze += (row[0] ^ 0x1F) & 0xFF;
    maze = (maze << 2) | (maze >> 3);

    for (int i = 0; i < 6; ++i) {
        row[i] ^= key;

        // junk logic
        volatile uint8_t trash = (row[i] + i * 7) ^ 0xAB;
        if ((trash & 0xF0) == 0xB0) trash ^= 0x33;
    }
}

void raven(uint8_t *row, uint8_t key) {
    volatile int trap = key * 7;
    trap ^= (row[1] | 0x22);
    trap = (trap >> 1) ^ 0x19;

    for (int i = 0; i < 6; ++i) {
        row[i] ^= key;

        // junk logic
        volatile uint8_t confuse = (row[i] << 2) ^ i;
        if (confuse & 1) confuse |= 0x1F;
    }
}

void eagle(uint8_t *row, uint8_t key) {
    volatile int illusion = (key + 5) ^ 0xDE;
    illusion |= (row[2] << 1);
    illusion = ~illusion;

    for (int i = 0; i < 6; ++i) {
        row[i] ^= key;

        // junk logic
        volatile uint8_t noise = ((row[i] ^ 0x77) + i) & 0xFE;
        if ((noise ^ 0xAA) == 0x00) noise ^= 0x55;
    }
}

void pigeon(uint8_t *row, uint8_t key) {
    volatile int cipher = key | 0xA0;
    cipher += (row[3] ^ 0x12);
    cipher = (cipher & 0xFF) ^ 0x33;

    for (int i = 0; i < 6; ++i) {
        row[i] ^= key;

        // junk logic
        volatile uint8_t shadow = (row[i] + 0x10) ^ (i * 3);
        if ((shadow & 0x0F) > 5) shadow += 1;
    }
}

void ostrich(uint8_t *row, uint8_t key) {
    volatile int code = (key ^ 0x1B) + 0x55;
    code = (code << 1) ^ 0xAB;
    code &= 0xFF;

    for (int i = 0; i < 6; ++i) {
        row[i] ^= key;

        // junk logic
        volatile uint8_t crypt = (row[i] ^ 0xCC) | (i << 2);
        if ((crypt & 0xE0) == 0xC0) crypt ^= 0x20;
    }
}

int main() {
    uint8_t egg_params[5][6] = {
        {0xb5, 0xb5, 0x85, 0xa5, 0x95, 0xb5},
        {0x85, 0xb5, 0xa5, 0xa5, 0xa5, 0x85},
        {0x95, 0x85, 0x95, 0x85, 0xa5, 0xb5},
        {0xf5, 0x95, 0xb5, 0x85, 0xa5, 0xb5},
        {0x25, 0xb5, 0xa5, 0xa5, 0x85, 0xb5}
    };

    uint8_t keys[5] = {0x4A, 0x3E, 0x77, 0x1B, 0x6D};

    crow(egg_params[0], keys[0]);
    raven(egg_params[1], keys[1]);
    eagle(egg_params[2], keys[2]);
    pigeon(egg_params[3], keys[3]);
    ostrich(egg_params[4], keys[4]);

    FILE *fp = fopen("embedded_eggs.h", "w");
    if (!fp) return 1;

    fprintf(fp, "#ifndef EMBEDDED_EGGS_H\n#define EMBEDDED_EGGS_H\n\n");
    fprintf(fp, "static const uint8_t embedded_eggs[5][6] = {\n");

    for (int i = 0; i < 5; ++i) {
        fprintf(fp, "    { ");
        for (int j = 0; j < 6; ++j) {
            fprintf(fp, "0x%02X", egg_params[i][j]);
            if (j < 5) fprintf(fp, ", ");
        }
        fprintf(fp, " }");
        if (i < 4) fprintf(fp, ",");
        fprintf(fp, "\n");
    }

    fprintf(fp, "};\n\n#endif\n");

    fclose(fp);
    return 0;
}

