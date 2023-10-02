#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "AMCS.hpp"

// TODO: Potentially additional complexity can be to add padding to BitSwap, which would make the key swap not neighbors but rather bytes seperated by some padding.
void encryptBitSwap(char* data, int length, const uint64_t bitsCopy) {
	uint64_t bits = bitsCopy; // Shift erases data, so bits is reset
	char tmp;
	int i, b; // i for data, b for bits.

	// length-1 because we can't swap last byte
	for (i = 0, b = 0; i < length-1; i++, b++, bits >>= 1) {
		if (b == 64) { // Reset bits every time we finish
			bits = bitsCopy;
			b = 0;
		}

		if ((bits & 1) && i != length-1) { // Swap forward
			tmp = data[i];
			data[i] = data[i+1];
			data[i+1] = tmp;
		}
	}
}
void decryptBitSwap(char* data, int length, const uint64_t bitsCopy) {
	uint64_t bits = bitsCopy; // Shift erases data, so bits is reset
	char tmp;
	int i, b; // i for data, b for bits.

	// length%64 -1 will work because in the beginning there is an if anyway.
	for (i = length-2, b = length%64 - 1; i >= 0; i--, b--) {
		if (b == -1) { // Reset bits every time we finish
			bits = bitsCopy;
			b = 63;
		}

		if ((bits & (((uint64_t)1)<<(b-1))) && i != length-1) { // It was swapped forkward, Swap backward
			tmp = data[i];
			data[i] = data[i+1];
			data[i+1] = tmp;
		}
	}
}

int main(int ArgsNum, char** Args) {
	char test[] = "Good luck understanding this bitch :) Good luck understanding this bitch :) Good luck understanding this bitch :)";
	puts(test);
	uint64_t key = rand() + (((long long)rand())<<31);
	encryptBitSwap(test, sizeof(test), key);
	puts(test);
	decryptBitSwap(test, sizeof(test), key);
	puts(test);

	return 0;
}
