#!/bin/bash

# Exit on any error
set -e

# Step 1: Compile key generator and egg encryptor
gcc -o keygen_encryptor keygen_encryptor.c
./keygen_encryptor
gcc -o egg_encryptor egg_encryptor.c
./egg_encryptor

# Step 2: Compile main program
gcc main.c -o a.out

# Step 3: First level encryption
gcc encrypt.c -o encrypt
./encrypt
xxd -i encrypted_a.out > payload.h

# Step 4: Loader for level 1
gcc loader_keygen_encryptor.c -o loader_keygen_encryptor
./loader_keygen_encryptor
gcc loader.c -o final_encrypt.out
./final_encrypt.out abc

# Step 5: Second level encryption
gcc encrypt_L88.c -o encrypt_L88
./encrypt_L88
xxd -i encrypted_a.out_L88 > payload_L88.h

# Step 6: Loader for level 2
gcc loader_keygen_encryptor_L88.c -o loader_keygen_encryptor_L88
./loader_keygen_encryptor_L88
gcc loader_L88.c -o final_encrypt_L88.out
./final_encrypt_L88.out abc

# Step 7: Third level encryption
gcc encrypt_L89.c -o encrypt_L89
./encrypt_L89
xxd -i encrypted_a.out_L89 > payload_L89.h

# Step 8: Compile final level encrypted binary
gcc loader_L89.c -o safe_main
./safe_main abc

