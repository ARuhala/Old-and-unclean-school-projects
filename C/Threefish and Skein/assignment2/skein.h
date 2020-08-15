// Authors:
// Arttu Mäkinen 
// Antti Ruhala


#include <stdint.h>
#include <stdbool.h>

/* This is your hash instance context, i.e., hash state.
 * You could put the following stuff inside here:
 * - buffered message bytes
 * - current offset within said buffer
 * - chaining value
 * - tweak
 * - leprechaun gold
 * - next week's correct lotto numbers
 */
typedef struct {

	//Buffer
	unsigned char msg_buffer[32];
	unsigned char finalize_message[32];
	unsigned char buffer[32];
	unsigned char finalize_buf[32];
	int buf_offset;

	//Tweak
	int position; // 0– 95 The number of bytes in the string processed so far (including this block)
	int finalize_position;
	bool bitPad; // 119 Set if this block contains the last byte of an input whose length was not an integral number of bytes. 0 otherwise.
	uint8_t type; // 120–125 Type of the field(config, message, output, etc.)
	bool first; // 126 Set for the first block of a UBI compression.
	bool final; //; 127 Set for the last block of a UBI compression.

} context;


enum twk_type{
	CONFIG = 4,
	MESSAGE = 48,
	OUTPUT = 63,
} twk_type;

void func(unsigned char* a, int len, context* ctx);

/* Implement the following API.
 * You can add your own functions above, but don't modify below this line.
 */

 /* Initialize fresh context ctx */
void init(context* ctx);

/* Under context ctx, incrementally process len bytes at a */
void update(unsigned char* a, int len, context* ctx);

/* Under context ctx, finalize the hash and place the digest at a */
void finalize(unsigned char* a, context* ctx);

