import sys
import re

if (len(sys.argv) != 3):
    raise TypeError('Illegal number of parameters. Expected 2 paramters\n Usage:\t python3 HEX_STRING FILE_NAME')

if (len(sys.argv[1]) % 2) != 0:
    raise TypeError('hex_string must be of even length')

x = re.findall(r"([A-F, a-f, 0-9])", sys.argv[1])
if len(sys.argv[1]) != len(x):
    raise TypeError('hex_string must only contain characters according to ([A-F, a-f, 0-9])')

with open(sys.argv[2], 'wb') as file:
    binary_format = bytearray(bytes.fromhex(sys.argv[1]))
    file.write(binary_format)
