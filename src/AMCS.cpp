#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "AMCS.hpp"

// ===================================================================
// WARNING: RELIES ON OVERFLOWS OF X86! IF THE PROCESSOR DOES NOT
// SUPPORT OVERFLOW OF BITS AND SIMPLY ERRORS OUT, THE ALGORITHM DOES NOT WORK!
// ===================================================================
// Can be used after the table stage to break repetition.
// Performs some spits on data that shift the integer value of data.
void encryptSpit(char* data, int length, const uint64_t _key) {
	union { char c[sizeof(_key)]; uint64_t i; } key;
	key.i = _key;

	// b is bit in the key, used to determine IF to spit.
	// j is the character in the key, which is used to spit on the current character.
	// j is incremented only after a spit.
	for (int i = 0, j = 0, b = 0; i < length; i++, b++, j++) {
		if (b >= sizeof(_key)*8)
			b = 0;
		if (j >= sizeof(_key))
			j = 0;

		if (_key & (1ULL<<b)) { // spit
			data[i] += key.c[j]; // RELIES ON X86!
		}
		else { // despit
			data[i] -= ~key.c[j]; // RELIES ON X86! Also the reason that this is ~ is a little complex, but it's what makes the thing reusable with decrypt.
		}
	}
}

// ===================================================================
// WARNING: RELIES ON OVERFLOWS OF X86! IF THE PROCESSOR DOES NOT
// SUPPORT UNDERFLOW OF BITS AND SIMPLY ERRORS OUT, THE ALGORITHM DOES NOT WORK!
// ===================================================================
void decryptSpit(char* data, int length, const uint64_t _key) {
	return encryptSpit(data, length, ~_key);
}

// class Table {
// 	public:
// 	char symbols[2][256];

// 	Table(uint64_t key) {
// 		fillLayer(0, key);
// 		fillLayer(1, key>>31);
		
// 		int n = 0;
// 		for (int i = 0; i < 256; i++) {
// 			printf("%hhx%hhx = %hhx\n", symbols[0][i], symbols[1][i], i);
// 		}
// 	}

// 	private:
// 	void fillLayer(int i, uint32_t subKey) {
// 		int s;
// 		for (int j = 0, k = 0; j < 256; j++, k++) {
// 			if (k == sizeof(subKey)*8)
// 				k = 0;
			
// 			if (subKey & (1<<k))
// 				symbols[i][j] = s++;
// 		}
// 		for (int j = 0, k = 0; j < 256; j++, k++) {
// 			if (k == sizeof(subKey)*8)
// 				k = 0;
			
// 			if (!(subKey & (1<<k)))
// 				symbols[i][j] = s++;
// 		}
// 	}
// };

// // data must be capable of containing a buffer twice it's mentioned "length"
// void encryptTable(char* data, int length, Table& t) {
// 	// We encrypt from the end to the start in order to not write over unencrypted data, since we make the buffer twice as big
// 	for (int i = length - 1; i >= 0; i--) {
// 		int tableEntry = data[i];

// 		data[i<<2+0] = t.symbols[0][tableEntry];
// 		data[i<<2+1] = t.symbols[1][tableEntry];
// 	}
// }

// // "length" points to the size of data as it is encrypted, meaning it's twice the length of the unencrypted data.
// void decryptTable(char* data, int length, Table& t) {
// 	for (int i = 0; i < length; i+=2) {
// 		int tableEntry = data[i];

// 		data[i>>2] = t.symbols[0][tableEntry];
// 		data[i>>2] = t.symbols[1][tableEntry];
// 	}
// }

// TODO: Potentially additional complexity can be to add padding to BitSwap, which would make the key swap not neighbors but rather bytes seperated by some padding.
void encryptSwap(char* data, int length, const uint64_t bitsCopy) {
	uint64_t bits = bitsCopy; // Shift erases data, so bits is reset
	char tmp;
	int i, b; // i for data, b for bits.

	// length-1 because we can't swap last byte
	for (i = 0, b = 0; i < length-1; i++, b++, bits >>= 1) {
		if (b == sizeof(bits)*8) { // Reset bits every time we finish
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
void decryptSwap(char* data, int length, const uint64_t bits) {
	char tmp;
	int i, b; // i for data, b for bits.

	// length%64 -1 will work because in the beginning there is an if anyway.
	for (i = length-2, b = length%(sizeof(bits)*8) - 1; i >= 0; i--, b--) {
		if (b == -1) // Reset bits every time we finish
			b = sizeof(bits)*8 - 1;

		// I HAVE NO IDEA WHY THIS IS B-1, NO FUCKING CLUE, BUT IT WORKS.
		if ((bits & (1ULL<<(b-1))) && i != length-1) { // It was swapped forkward, Swap backward
			tmp = data[i];
			data[i] = data[i+1];
			data[i+1] = tmp;
		}
	}
}

int main(int ArgsNum, char** Args) {
	char test[] = "Good luck understanding this bitch :)";
	puts(test);

	uint64_t key = rand() + (((long long)rand())<<31);
	
	// encryptSwap(test, sizeof(test), key);
	encryptSpit(test, sizeof(test)-1, key);
	puts(test);

	decryptSpit(test, sizeof(test)-1, key);
	// decryptSwap(test, sizeof(test), key);
	puts(test);

	return 0;
}
