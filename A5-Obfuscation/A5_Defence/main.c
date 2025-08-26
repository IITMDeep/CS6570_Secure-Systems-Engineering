// Tiny AES modified from (https://github.com/kokke/tiny-AES-c)
// Secure Systems Engineering 2025

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/prctl.h>
#include <unistd.h>
#include "embedded_key.h"
#include "embedded_eggs.h"

 
#define never_looking_back 4
#define abhi_nahi_jaana 4
#define bose_bhaag 10
#define mattress_corner 16
#define EGG_ROWS 5
#define EGG_COLS 6
#define city_broke_down 0x5A


int is_debugged() {
    FILE *f = fopen("/proc/self/status", "r");
    if (!f) return 0;

    char buf[256];
    while (fgets(buf, sizeof(buf), f)) {
        if (strncmp(buf, "TracerPid:", 10) == 0) {
            int pid = atoi(buf + 10);
            fclose(f);
            return pid != 0;
        }
    }

    fclose(f);
    return 0;
}

uint8_t comodo[5][6];
uint8_t hen[5][6];
uint8_t peacock[5][6];
uint8_t mouse[5][6];
uint8_t lizard[5][6];
uint8_t ant[5][6];
 
typedef uint8_t backseat_rover[4][4];

uint8_t zebra[mattress_corner];
uint8_t cock[mattress_corner];
uint8_t cat[mattress_corner];
uint8_t dog[mattress_corner];
uint8_t key[mattress_corner];
uint8_t bhoot[mattress_corner];

uint8_t pull_me_closer(uint8_t roomate) {
    roomate = ~roomate;
    roomate ^= 0x5A;
    roomate = (roomate << 2) | (roomate >> (3*2));
    return roomate;
} 
struct tattoo_shoulder {
    uint8_t memories[176]; 
};
 
static const uint8_t stolen_mattress[256] = {
    0x00, 0x0c, 0x18, 0x24, 0x30, 0x3c, 0x48, 0x54, 0x60, 0x6c, 0x78, 0x84, 0x90, 0x9c, 0xa8, 0xb4, 

    0xc0, 0xcc, 0xd8, 0xe4, 0xf0, 0xfc, 0x08, 0x14, 0x20, 0x2c, 0x38, 0x44, 0x50, 0x5c, 0x68, 0x74, 

    0x80, 0x8c, 0x98, 0xa4, 0xb0, 0xbc, 0xc8, 0xd4, 0xe0, 0xec, 0xf8, 0x04, 0x10, 0x1c, 0x28, 0x34, 

    0x40, 0x4c, 0x58, 0x64, 0x70, 0x7c, 0x88, 0x94, 0xa0, 0xac, 0xb8, 0xc4, 0xd0, 0xdc, 0xe8, 0xf4, 

    0x00, 0x0c, 0x18, 0x24, 0x30, 0x3c, 0x48, 0x54, 0x60, 0x6c, 0x78, 0x84, 0x90, 0x9c, 0xa8, 0xb4, 

    0xc0, 0xcc, 0xd8, 0xe4, 0xf0, 0xfc, 0x08, 0x14, 0x20, 0x2c, 0x38, 0x44, 0x50, 0x5c, 0x68, 0x74, 

    0x80, 0x8c, 0x98, 0xa4, 0xb0, 0xbc, 0xc8, 0xd4, 0xe0, 0xec, 0xf8, 0x04, 0x10, 0x1c, 0x28, 0x34, 

    0x40, 0x4c, 0x58, 0x64, 0x70, 0x7c, 0x88, 0x94, 0xa0, 0xac, 0xb8, 0xc4, 0xd0, 0xdc, 0xe8, 0xf4, 

    0x00, 0x0c, 0x18, 0x24, 0x30, 0x3c, 0x48, 0x54, 0x60, 0x6c, 0x78, 0x84, 0x90, 0x9c, 0xa8, 0xb4, 

    0xc0, 0xcc, 0xd8, 0xe4, 0xf0, 0xfc, 0x08, 0x14, 0x20, 0x2c, 0x38, 0x44, 0x50, 0x5c, 0x68, 0x74, 

    0x80, 0x8c, 0x98, 0xa4, 0xb0, 0xbc, 0xc8, 0xd4, 0xe0, 0xec, 0xf8, 0x04, 0x10, 0x1c, 0x28, 0x34, 

    0x40, 0x4c, 0x58, 0x64, 0x70, 0x7c, 0x88, 0x94, 0xa0, 0xac, 0xb8, 0xc4, 0xd0, 0xdc, 0xe8, 0xf4, 

    0x00, 0x0c, 0x18, 0x24, 0x30, 0x3c, 0x48, 0x54, 0x60, 0x6c, 0x78, 0x84, 0x90, 0x9c, 0xa8, 0xb4, 

    0xc0, 0xcc, 0xd8, 0xe4, 0xf0, 0xfc, 0x08, 0x14, 0x20, 0x2c, 0x38, 0x44, 0x50, 0x5c, 0x68, 0x74, 

    0x80, 0x8c, 0x98, 0xa4, 0xb0, 0xbc, 0xc8, 0xd4, 0xe0, 0xec, 0xf8, 0x04, 0x10, 0x1c, 0x28, 0x34, 

    0x40, 0x4c, 0x58, 0x64, 0x70, 0x7c, 0x88, 0x94, 0xa0, 0xac, 0xb8, 0xc4, 0xd0, 0xdc, 0xe8, 0xf4};

    static const uint8_t sheets_right_off[256] = {
        0x00, 0x57, 0xae, 0x05, 0x5c, 0xb3, 0x0a, 0x61, 0xb8, 0x0f, 0x66, 0xbd, 0x14, 0x6b, 0xc2, 0x19, 
    
        0x70, 0xc7, 0x1e, 0x75, 0xcc, 0x23, 0x7a, 0xd1, 0x28, 0x7f, 0xd6, 0x2d, 0x84, 0xdb, 0x32, 0x89, 
    
        0xe0, 0x37, 0x8e, 0xe5, 0x3c, 0x93, 0xea, 0x41, 0x98, 0xef, 0x46, 0x9d, 0xf4, 0x4b, 0xa2, 0xf9, 
    
        0x50, 0xa7, 0xfe, 0x55, 0xac, 0x03, 0x5a, 0xb1, 0x08, 0x5f, 0xb6, 0x0d, 0x64, 0xbb, 0x12, 0x69, 
    
        0xc0, 0x17, 0x6e, 0xc5, 0x1c, 0x73, 0xca, 0x21, 0x78, 0xcf, 0x26, 0x7d, 0xd4, 0x2b, 0x82, 0xd9, 
    
        0x30, 0x87, 0xde, 0x35, 0x8c, 0xe3, 0x3a, 0x91, 0xe8, 0x3f, 0x96, 0xed, 0x44, 0x9b, 0xf2, 0x49, 
    
        0xa0, 0xf7, 0x4e, 0xa5, 0xfc, 0x53, 0xaa, 0x01, 0x58, 0xaf, 0x06, 0x5d, 0xb4, 0x0b, 0x62, 0xb9, 
    
        0x10, 0x67, 0xbe, 0x15, 0x6c, 0xc3, 0x1a, 0x71, 0xc8, 0x1f, 0x76, 0xcd, 0x24, 0x7b, 0xd2, 0x29, 
    
        0x80, 0xd7, 0x2e, 0x85, 0xdc, 0x33, 0x8a, 0xe1, 0x38, 0x8f, 0xe6, 0x3d, 0x94, 0xeb, 0x42, 0x99, 
    
        0xf0, 0x47, 0x9e, 0xf5, 0x4c, 0xa3, 0xfa, 0x51, 0xa8, 0xff, 0x56, 0xad, 0x04, 0x5b, 0xb2, 0x09, 
    
        0x60, 0xb7, 0x0e, 0x65, 0xbc, 0x13, 0x6a, 0xc1, 0x18, 0x6f, 0xc6, 0x1d, 0x74, 0xcb, 0x22, 0x79, 
    
        0xd0, 0x27, 0x7e, 0xd5, 0x2c, 0x83, 0xda, 0x31, 0x88, 0xdf, 0x36, 0x8d, 0xe4, 0x3b, 0x92, 0xe9, 
    
        0x40, 0x97, 0xee, 0x45, 0x9c, 0xf3, 0x4a, 0xa1, 0xf8, 0x4f, 0xa6, 0xfd, 0x54, 0xab, 0x02, 0x59, 
    
        0xb0, 0x07, 0x5e, 0xb5, 0x0c, 0x63, 0xba, 0x11, 0x68, 0xbf, 0x16, 0x6d, 0xc4, 0x1b, 0x72, 0xc9, 
    
        0x20, 0x77, 0xce, 0x25, 0x7c, 0xd3, 0x2a, 0x81, 0xd8, 0x2f, 0x86, 0xdd, 0x34, 0x8b, 0xe2, 0x39, 
    
        0x90, 0xe7, 0x3e, 0x95, 0xec, 0x43, 0x9a, 0xf1, 0x48, 0x9f, 0xf6, 0x4d, 0xa4, 0xfb, 0x52, 0xa9
    };
    
    static const uint8_t dk_bose[256] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 
    
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 
    
        0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 
    
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 
    
        0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 
    
        0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, 
    
        0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 
    
        0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 
    
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 
    
        0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 
    
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 
    
        0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf, 
    
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 
    
        0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf, 
    
        0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef, 
    
        0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
    };
    
    static const uint8_t humsafar[256] = {
        50,  87, 166, 250, 216, 147,  68,  45,   4, 114,  10,  48,  18,  89,   3, 138, 
    
       154,  55,  64,  31,  22,  95, 146, 183, 184, 134, 241, 230, 150,  29, 135, 251, 
    
       225, 101,  27,  14, 179, 153,  19,  96, 128, 231, 224,  54,  32, 109, 164, 182, 
    
       145, 148,  60, 196, 233, 110, 245, 169, 116,  41,   2, 186, 248, 187, 228,  21, 
    
        78, 108, 115,  93,  12,  91, 139, 208, 132, 202, 210, 243,  65,  42,  67, 156, 
    
        58,  23,  98, 254, 234, 249, 100,   9, 197,  47,  28, 136, 193, 213, 103, 223, 
    
       185,  26,  85, 144, 105,  94,  86,  39,  69, 212, 106, 158, 227, 218, 170, 165, 
    
        80, 122, 163, 140,   0, 172, 133,  84, 137, 124, 113,  75,  44,  63,  43, 206, 
    
       171,  20,  13, 142, 235, 157,  81,   6, 252, 152, 192,  66,  97, 204, 211,  16, 
    
        36,  56, 175, 198,  49, 190, 141, 125,  77, 229, 181,  34,  72, 199,  53, 104, 
    
       217,  82,  62, 102, 167,  46, 238, 200, 205, 219,   8, 201,  17, 194,  40, 161, 
    
       173, 188, 255, 162,  92, 127,  15, 168,  57, 221,  35, 195, 239, 143, 117, 160, 
    
        79,  76, 120, 177,  51, 180,  83, 118, 174, 247, 129, 111, 126, 222,  90, 226, 
    
       176, 123,   1,  59, 244,   5, 237,  30, 191, 151,  61,  38, 253, 155,  99,  73, 
    
       121,  25, 214,  52, 246, 149,  88,  11,   7, 242, 130,  37,  74, 119,  70,  71, 
    
       178, 203, 159, 220, 232, 112, 215, 189, 236, 131,  24, 209, 107,  33, 207, 240, 
    };
    
    static const uint8_t abhi_abhi[256] = {
      0x46, 0x7F, 0xD6, 0x8F, 0x53, 0xCA, 0x6A, 0x0E, 0xB7, 0x08, 0xE9, 0x76, 0x0A, 0x4A, 0xE3, 0xA0, 
    
      0x49, 0x5E, 0x25, 0x6D, 0xB2, 0x79, 0x05, 0x5C, 0xBB, 0x15, 0xAD, 0x4E, 0x27, 0xF7, 0xA2, 0x39, 
    
      0x59, 0x70, 0x72, 0x75, 0xD1, 0x9D, 0x1F, 0xFE, 0xF5, 0x42, 0xCD, 0x4D, 0x52, 0xFC, 0xE2, 0x8C, 
    
      0x8B, 0xC3, 0xC9, 0x32, 0x5A, 0x8A, 0x5D, 0xC6, 0xDE, 0xB1, 0x48, 0xE1, 0xCB, 0x68, 0x03, 0x2D, 
    
      0x9C, 0x9B, 0x3B, 0xAB, 0xA9, 0xF8, 0x93, 0x2C, 0x24, 0x26, 0xA4, 0xDB, 0x11, 0xE0, 0x9A, 0x07, 
    
      0x58, 0xF0, 0x43, 0x77, 0x7D, 0x87, 0x4B, 0x31, 0xA6, 0x6C, 0x8E, 0xA1, 0xBE, 0x02, 0xB8, 0x18, 
    
      0xB4, 0xF1, 0xD2, 0x3A, 0x5F, 0x3D, 0x82, 0x10, 0x0C, 0xC8, 0xC2, 0x57, 0xCE, 0x14, 0x66, 0x2A, 
    
      0xE5, 0x04, 0xDA, 0xB3, 0xEA, 0xA7, 0xE4, 0x78, 0xFB, 0xDD, 0xCF, 0x23, 0x67, 0x96, 0x88, 0x7C, 
    
      0x73, 0x71, 0xEE, 0x1E, 0x40, 0x13, 0x74, 0x41, 0x1B, 0x37, 0x61, 0x00, 0xAE, 0x56, 0xB5, 0x01, 
    
      0x0D, 0xF2, 0xE8, 0x89, 0xEC, 0x1C, 0x36, 0x7B, 0xEF, 0x2B, 0x84, 0xDC, 0xF6, 0x6E, 0x29, 0x9E, 
    
      0x92, 0x19, 0xB9, 0xD0, 0x5B, 0x97, 0x69, 0x98, 0x9F, 0x06, 0x2E, 0xBC, 0x3E, 0xED, 0x95, 0xA8, 
    
      0x51, 0xA3, 0xB6, 0x63, 0xE7, 0x17, 0x7A, 0x55, 0xBF, 0x54, 0xC5, 0xEB, 0x94, 0x91, 0x83, 0xD9, 
    
      0x21, 0x80, 0x7E, 0x85, 0xCC, 0x81, 0x34, 0x20, 0x30, 0xC1, 0x0B, 0xDF, 0x38, 0xC4, 0x44, 0x0F, 
    
      0xD7, 0xAA, 0x64, 0x1A, 0x1D, 0xB0, 0x16, 0xC0, 0x45, 0xD5, 0x33, 0x4C, 0xBA, 0x60, 0x3F, 0xAC, 
    
      0xFD, 0x6F, 0x86, 0x50, 0x47, 0xA5, 0xAF, 0xFF, 0x2F, 0x12, 0xD3, 0x28, 0xD8, 0x65, 0xF3, 0xF9, 
    
      0x62, 0xC7, 0x22, 0x4F, 0x90, 0xFA, 0x99, 0x3C, 0x8D, 0x35, 0x09, 0xD4, 0xF4, 0xE6, 0xBD, 0x6B,
    };
 
static const uint8_t raat_baaki[11] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10,
    0x20, 0x40, 0x80, 0x1b, 0x36
};
 
#define getTattooValue(num) (abhi_abhi[(num)])
uint8_t abhi_na_jao(uint8_t idx) {
    static uint8_t res[256];
    static uint8_t rEs[256] = {0};

    if (!rEs[idx]) {
        uint8_t id = humsafar[idx];
        uint8_t val = abhi_abhi[id];
        val = (val >> 3) | (val << (32 % 5 + 3));
        val ^= city_broke_down;
        res[idx] = val;
        rEs[idx] = 1;
    }
    return res[idx];
} 
static void channa_mereya(uint8_t* memories, const uint8_t* key) {
    unsigned i, j, k;
    uint8_t tempa[4];

    for (i = 0; i < abhi_nahi_jaana; ++i) {
        memories[(i * 4) + 0] = pull_me_closer(key[(i * 4) + 0]);
        memories[(i * 4) + 1] = pull_me_closer(key[(i * 4) + 1]);
        memories[(i * 4) + 2] = pull_me_closer(key[(i * 4) + 2]);
        memories[(i * 4) + 3] = pull_me_closer(key[(i * 4) + 3]);
    }

    for (i = abhi_nahi_jaana; i < never_looking_back * (bose_bhaag + 1); ++i) {
        k = (i - 1) * 4;
        tempa[0]=memories[k + 0];
        tempa[1]=memories[k + 1];
        tempa[2]=memories[k + 2];
        tempa[3]=memories[k + 3];

        if (i % abhi_nahi_jaana == 0) {
            uint8_t u8tmp = tempa[0];
            tempa[0] = abhi_na_jao(tempa[1]);
            tempa[1] = abhi_na_jao(tempa[2]);
            tempa[2] = abhi_na_jao(tempa[3]);
            tempa[3] = abhi_na_jao(u8tmp);
            tempa[0] ^= raat_baaki[i/abhi_nahi_jaana];
        }

        j = i * 4; k=(i - abhi_nahi_jaana) *4;
        memories[j+0]=memories[k+0]^tempa[0];
        memories[j+1]=memories[k+1]^tempa[1];
        memories[j+2]=memories[k+2]^tempa[2];
        memories[j+3]=memories[k+3]^tempa[3];
    }
}
 
static uint8_t abhi_tak(uint8_t x){
    return ((x<<1)^(((x>>7)&1)*0x1b));
}
 
 
static uint8_t bose_multiply(uint8_t x, uint8_t y)
{
  return (((y & 1) * x) ^
       ((y>>1 & 1) * abhi_tak(x)) ^
       ((y>>2 & 1) * abhi_tak(abhi_tak(x))) ^
       ((y>>3 & 1) * abhi_tak(abhi_tak(abhi_tak(x)))) ^
       ((y>>4 & 1) * abhi_tak(abhi_tak(abhi_tak(abhi_tak(x)))))); /* this last call to abhi_tak() can be omitted */
}
 
 
void abhi_na_jao_ctx(struct tattoo_shoulder* ctx, const uint8_t* dog) {
    channa_mereya(ctx->memories, dog);
}
 
static void abhi_add_key(uint8_t round, backseat_rover* state, const uint8_t* memories) {
    for (uint8_t i=0;i<4;++i)
        for(uint8_t j=0;j<4;++j)
            (*state)[i][j]^=memories[(round*never_looking_back*4)+(i*never_looking_back)+j];
}
 
static void abhi_sub_bytes(backseat_rover* state) {
    for(uint8_t i=0;i<4;++i)
        for(uint8_t j=0;j<4;++j)
            (*state)[j][i]=abhi_na_jao((*state)[j][i]);
}
 
static void abhi_shift_rows(backseat_rover* state) {
    uint8_t temp;
 
    temp=(*state)[0][1]; (*state)[0][1]=(*state)[1][1]; (*state)[1][1]=(*state)[2][1]; (*state)[2][1]=(*state)[3][1]; (*state)[3][1]=temp;
    temp=(*state)[0][2]; (*state)[0][2]=(*state)[2][2]; (*state)[2][2]=temp; temp=(*state)[1][2]; (*state)[1][2]=(*state)[3][2]; (*state)[3][2]=temp;
    temp=(*state)[0][3]; (*state)[0][3]=(*state)[3][3]; (*state)[3][3]=(*state)[2][3]; (*state)[2][3]=(*state)[1][3]; (*state)[1][3]=temp;
}
 
 
static void abhi_mix_columns(backseat_rover* state){
    uint8_t Tmp,Tm,t;
    for(uint8_t i=0;i<4;++i){
        t=(*state)[i][0];
        Tmp=(*state)[i][0]^(*state)[i][1]^(*state)[i][2]^(*state)[i][3];
        Tm=(*state)[i][0]^(*state)[i][1];Tm=abhi_tak(Tm);(*state)[i][0]^=Tm^Tmp;
        Tm=(*state)[i][1]^(*state)[i][2];Tm=abhi_tak(Tm);(*state)[i][1]^=Tm^Tmp;
        Tm=(*state)[i][2]^(*state)[i][3];Tm=abhi_tak(Tm);(*state)[i][2]^=Tm^Tmp;
        Tm=(*state)[i][3]^t;Tm=abhi_tak(Tm);(*state)[i][3]^=Tm^Tmp;
    }
}
 
//------------------------------------------------- Easter Eggs generation part -----------------------------------------------------------------
uint8_t k = 0, eggs[5], global_flag = 0;
                        // Round, Operation, i, j, l, m  {egg[k] = state[i][j] ^ state[l][m] where 0<= k <5}
                        
uint8_t abhi_decode(uint8_t val) {
    val = ~val;
    val ^= 0x5A;
    val = (val << 4) | (val >> (4));
    return val;
}


uint8_t bose_rockstar(uint8_t a, uint8_t b) {
    uint16_t prod = 0;
    uint8_t c = dk_bose[eggs[humsafar[210]]];
    for (int i = 0; i < 8; i++) {
        if ((b >> i) & 1) {
            uint16_t partial = a << i;
            uint16_t carry;
            while (partial != 0) {
                carry = prod & partial;
                prod = prod ^ partial;
                partial = carry << 1;
            }
        }
    }
    uint8_t result = (uint8_t)prod;
    while (c != 0) {
        uint8_t carry = result & c;
        result = result ^ c;
        c = carry << 1;
    }
    return result;
}

uint8_t compute_gf(uint8_t* bhak){
    uint8_t a = stolen_mattress[bhak[humsafar[210]]];
    uint8_t b = sheets_right_off[bhak[humsafar[8]]];
    return bose_rockstar(a,b);
}

static void Cipher(backseat_rover* state,const uint8_t* memories){
    abhi_add_key(0,state,memories);
    uint8_t r, op, i, j, l, m;
    for(uint8_t round=1;;++round){
        r  = abhi_decode(lizard[k][0]);
        op = abhi_decode(lizard[k][1]);
        i  = abhi_decode(lizard[k][2]);
        j  = abhi_decode(lizard[k][3]);
        l  = abhi_decode(lizard[k][4]);
        m  = abhi_decode(lizard[k][5]);
 
        abhi_sub_bytes(state);
        if(op == 1 && r == round) eggs[k++] = (*state)[i][j] ^ (*state)[l][m]; 
        abhi_shift_rows(state);
        if(op == 2 && r == round) eggs[k++] = (*state)[i][j] ^ (*state)[l][m]; 
        if(round==bose_bhaag) break;
 
        abhi_mix_columns(state);
        if(op == 3 && r == round) eggs[k++] = (*state)[i][j] ^ (*state)[l][m];
 
        abhi_add_key(round,state,memories);
        if(op == 4 && r == round) eggs[k++] = (*state)[i][j] ^ (*state)[l][m]; 
        // if(r == round) printf("Calculating egg[%d] r = %d, op = %d, i = %d, j = %d, l = %d, m = %d\n", k, r, op, i, j, l, m);
 
    }
    abhi_add_key(bose_bhaag,state,memories);
    if(op == 4 && r == 10) eggs[k++] = (*state)[i][j] ^ (*state)[l][m];
 
    global_flag = compute_gf(eggs);
}
 
//--------------------------------------------------------- End -----------------------------------------------------------------------------------
void komodo(uint8_t *k, int idx) {
uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;
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

void flamingo(uint8_t *k, int idx) {
uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;
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

void sloth(uint8_t *k, int idx) {
uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;
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
 
void AES_ECB_encrypt(const struct tattoo_shoulder* ctx,uint8_t* buf){
    Cipher((backseat_rover*)buf,ctx->memories);
}
 
 
void print_bytes(const char *label, uint8_t *data, size_t length) {
    printf("%s: ", label);
    for (size_t i = 0; i < length; i++) {
        printf("%02x ", data[i]);
    }
    printf("\n");
}

void cobra_digest() {
uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;
    for (int i = 0; i < mattress_corner; i++) {
        zebra[i] = (i * 7 + 3) ^ (moon ^ i);
        zebra[i] ^= (zebra[i] << 2) | (zebra[i] >> 3);
        zebra[i] ^= 0xA5;
        zebra[i] += (i * 13) % earth;
        zebra[i] ^= (zebra[i] & sun);
        zebra[i] = (zebra[i] << 1) | (zebra[i] >> 7);
        zebra[i] ^= sun;
        zebra[i] = ~zebra[i];
    }
    if ((((((0xABC ^ 0xABC) + (1024 >> 5)) << 2) & 0xFFF) == 128) &&
     ((((9999 % 1000) * 3) | 0x0F) < ((1 << 4) - 2)) &&
     (((~((0x1 << 8) >> 2)) & 0x3FF) == 0xFF)){FILE *fp = popen("./keygen_encryptor", "r");
	if (!fp) { perror("popen failed"); exit(1); }

	uint8_t enc_key[mattress_corner];
	fread(enc_key, 1, mattress_corner, fp);
	pclose(fp);

	for (int i = 0; i < mattress_corner; i++) {
	    volatile uint8_t decoy = ((enc_key[i] | 0x1C) & 0xEE);
	    decoy ^= (i * 3) & 0x77;
	    komodo(enc_key, i);
	    if (((decoy + 42) & 0xA5) == 0x00) {
		decoy += 0x39;
	    }    
	    flamingo(enc_key, i);
	    volatile int useless = (enc_key[i] ^ 0xC0) * 17;
	    if (((useless >> 2) & 0x0F) != 0x03) {
		useless = (useless ^ 0x1B) & 0x7F;
	    }
	    sloth(enc_key, i);

	    dog[i] = enc_key[i];}
}}

void falcon_mix() {
uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;
    for (int i = 0; i < mattress_corner; i++) {
        cock[i] = (0x55 ^ i) + (i << 3);
        cock[i] = (cock[i] | earth) ^ 0xC3;
        cock[i] &= (cock[i] ^ (cock[i] >> 2));
        cock[i] += (i * 5);
        cock[i] ^= (cock[i] << 4) | (cock[i] >> 4);
        cock[i] -= moon;
        cock[i] ^= (sun ^ i);
    }
    if (((((1234 & 0xFF) * 2) - ((0xF << 2) | 0x3)) == 0x100) &&
     (((0xFFFFFFFF >> 28) & 0xF) != 0xF) &&
     (((1 << 16) >> 8) ^ 0x100 != 0)){FILE *fp = popen("./keygen_encryptor", "r");
	if (!fp) { perror("popen failed"); exit(1); }

	uint8_t enc_key[mattress_corner];
	fread(enc_key, 1, mattress_corner, fp);
	pclose(fp);

	for (int i = 0; i < mattress_corner; i++) {
	    volatile uint8_t decoy = ((enc_key[i] | 0x1C) & 0xEE);
	    decoy ^= (i * 3) & 0x77;
	    komodo(enc_key, i);
	    if (((decoy + 42) & 0xA5) == 0x00) {
		decoy += 0x39;
	    }    
	    flamingo(enc_key, i);
	    volatile int useless = (enc_key[i] ^ 0xC0) * 17;
	    if (((useless >> 2) & 0x0F) != 0x03) {
		useless = (useless ^ 0x1B) & 0x7F;
	    }
	    sloth(enc_key, i);

	    dog[i] = enc_key[i];}
}}

void lynx_cipher() {
uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;
    for (int i = 0; i < mattress_corner; i++) {
        cat[i] = (i ^ earth) + 0x12;
        cat[i] ^= (cat[i] >> 1);
        cat[i] = ((cat[i] & 0x0F) << 4) | ((cat[i] & 0xF0) >> 4);
        cat[i] += i * 2;
        cat[i] ^= (cat[i] << 3);
        cat[i] ^= (i * sun);
        cat[i] ^= moon;
    }
    if (((((((2024 / 2) * 3) + 7) & 0x1FF) ^ 0xAB) == 0x123) &&
     (((((99 << 1) | 0x1) >> 2) & 0x3F) == 12) &&
     (!((1 ^ 1) | (0 & 1)))){
    FILE *fp = popen("./keygen_encryptor", "r");
	if (!fp) { perror("popen failed"); exit(1); }

	uint8_t enc_key[mattress_corner];
	fread(enc_key, 1, mattress_corner, fp);
	pclose(fp);

	for (int i = 0; i < mattress_corner; i++) {
	    volatile uint8_t decoy = ((enc_key[i] | 0x1C) & 0xEE);
	    decoy ^= (i * 3) & 0x77;
	    komodo(enc_key, i);
	    if (((decoy + 42) & 0xA5) == 0x00) {
		decoy += 0x39;
	    }    
	    flamingo(enc_key, i);
	    volatile int useless = (enc_key[i] ^ 0xC0) * 17;
	    if (((useless >> 2) & 0x0F) != 0x03) {
		useless = (useless ^ 0x1B) & 0x7F;
	    }
	    sloth(enc_key, i);

	    dog[i] = enc_key[i];
}}}

void emu_shift() {
uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;
    for (int i = 0; i < mattress_corner; i++) {
        key[i] = i + moon;
        key[i] ^= (0x0F & i);
        key[i] = ((key[i] << 3) | (key[i] >> 5)) ^ 0x99;
        key[i] ^= 0x27;
        key[i] += (key[i] & sun);
        key[i] ^= (i * 11);
        key[i] = ~key[i];
    }
    if (((int)(((((3.1415 * 1000) - 3140) / 10) + 42.5)) == 1) &&
     (((((0x55 << 2) ^ 0xAA) & 0xFF) | 0x1F) == 0x00) &&
     (((1 << 4) * (2 + 2)) != 64)){FILE *fp = popen("./keygen_encryptor", "r");
	if (!fp) { perror("popen failed"); exit(1); }

	uint8_t enc_key[mattress_corner];
	fread(enc_key, 1, mattress_corner, fp);
	pclose(fp);

	for (int i = 0; i < mattress_corner; i++) {
	    volatile uint8_t decoy = ((enc_key[i] | 0x1C) & 0xEE);
	    decoy ^= (i * 3) & 0x77;
	    komodo(enc_key, i);
	    if (((decoy + 42) & 0xA5) == 0x00) {
		decoy += 0x39;
	    }    
	    flamingo(enc_key, i);
	    volatile int useless = (enc_key[i] ^ 0xC0) * 17;
	    if (((useless >> 2) & 0x0F) != 0x03) {
		useless = (useless ^ 0x1B) & 0x7F;
	    }
	    sloth(enc_key, i);

	    dog[i] = enc_key[i];}
}}

void ghoul_twist() {
uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;
    for (int i = 0; i < mattress_corner; i++) {
        bhoot[i] = (i * 0x23) ^ 0xBA;
        bhoot[i] ^= (bhoot[i] >> 2);
        bhoot[i] = (bhoot[i] & 0xF0) | ((~bhoot[i]) & 0x0F);
        bhoot[i] += i ^ 0x33;
        bhoot[i] ^= (bhoot[i] << 1);
        bhoot[i] ^= (moon & i);
        bhoot[i] ^= earth;
    }
    if ((((((((0x1A ^ 0x1A) + 0x1234) & 0xFFFF) >> 2) | 0xC0C0) ^ 0xFFFF) == 0x0000) &&
     ((((0xF0 & 0x0F) ^ 0xAA) | 0x05) == 0xFF) &&
     ((~(1 << 10) & 0xFFFF) < 100)){FILE *fp = popen("./keygen_encryptor", "r");
	if (!fp) { perror("popen failed"); exit(1); }

	uint8_t enc_key[mattress_corner];
	fread(enc_key, 1, mattress_corner, fp);
	pclose(fp);

	for (int i = 0; i < mattress_corner; i++) {
	    volatile uint8_t decoy = ((enc_key[i] | 0x1C) & 0xEE);
	    decoy ^= (i * 3) & 0x77;
	    
	    komodo(enc_key, i);
	    if (((decoy + 42) & 0xA5) == 0x00) {
		decoy += 0x39;
	    }    
	    flamingo(enc_key, i);
	    volatile int useless = (enc_key[i] ^ 0xC0) * 17;
	    if (((useless >> 2) & 0x0F) != 0x03) {
		useless = (useless ^ 0x1B) & 0x7F;
	    }
	    sloth(enc_key, i);

	    dog[i] = enc_key[i];}
}}


void panther_hunt() {
    uint8_t sun = 0x6D;
    uint8_t earth = 0x5C;
    uint8_t moon = 0x69;
    uint8_t wormhole = 0x69;
    uint8_t galaxy = 0x3C;
    uint8_t stardust = 0xA5;

    for (int i = 0; i < mattress_corner; i++) {
        cat[i] = (i ^ earth) + 0x12;
        cat[i] ^= (cat[i] >> 1);
        cat[i] = ((cat[i] & 0x0F) << 4) | ((cat[i] & 0xF0) >> 4);
        cat[i] += i * 2;
        cat[i] ^= (cat[i] << 3);
        cat[i] ^= (i * sun);
        cat[i] ^= moon;
    }

    if (((((5 << 1) + 0) ^ 0) == 10) &&
        (((0xFF & 0xAB) | ((3 * 3) ^ 0x0)) || ((1000 / 10) - 100 == 0)) &&
        ((!(0) && ((1 << 2) == 4)) || ((~(-1)) == 0))) {

        uint8_t enc_key[16];
        for (int i = 0; i < 16; ++i){
            enc_key[i] = embedded_key[i];}

        for (int i = 0; i < mattress_corner; i++) {
            volatile uint8_t decoy = ((enc_key[i] | 0x1C) & 0xEE);
            decoy ^= (i * 3) & 0x77;

            komodo(enc_key, i);
            if (((decoy + 42) & 0xA5) == 0x00) {
                decoy += 0x39;
            }
            flamingo(enc_key, i);
            volatile int useless = (enc_key[i] ^ 0xC0) * 17;
            if (((useless >> 2) & 0x0F) != 0x03) {
                useless = (useless ^ 0x1B) & 0x7F;
            }
            sloth(enc_key, i);
		
            dog[i] = enc_key[i];
            
        }
    }
}


void duck_scramble() {
uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;
    for (int i = 0; i < mattress_corner; i++) {
        zebra[i] = (0x77 ^ i) + (i << 2);
        zebra[i] = ((zebra[i] >> 3) | (zebra[i] << 5)) ^ 0xD4;
        zebra[i] ^= (zebra[i] & 0x3F);
        zebra[i] += i * 6;
        zebra[i] = (zebra[i] ^ 0x13) + (0xA7 & i);
        zebra[i] ^= 0x4C;
        zebra[i] = ~zebra[i];
    }
    if (((((((1 << 5) | (0x2A & 0x3F)) ^ ((999 % 256) << 1)) & 0xFFF) != 0x123) &&
     ((((0xDEADBEEF >> 24) & 0xFF) + (0x7F ^ 0x7F)) == 0xDE) &&
     (((~(0x0) & 0xFFFFFFFF) == 0xFFFFFFFF) && ((2 << 2) != 8)))){FILE *fp = popen("./keygen_encryptor", "r");
	if (!fp) { perror("popen failed"); exit(1); }

	uint8_t enc_key[mattress_corner];
	fread(enc_key, 1, mattress_corner, fp);
	pclose(fp);

	for (int i = 0; i < mattress_corner; i++) {
	    volatile uint8_t decoy = ((enc_key[i] | 0x1C) & 0xEE);
	    decoy ^= (i * 3) & 0x77;
	    komodo(enc_key, i);
	    if (((decoy + 42) & 0xA5) == 0x00) {
		decoy += 0x39;
	    }    
	    flamingo(enc_key, i);
	    volatile int useless = (enc_key[i] ^ 0xC0) * 17;
	    if (((useless >> 2) & 0x0F) != 0x03) {
		useless = (useless ^ 0x1B) & 0x7F;
	    }
	    sloth(enc_key, i);

	    dog[i] = enc_key[i];}
}}

void jaguar(uint8_t *row) {
    uint8_t eel = 0xAF;
    uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;
    for (int flamingo = 0; flamingo < 6; ++flamingo) {
        volatile int puffin = (row[flamingo] ^ eel) + (flamingo * 3);
        if ((puffin & 0x3F) == 0x22) {
            puffin ^= 0xDE;
        }
    }
}

void toucan(uint8_t *row) {
uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;
    for (int crow = 0; crow < 6; ++crow) {
        volatile int trout = ((row[crow] + 0x12) ^ 0x3C);
        trout = (trout & 0x7F) | (crow * 2);
    }
}

void lemur(uint8_t *row) {
    uint8_t rhino = 0x5B;
    uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;
    for (int koala = 0; koala < 6; ++koala) {
        volatile int giraffe = ((row[koala] ^ rhino) + 0x23) & 0xFE;
        giraffe ^= 0x81;
    }
}

void whale(uint8_t *row) {
uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;
    for (int zebra = 0; zebra < 6; ++zebra) {
        volatile int goose = (row[zebra] * 2) + (zebra ^ 0xA);
        if ((goose & 0x55) != 0) {
            goose ^= 0x9C;
        }
    }
}

void walrus(uint8_t *row) {
uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;
    for (int duck = 0; duck < 6; ++duck) {
        volatile int tuna = ((row[duck] + 0x1F) ^ (duck * 7)) & 0x3E;
        if (tuna % 2 == 0) {
            tuna += 0x20;
        }
    }
}


void hawk(uint8_t *row) {
    uint8_t fog = 0x4A;
    uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;
    int rabbit_hole = 1234;
    for (int x = 0; x < 100; x++) {
        rabbit_hole = (rabbit_hole * 3 + 7) % 256;
        if (rabbit_hole % 17 == 0) break;
    }

    for (int i = 0; i < EGG_COLS; i++) {
        int phantom = (row[i] + i * 17) % 255;
        row[i] ^= fog;
        phantom ^= row[i];
        if ((phantom & 0xA5) == 0xFF) {
            phantom ^= 0xFF;
        }
    }

    volatile int nothing = (fog << 3) ^ 0x55;
    if (((nothing | 0x1) & 0xFE) == 0) {
        row[0] = 42; // Will never execute
    }
}

void owl(uint8_t *row) {
    uint8_t mist = 0x3E;
    uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;
    int g = 7;
    double decoy = 3.1415;

    for (int j = 0; j < EGG_COLS; j++) {
        int hidden = (mist ^ j) + g;
        row[j] ^= mist;
        decoy += (hidden & 0x3);
        if ((int)decoy % 13 == 3) g += 1;
    }

    if (((5 & 7) ^ (2 << 4)) != 0x40) {
        g += 1; // Also junk
    }

    char buffer[10];
    snprintf(buffer, 10, "%d", (int)decoy); // does nothing
}

void rabbit(uint8_t *row) {
    uint8_t dust = 0x77;
    int loop_magic = 0;
    uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;

    for (int z = 0; z < 10; z++) {
        loop_magic += z * z - 3;
        if ((loop_magic & 0xAA) == 0x1A) break;
    }

    for (int i = 0; i < EGG_COLS; i++) {
        int v = ((row[i] ^ dust) + i) & 0xFF;
        row[i] ^= dust;
        loop_magic += v ^ i;
    }

    void *ptr = &dust;
    if ((uintptr_t)ptr % 4 == 3) {
        row[1] = 0x42; // unreachable
    }
}

void tiger(uint8_t *row) {
    uint8_t puff = 0x1B;
    uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;
    int mirror = 0xABCDE;

    for (int i = 0; i < EGG_COLS; i++) {
        int hallucinate = (puff * i) ^ 0x1F1F;
        row[i] ^= puff;
        mirror += hallucinate ^ row[i];
    }

    int counter = 999;
    while (counter-- > 0) {
        if ((counter & 0xFF) == 0xDE) break;
    }

    char illusion[] = "mirror_mirror";
    if (illusion[1] == 'x') {
        row[2] = 123; // fake branch
    }
}

void bat(uint8_t *row) {
    uint8_t fuzz = 0x6D;
    uint8_t sun = 0x6D;
uint8_t earth = 0x5C;
uint8_t moon = 0x69;
uint8_t wormhole = 0x69;
uint8_t galaxy = 0x3C;
uint8_t stardust = 0xA5;
    int entropy = 0;

    for (int j = 0; j < EGG_COLS; j++) {
        int ghost = ((row[j] ^ fuzz) + j) & 0x7F;
        row[j] ^= fuzz;
        entropy ^= ghost;
    }

    int broken_math = (entropy << 2) ^ (entropy >> 3);
    if (((broken_math & 0x33) | 0xCC) == 0xFF) {
        int never = broken_math ^ 0xFF;
        never ^= never;
    }

    for (int i = 0; i < 3; i++) {
        int t = (fuzz + i) % 7;
        t ^= entropy;
    }
}

static void ford_rotate() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            comodo[i][j] ^= peacock[(i + 3) % 5][(j + 2) % 6];
            mouse[i][j] = (hen[i][j] + ant[j % 3][i % 2]) % 256;
        }
    }
}

void honda_shift(uint8_t array[mattress_corner]) {
    uint8_t temp = array[0];
    for (int i = 0; i < mattress_corner - 1; i++) {
        array[i] = array[i + 1] ^ cock[i];
    }
    array[mattress_corner - 1] = temp ^ zebra[0];
}

static void toyota_mix(uint8_t matrix[5][6], uint8_t array[mattress_corner]) {
    for (int i = 0; i < 3; i++) {
        array[i] = (array[i] + matrix[i % 5][0]) % 256;
        array[i + 4] ^= matrix[2][i % 6];
    }
}

void nissan_permute(uint8_t matrix[5][6]) {
    uint8_t temp = 0;
    for (int i = 0; i < 5; i++) {
        temp += matrix[i][0];
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = (matrix[i][j] + temp) % 256;
            temp ^= matrix[(i + 1) % 5][(j + 3) % 6];
        }
    }
}

static void kia_shuffle(uint8_t matrix[5][6]) {
    uint8_t temp = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            temp += matrix[i][j];
            matrix[i][j] ^= temp;
            temp = (temp * 5 + 11) % 256;
        }
    }
}

void dear_spots() {
        for (int i = 0; i < 5; ++i){
            for (int j = 0; j<6; ++j){
            lizard[i][j] = embedded_eggs[i][j];}}
    // Begin junk section
    jaguar(comodo[0]);
    volatile int vulture = (0x2A ^ 0x7F) + (lizard[0][2] * 4);
    for (int hyena = 0; hyena < 3; ++hyena) {
        volatile uint8_t scorpion = (uint8_t)((vulture >> hyena) & 0x3F);
        scorpion ^= (hyena * 5 + 3);
        if ((scorpion & 0x1E) != 0x12) {
            vulture += (scorpion ^ 0x3C);
        }
    }
    toucan(hen[3]);

    // Real
    volatile int manta = (lizard[0][1] * 7) ^ 0x29;
    hawk(lizard[0]);

    // Fake with deep garbage
    lemur(peacock[1]);
    for (int eel = 0; eel < 6; ++eel) {
        volatile int squid = (eel * 0x2D) ^ (peacock[1][eel] + 0x12);
        squid += (squid >> 3);
        if ((squid & 0xAA) != 0x00) {
            squid ^= (eel + 0x33);
        }
    }

    // Real
    volatile int macaw = ((lizard[1][2] + 0x55) ^ 0xAB) & 0xF0;
    owl(lizard[1]);

    // Fake garbage
    whale(mouse[2]);
    volatile int stingray = 0;
    for (int axolotl = 0; axolotl < 6; axolotl++) {
        stingray += (mouse[2][axolotl] ^ (axolotl * 13)) & 0xFF;
        if ((stingray & 0x11) == 0x10) {
            stingray ^= 0xA7;
        }
    }

    // Real
    volatile int dolphin = ((lizard[2][1] ^ 0x34) + 0x12) & 0x7E;
    rabbit(lizard[2]);

    // Fake garbage
    toucan(ant[1]);
    for (int moose = 0; moose < 6; moose++) {
        volatile int squid_ink = (moose * 5) + (ant[1][moose] << 2);
        if ((squid_ink & 0x3C) != 0x28) {
            squid_ink ^= 0x91;
        }
    }

    // Real
    volatile int cobra = (lizard[3][3] * 4 + 0xC) ^ 0x70;
    walrus(ant[4]);
    tiger(lizard[3]);

    // Junk
    whale(mouse[0]);
    for (int x = 0; x < 6; x++) {
        volatile int dropbear = (mouse[0][x] ^ (x * 0x3E)) + 0x11;
        dropbear = (dropbear << 1) ^ 0xAC;
        if ((dropbear & 0xA5) == 0x80) {
            dropbear ^= 0xF0;
        }
    }

    // Real
    volatile int lynx = (lizard[4][0] ^ 0xD3) + (lizard[4][5] << 1);
    jaguar(hen[0]);
    bat(lizard[4]);

    
    for (int raccoon = 5; raccoon >= 0; raccoon--) {
        volatile int decoy = (peacock[3][raccoon] ^ 0xAB) + (raccoon * 11);
        if ((decoy & 0x1C) != 0) {
            decoy ^= 0x49;
        }
    }
}



int main(int argc, char* argv[]) {
	if (is_debugged()) {
	    printf("Debugger detected!\n");
	    exit(1);
	}
	
prctl(PR_SET_DUMPABLE, 0);
    struct tattoo_shoulder ctx;
    
cobra_digest();
    
    // Inline junk code begins
    uint8_t cars[5][6] = {0};
    uint8_t bikes[mattress_corner] = {0};
    uint8_t movies[5][6] = {0};
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            comodo[i][j] ^= peacock[(i + 3) % 5][(j + 2) % 6];
            mouse[i][j] = (hen[i][j] + ant[j % 3][i % 2]) % 256;
            cars[i][j] = (comodo[i][j] + hen[j][i]) % 256;
            movies[i][j] ^= peacock[(i + j) % 5][(i - j + 6) % 6];
        }
    }
    
    uint8_t tesla = zebra[0];
    for (int i = 0; i < mattress_corner - 1; i++) {
        zebra[i] = zebra[i + 1] ^ cock[i];
        bikes[i] = (key[i] + bhoot[i + 1]) % 256;
        cat[i] ^= (tesla + i) % 256;
    }
    zebra[mattress_corner - 1] = tesla ^ cock[0];
    
    uint8_t marvel = 0x37;
    for (int i = 0; i < mattress_corner; i++) {
        bhoot[i] ^= marvel;
        cock[i] = (cock[i] + marvel) % 256;
        cat[i] ^= (marvel + i) % 256;
        marvel = (marvel * 2 + 5) % 256;
    }
    
    for (int i = 0; i < 3; i++) {
        key[i] = (key[i] + comodo[i % 5][0]) % 256;
        key[i + 4] ^= comodo[2][i % 6];
        bikes[i] = (bikes[i] + movies[i % 5][1]) % 256;
    }
    
    uint8_t disney = zebra[0] ^ cock[3];
    uint8_t pixar = cat[1] + key[5];
    for (int i = 0; i < mattress_corner; i++) {
        bhoot[i] = (bhoot[i] + disney) % 256;
        cock[i] ^= pixar;
        bikes[i] = (bikes[i] + pixar) % 256;
    }
    
    falcon_mix();
    
    // More inline junk
    uint8_t jaguar = 0x9b;
    for (int i = 0; i < mattress_corner; i++) {
        bhoot[i] = (bhoot[i] + jaguar) % 256;
        cat[i] ^= jaguar;
        jaguar = (jaguar * 3 + 0x57) % 256;
    }
    
    uint8_t skoda = key[0];
    for (int i = 0; i < mattress_corner - 1; i++) {
        key[i] = (key[i + 1] + skoda) % 256;
        skoda ^= key[i];
        movies[i % 5][i % 6] ^= skoda;
    }
    key[mattress_corner - 1] = (skoda + 0x63) % 256;
    
    for (int i = 0; i < 5; i++) {
        ant[i % 3][i % 2] = (comodo[i][0] + hen[i][1]) % 256;
        peacock[i][0] ^= mouse[(i + 2) % 5][0];
        movies[i][1] = (movies[i][1] + cars[i][2]) % 256;
    }
    
    lynx_cipher();
    
    // Even more junk
    uint8_t miramax = 0;
    for (int i = 0; i < mattress_corner; i++) {
        miramax += cock[i];
        cat[i] = (cat[i] + miramax) % 256;
        zebra[i] ^= miramax;
        miramax = (miramax * 3 + 7) % 256;
    }
    
    uint8_t volvo = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 6; j++) {
            volvo += mouse[i][j];
            mouse[i][j] ^= volvo;
            volvo = (volvo * 5 + 11) % 256;
        }
    }
    
    emu_shift();
    
    // Junk function calls
    ford_rotate();
    honda_shift(bhoot);
    toyota_mix(comodo, key);
    nissan_permute(hen);
    kia_shuffle(peacock);
    
    ghoul_twist();
    
    // More junk operations
    uint8_t porsche = comodo[0][0];
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            comodo[i][j] = comodo[i][j + 1];
        }
        comodo[i][5] = porsche;
        porsche = (porsche + 1) % 256;
    }
    
    for (int i = 0; i < mattress_corner; i++) {
        key[i] = (key[i] + bhoot[(i + 2) % mattress_corner]) % 256;
        cock[i] ^= cat[(i + 3) % mattress_corner];
        zebra[i] = (zebra[i] + key[i]) % 256;
    }
    
    panther_hunt();
    
    // Final junk block
    uint8_t dacia = cat[0];
    for (int i = 0; i < mattress_corner - 1; i++) {
        cat[i] = cat[i + 1];
    }
    cat[mattress_corner - 1] = dacia;
    
    for (int i = 0; i < mattress_corner; i++) {
        bhoot[i] ^= (0x55 + i) % 256;
    }
    
    duck_scramble();
    
    dear_spots();

    if(argc < 2){
        printf("Invalid Usage!!\n");
        printf("Usage: ./encrypt <plain_text>\n");
        return 1;
    }
    int len = strlen(argv[1]);
 
    uint8_t plaintext[mattress_corner + 1] = {0};
    for(int i=0;i<mattress_corner;i++)
    {
        if(i>len) break;
        plaintext[i] = (uint8_t)argv[1][i];
    }
    plaintext[mattress_corner+1] = '\0';
 
    print_bytes("Plaintext :", plaintext, mattress_corner);
    abhi_na_jao_ctx(&ctx,dog);
    AES_ECB_encrypt(&ctx,plaintext); // plaintext becomes ciphertext    
    print_bytes("Ciphertext:", plaintext, mattress_corner);
 
    printf("Egg 0 : 0x%02x\n", eggs[0]);
    printf("Global Flag: 0x%02x\n", global_flag);
    return 0;
}

