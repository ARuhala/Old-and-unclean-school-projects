#include <stdint.h>
#include "threefish.h"

#if 1 /* TODO change to 0 after you complete this task */
/*

TODO FREE TEXT ASSIGNMENT

If there was a FAQ for this assignment, what question and answer would've helped you the most?

Q: <FILL ME IN>

A: <FILL ME IN>

*/
#warning "FAIL you have not completed the free text assignment"
#endif

// mix function
// ------------------implementation from pdf--------
// MIX(x1,x2){
// y1 = x1 + x2 mod 2^64
//
//
// Values for constant R in rounds i with a variable j(????what is j? ????):
// i = i mod 8
// int rotate_constant_array[8][2] // as in [i][j]
// rotate_constant_array[0][0] = 14;
// rotate_constant_array[0][1] = 16;
// rotate_constant_array[1][0] = 52;
// rotate_constant_array[1][1] = 57;
// rotate_constant_array[2][0] = 23;
// rotate_constant_array[2][1] = 40;
// rotate_constant_array[3][0] = 5;
// rotate_constant_array[3][1] = 37;
// rotate_constant_array[4][0] = 25;
// rotate_constant_array[4][1] = 33;
// rotate_constant_array[5][0] = 46;
// rotate_constant_array[5][1] = 12;
// rotate_constant_array[6][0] = 58;
// rotate_constant_array[6][1] = 22;
// rotate_constant_array[7][0] = 32;
// rotate_constant_array[7][1] = 32;
//
// y2 = ( x2 ROTATE_LEFT_by_R(i,j) ) XOR y1
//
// return y1,y2
//}



// permute function as pseudo code
// permute(old_words){
// new_words[0] = old_words[0]
// new_words[1] = old_words[3]
// new_words[2] = old_words[2]
// new words[3] = old_words[1]
// return new_words
//}
// same for every round



// subkey generation aka key schedule function
// generates the subkeys from the key and the tweak
    // each subkey consists of 1. key words, 2. tweak words, 3. counter value
// To create the key schedule:
    // the key k and tweak t are extended with extra parity word that is the XOR of all the other words(?)
    // each subkey is a combination of (see figure 3):
        // 1. all but one of the extended key words
        // 2. two of the tree extentded tweak words
        // 3. subkey number





/* Under key at k and tweak at t, encrypt 32 bytes of plaintext at p and store it at c. */
void threefish(unsigned char *c, const unsigned char *p, const unsigned char *k, const unsigned char *t) {

    // 72 rounds in total
    // each round four MIXes followed by a permutation of the 4 64-bit words (4 in 256 bit)
        // 2 words go into MIX, and it outputs 2 words

        // all (in total) 4 outputs from MIX go into PERMUTE and it outputs 4 words
        // these outputs are used for the next round

    // a subkey is injected every 4 rounds, as addition
    // rotation constants repeat every 8 rounds

}

