#include <stdint.h>
#include "threefish.h"
#include <stdio.h>

#if 0 /* TODO change to 0 after you complete this task */
/*

TODO FREE TEXT ASSIGNMENT

If there was a FAQ for this assignment, what question and answer would've helped you the most?

Q: The keyschedule formula makes no sense, why would you take mod 5 of a subkey???

A: The modulo operators and such are for calculating the lower index for the K

*/
#warning "FAIL you have not completed the free text assignment"
#endif

// Programming assignment by Arttu Mäkinen (246085) and Antti Ruhala (253037)

void mix(uint64_t in1, uint64_t in2, uint64_t * out1, uint64_t * out2, uint8_t rotation_value)
{
	//Addition
	*out1 = in1 + in2;

	//Rotation
	*out2 = (in2 << rotation_value) | (in2 >> (64 - rotation_value));
	uint64_t left = (in2 << rotation_value); //for testing
	uint64_t right = (in2 >> (64 - rotation_value)); //for testing


	//XOR
	*out2 = (*out1) ^ (*out2);

}

void permutate(uint64_t* word1, uint64_t* word3)
{
	// the input pointers are words that come from the mix function as output
	// word0 and word 1 come from MIX_1, word2 and word 3 come from MIX_2

	// switching words 3 and 1
	uint64_t temp = *word1;
	*word1 = *word3;
	*word3 = temp;

	// "the output of the permutation is the output of the round"

}

/* Under key at k and tweak at t, encrypt 32 bytes of plaintext at p and store it at c. */
void threefish(unsigned char* c, const unsigned char* p, const unsigned char* k, const unsigned char* t) {

	// array of rotate constant R for round i, j
	// i = i mod 8
	int rotate_constant_array[8][2];
	rotate_constant_array[0][0] = 14;
	rotate_constant_array[0][1] = 16;
	rotate_constant_array[1][0] = 52;
	rotate_constant_array[1][1] = 57;
	rotate_constant_array[2][0] = 23;
	rotate_constant_array[2][1] = 40;
	rotate_constant_array[3][0] = 5;
	rotate_constant_array[3][1] = 37;
	rotate_constant_array[4][0] = 25;
	rotate_constant_array[4][1] = 33;
	rotate_constant_array[5][0] = 46;
	rotate_constant_array[5][1] = 12;
	rotate_constant_array[6][0] = 58;
	rotate_constant_array[6][1] = 22;
	rotate_constant_array[7][0] = 32;
	rotate_constant_array[7][1] = 32;



	// generate subkeys and store them somewhere
	uint64_t subkeys[19][4];
	uint64_t originalkey[5];
	uint64_t tweakword[3];
	uint8_t subkey_ind = 0;
	uint64_t out0;
	uint64_t out1;
	uint64_t out2;
	uint64_t out3;

	memcpy(&originalkey[0], k, sizeof(uint64_t));
	memcpy(&originalkey[1], &k[8], sizeof(uint64_t));
	memcpy(&originalkey[2], &k[16], sizeof(uint64_t));
	memcpy(&originalkey[3], &k[24], sizeof(uint64_t));
	memcpy(&tweakword[0], t, sizeof(uint64_t));
	memcpy(&tweakword[1], &t[8], sizeof(uint64_t));

	originalkey[4] = (originalkey[0] ^ originalkey[1] ^ originalkey[2] ^ originalkey[3]) ^ 0x1BD11BDAA9FC1A22;
	tweakword[2] = tweakword[0] ^ tweakword[1];

	for (int s = 0; s < 19; s++)
	{
		subkeys[s][0] = originalkey[(s % 5)];
		subkeys[s][1] = originalkey[(s + 1) % 5] + tweakword[s % 3];
		subkeys[s][2] = originalkey[(s + 2) % 5] + tweakword[(s + 1) % 3];
		subkeys[s][3] = originalkey[(s + 3) % 5] + s;
	}

	// divide the plaintext into 4 words of 64 bits
	uint64_t in0 = 0;
	uint64_t in1 = 0;
	uint64_t in2 = 0;
	uint64_t in3 = 0;

	memcpy(&in0, p, sizeof(in0));
	memcpy(&in1, &p[8], sizeof(in1));
	memcpy(&in2, &p[16], sizeof(in2));
	memcpy(&in3, &p[24], sizeof(in3));

	//start rounds
	for (int i = 0; i < 72; i++) {
		// a subkey is injected every 4 rounds, as addition mod 2⁶⁴
		// add subkey if round number is divisible by 4
		if ((i % 4) == 0) {
			in0 += subkeys[subkey_ind][0];
			in1 += subkeys[subkey_ind][1];
			in2 += subkeys[subkey_ind][2];
			in3 += subkeys[subkey_ind][3];
			subkey_ind += 1;
		}

		// put the words into the mix function
		mix(in0, in1, &out0, &out1, rotate_constant_array[i % 8][0]);
		mix(in2, in3, &out2, &out3, rotate_constant_array[i % 8][1]);

		// permutate
		permutate(&out1, &out3);

		// prepare for new round
		in0 = out0;
		in1 = out1;
		in2 = out2;
		in3 = out3;
	}

	// last subkey addition
	in0 += subkeys[18][0];
	in1 += subkeys[18][1];
	in2 += subkeys[18][2];
	in3 += subkeys[18][3];

	// after last round turn the uin64's back into 64-bit words and reconstruct into *c
	// *c = combined_ciphertext
	memcpy(c, &in0, sizeof(uint64_t));
	memcpy(&c[8], &in1, sizeof(uint64_t));
	memcpy(&c[16], &in2, sizeof(uint64_t));
	memcpy(&c[24], &in3, sizeof(uint64_t));
}
