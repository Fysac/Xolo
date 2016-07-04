# xolo

### XOR cipher implemented in C.

**Usage**

`xolo [options] <input> <output>`

`-h`: Show usage.

`-k`: Use existing key (default: generate random key).

`-b`: Generate this many bytes for key (default: 1024).

**Examples**

Encrypt a file:

`xolo secret.txt encrypted.xor`

Encrypt a file with bigger key:

`xolo -b 4096 secret.txt encrypted.xor`

Decrypt a file using existing key:

`xolo -k private.key encrypted.xor secret.txt`

**Obligatory Crypto Disclaimer**

xolo is for educational purposes only. XOR ciphers/OTPs are unwieldy and vulnerable to numerous attacks. Don't use this for anything requiring actual security.
