import subprocess

import re

import time

import os



EXECUTABLE = "./final_encrypt_L3.out"

TEST_FILE = "test_results.txt"



def parse_test_file(filepath):

    with open(filepath, 'r') as f:

        content = f.read()



    test_blocks = content.split("Plaintext:")[1:]  # Skip header

    tests = []



    for block in test_blocks:

        lines = block.strip().splitlines()

        plaintext = lines[0].strip()

        expected_cipher = lines[1].split(":")[1].strip()

        expected_egg = lines[3].split(":")[1].strip()

        expected_flag = lines[4].split(":")[1].strip()



        tests.append({

            "plaintext": plaintext,

            "expected_cipher": expected_cipher.lower(),

            "expected_egg": expected_egg.lower(),

            "expected_flag": expected_flag.lower()

        })



    return tests



def extract_output(output):

    cipher_match = re.search(r"Ciphertext::([0-9a-fA-F ]+)", output)

    egg_match = re.search(r"Egg 0 *: *(0x[0-9a-fA-F]+)", output)

    flag_match = re.search(r"Global Flag: *(0x[0-9a-fA-F]+)", output)



    cipher = cipher_match.group(1).replace(" ", "").lower() if cipher_match else None

    egg = egg_match.group(1).lower() if egg_match else None

    flag = flag_match.group(1).lower() if flag_match else None



    return cipher, egg, flag



def run_test_case(plaintext, expected_cipher, expected_egg, expected_flag):

    try:

        start = time.time()

        result = subprocess.run([EXECUTABLE, plaintext], stdout=subprocess.PIPE, stderr=subprocess.PIPE, timeout=2)

        end = time.time()



        output = result.stdout.decode()

        actual_cipher, actual_egg, actual_flag = extract_output(output)



        match = (actual_cipher == expected_cipher and actual_egg == expected_egg and actual_flag == expected_flag)



        print("\nPlaintext: {}".format(plaintext))

        print("Expected CipherText: {}".format(expected_cipher))

        print("Actual   CipherText: {}".format(actual_cipher))

        print("Expected Egg 0     : {}".format(expected_egg))

        print("Actual   Egg 0     : {}".format(actual_egg))

        print("Expected Flag      : {}".format(expected_flag))

        print("Actual   Flag      : {}".format(actual_flag))

        print("Time of execution  : {:.6f} seconds".format(end - start))

        print("Match Result       : {}".format("✅ Matched" if match else "❌ MISMATCHED"))



    except subprocess.TimeoutExpired:

        print("\nPlaintext: {}".format(plaintext))

        print("❌ Error: Execution exceeded 2 seconds.")



def main():

    if not os.path.exists(EXECUTABLE):

        print("Executable '{}' not found.".format(EXECUTABLE))

        return



    test_cases = parse_test_file(TEST_FILE)

    for case in test_cases:

        run_test_case(case["plaintext"], case["expected_cipher"], case["expected_egg"], case["expected_flag"])



    print("\nSize of executable: {} bytes".format(os.path.getsize(EXECUTABLE)))



if __name__ == "__main__":

    main()

