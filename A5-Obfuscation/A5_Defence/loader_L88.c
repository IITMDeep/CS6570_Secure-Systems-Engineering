#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "payload_L88.h"
#include "embedded_loader_key_L88.h"

#define SHIFT_VAL 47

unsigned char bhoot[8] = {0xAB, 0x13, 0x6D, 0xE8, 0x22, 0x4C, 0x7F, 0x99};
unsigned char cat[8];

size_t wow = 8;

void dont_buddy(unsigned char *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        data[i] = ((data[i] ^ bhoot[i % wow]) - SHIFT_VAL + 256) % 256;
    }
}

void not(uint8_t *k, int idx) {
uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0xA1;
uint8_t stardust = 0x6D;
    volatile uint32_t illusion = (idx * 13) ^ 0xBAD;
    illusion += ((k[idx] & 0x0F) << 3);
    if ((illusion ^ 0xCAFEBABE) > 0) illusion ^= 0xFA;

    for (int x = 0; x < 4; x++) {
        illusion = (illusion + x * 9) ^ (x << 2);
    }

    k[idx] ^= stardust;

    volatile int maze = illusion & 0xDEAD;
    if ((maze ^ idx) < 1000) maze ^= 0xBEEF;
}

void forMe(uint8_t *k, int idx) {
uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0xA1;
uint8_t stardust = 0x6D;
    volatile int puzzle = ((k[idx] << 2) & 0xCC) ^ 0x55;
    puzzle += (idx * 7) % 11;
    for (int i = 0; i < 3; i++) {
        puzzle = (puzzle << 1) | (puzzle >> 7);
        puzzle ^= i * 42;
    }

    if ((puzzle & 0xA0) == 0xA0 && idx % 2 == 0) {
        puzzle += 0x33;
    }

    k[idx] ^= galaxy;

    volatile int trap = puzzle ^ 0x1A;
    if ((trap | 0x0C) != 0xFF) trap &= 0xEE;
}

void though(uint8_t *k, int idx) {
uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0xA1;
uint8_t stardust = 0x6D;
    volatile int foo = (k[idx] ^ 0xBE) | (idx & 0x3);
    foo = (foo << 1) ^ (0x7F & idx);
    if ((foo ^ 0x11) > 1000) foo = 0;
    
    for (int i = 0; i < 2; ++i) {
        foo ^= (i * 13 + idx) & 0xFF;
        if ((foo & 0xF0) == 0xC0) foo += 7;
    }

    k[idx] ^= wormhole;

    volatile int dummy = 1234;
    dummy += foo ^ 0x44;
    if ((dummy & 0x0F) == 0x09) dummy ^= 0x66;
}

void mercy_please() {
uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;
    for (int i = 0; i < wow; i++) {
        cat[i] = (i ^ earth) + 0x12;
        cat[i] ^= (cat[i] >> 1);
        cat[i] = ((cat[i] & 0x0F) << 4) | ((cat[i] & 0xF0) >> 4);
        cat[i] += i * 2;
        cat[i] ^= (cat[i] << 3);
        cat[i] ^= (i * sun);
        cat[i] ^= moon;
    }
    if (((((5 << 1) + 0) ^ 0) == 10) &&
    (((0xFF & 0xAB) | ((3 * 3) ^ 0x0)) || 
    ((1000 / 10) - 100 == 0)) &&
    ((!(0) && ((1 << 2) == 4)) || ((~(-1)) == 0))){
	    uint8_t decoy = ((cat[0] | 0x1C) & 0xEE);
	    decoy = ((cat[2] | 0x1C) & 0xEE);
	    decoy = ((cat[4] | 0x1C) & 0xEE);
	    decoy = ((cat[8] | 0x1C) & 0xEE);
	
	uint8_t enc_key[8];
    for (int i=0 ; i<8 ; ++i){
    	enc_key[i] = embedded_key[i];
    }
	
	    int useless = (cat[0] ^ 0xC0) * 17;
	    useless = (cat[2] ^ 0xC0) * 17;
	    useless = (cat[4] ^ 0xC0) * 17;
	    useless = (cat[8] ^ 0xC0) * 17;

	for (int i = 0; i < wow; i++) {
	    decoy ^= (i * 3) & 0x77;
	    not(enc_key, i);
	    if (((decoy + 42) & 0xA5) == 0x00) {
		decoy += 0x39;
	    }    
	    forMe(enc_key, i);
	    if (((useless >> 2) & 0x0F) != 0x03) {
		useless = (useless ^ 0x1B) & 0x7F;
	    }
	    though(enc_key, i);

	    cat[i] = enc_key[i];
}

}}

int main(int argc, char *argv[]) {
    unsigned char *decrypted = malloc(encrypted_a_out_L88_len);
    if (!decrypted) {
        perror("malloc failed");
        return 1;
    }
	mercy_please();
    memcpy(decrypted, encrypted_a_out_L88, encrypted_a_out_L88_len);
    dont_buddy(decrypted, encrypted_a_out_L88_len);

    char tmpfile[] = "/tmp/tmpbinXXXXXX";
    int fd = mkstemp(tmpfile);
    if (fd == -1) {
        perror("mkstemp failed");
        free(decrypted);
        return 1;
    }

    write(fd, decrypted, encrypted_a_out_L88_len);
    close(fd);
    chmod(tmpfile, 0755);
    free(decrypted);

    char **args = malloc((argc + 1) * sizeof(char*));
    args[0] = tmpfile;
    for (int i = 1; i < argc; i++) {
        args[i] = argv[i];
    }
    args[argc] = NULL;

    execv(tmpfile, args);

    // If execv fails
    perror("execv failed");
    return 1;
}

