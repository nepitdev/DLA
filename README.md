# DLA
DLA is an implementation of the Hill Cipher with several modifications to make it more secure. Some improvments include:
* Each of the 4 modulus options is prime and chosen to be just less than a power of 256.
* A salt vector is added to the begining of each message
* The salt vector is never saved unless the user explicity requests that it is
* Each vector in a message is modified based on the SHA-256 of the previous vector

These modifications minimize the size of the ciphertext, reduce predictability, and reduce the liklyhood of a known-plaintext attack.

This project is a work in progress.
