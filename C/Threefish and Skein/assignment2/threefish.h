#include <inttypes.h>

void mix(uint64_t in1, uint64_t in2, uint64_t* out1, uint64_t* out2, uint8_t rotation_value);
void permutate(uint64_t* word1, uint64_t* word3);

/* Implement the following API.
 * You can add your own functions above, but don't modify below this line.
 */

 /* Under key at k and tweak at t, encrypt 32 bytes of plaintext at p and store it at c. */
void threefish(unsigned char* c, const unsigned char* p, const unsigned char* k, const unsigned char* t);

