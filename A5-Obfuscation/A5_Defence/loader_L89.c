#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "payload_L89.h"  // encrypted_a_out_L89[], encrypted_a_out_L89_len

#define SHIFT_VAL 47
#define ROTATE_BITS 3

unsigned char rotate_right(unsigned char byte, int bits) {
    return ((byte >> bits) | (byte << (8 - bits))) & 0xFF;
}

void complex_decrypt(unsigned char *data, size_t len, const unsigned char *key, size_t keylen) {
    for (size_t i = 0; i < len; i++) {
        unsigned char b = data[i];

        switch (i % 3) {
            case 0:
                b ^= key[i % keylen];
                b = (b - SHIFT_VAL + 256) % 256;
                b = rotate_right(b, ROTATE_BITS);
                break;
            case 1:
                b = rotate_right(b, ROTATE_BITS);
                b ^= key[i % keylen];
                b = (b - SHIFT_VAL + 256) % 256;
                break;
            case 2:
                b = (b - SHIFT_VAL + 256) % 256;
                b = rotate_right(b, ROTATE_BITS);
                b ^= key[i % keylen];
                break;
        }

        data[i] = b;
    }
}

int main(int argc, char *argv[]) {
    unsigned char *decrypted = malloc(encrypted_a_out_L89_len);
    if (!decrypted) {
        perror("malloc failed");
        return 1;
    }

    memcpy(decrypted, encrypted_a_out_L89, encrypted_a_out_L89_len);

    unsigned char key[] = {0x3E, 0x77, 0xC2, 0x91, 0xD4, 0x5A, 0xB8, 0x0F};

    size_t keylen = sizeof(key);

    complex_decrypt(decrypted, encrypted_a_out_L89_len, key, keylen);

    char tmpfile[] = "/tmp/tmpbinXXXXXX";
    int fd = mkstemp(tmpfile);
    if (fd == -1) {
        perror("mkstemp failed");
        free(decrypted);
        return 1;
    }

    write(fd, decrypted, encrypted_a_out_L89_len);
    close(fd);
    chmod(tmpfile, 0755);
    free(decrypted);

    char **args = malloc((argc + 1) * sizeof(char*));
    args[0] = tmpfile;
    for (int i = 1; i < argc; i++) args[i] = argv[i];
    args[argc] = NULL;

    execv(tmpfile, args);
    perror("execv failed");
    return 1;
}

