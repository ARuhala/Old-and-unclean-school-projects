// Authors:
// Arttu Mäkinen 
// Antti Ruhala


#include <string.h>
#include <stdio.h>
#include "threefish.h"
#include "skein.h"

#if 0 /* TODO change to 0 after you complete this task */
/*

TODO FREE TEXT ASSIGNMENT

If there was a FAQ for this assignment, what question and answer would've helped you the most?

Q: When should we call threefish?  

A: Threefish should be called only when the buffer is full.

*/
#warning "FAIL you have not completed the free text assignment"
#endif

static const uint64_t chaining_values[4] = {
	0xFC9DA860D048B449, 0x2FCA66479FA7D833, 0xB33BC3896656840F, 0x6A54E920FDE8DA69
};

void func(unsigned char* a, int len, context* ctx) {
	unsigned char message[32] = { 0 };
	unsigned char* chaining_vals = &chaining_values;

	int lenght = len > 32 ? 32 : len;
	for (int i = 0; i < lenght; i++)
	{
		message[i] = ctx->msg_buffer[i];
	}

	uint64_t T[2] = { 0,0 };
	T[1] += (uint64_t)ctx->final << (127 - 64);
	T[1] += (uint64_t)ctx->first << (126 - 64);
	T[1] += (uint64_t)ctx->type << (120 - 64);
	T[1] += (uint64_t)ctx->bitPad << (119 - 64);
	T[1] += (uint64_t)ctx->position >> 64;
	T[0] += (uint64_t)ctx->position & 0xffffffffffffffff;

	unsigned char* to_bytes = &T;

	if (ctx->first)
	{
		memcpy(ctx->finalize_buf, ctx->buffer, sizeof(unsigned char) * 32);
		threefish(ctx->buffer, message, chaining_vals, to_bytes);
	}
	else
	{
		memcpy(ctx->finalize_buf, ctx->buffer, sizeof(unsigned char) * 32);
		threefish(ctx->buffer, message, ctx->buffer, to_bytes);
	}

	for (int i = 0; i < 32; i++)
	{
		ctx->buffer[i] = ctx->buffer[i] ^ message[i];
	}
}

void init(context * ctx) {

	//Buffers
	memset(ctx->buffer, 0, sizeof(unsigned char) * 32);
	memset(ctx->msg_buffer, 0, sizeof(unsigned char) * 32);
	memset(ctx->finalize_buf, 0, sizeof(unsigned char) * 32);
	memset(ctx->finalize_message, 0, sizeof(unsigned char) * 32);
	ctx->buf_offset = 0;

	//Tweak
	ctx->position = 0; // 0– 95 The number of bytes in the string processed so far (including this block)
	ctx->finalize_position = 0;
	ctx->bitPad = 0; // 119 Set if this block contains the last byte of an input whose length was not an integral number of bytes. 0 otherwise.
	ctx->type = MESSAGE; // 120–125 Type of the field(config, message = 48, output = 63, etc.)
	ctx->first = 1; // 126 Set for the first block of a UBI compression.
	ctx->final = 0; //; 127 Set for the last block of a UBI compression.
}


/* Under context ctx, incrementally process len bytes at a */
void update(unsigned char* a, int len, context* ctx) {
	int counter = 0;
	int values = 0;
	int offset = ctx->buf_offset - ctx->position;
	while (counter < len)
	{
		values = len - counter > 32 ? 32 : len - counter;
		for (int i = 0; i < values; i++)
		{
			ctx->msg_buffer[offset] = a[i + counter];
			ctx->finalize_message[offset] = a[i + counter];
			ctx->buf_offset += 1;
			offset += 1;
			if (offset == 32)
			{
				ctx->position += 32;
				func(a, 32, ctx);
				offset = 0;
				ctx->first = false;
			}
		}
		counter += 32;
	}
}

void finalize(unsigned char* a, context* ctx) {

	unsigned char* chaining_vals = &chaining_values;
	unsigned char message[32] = { 0 };
	ctx->final = true;
	
	int lenght = ctx->buf_offset % 32;
	if (lenght == 0)
	{
		memcpy(message, ctx->finalize_message, sizeof(unsigned char) * 32);
	}
	else 
	{
		for (int i = 0; i < lenght; i++)
		{
			message[i] = ctx->finalize_message[i];
		}
	}

	if (ctx->buf_offset <= 32) ctx->first = true;
	
	uint64_t T[2] = { 0,0 };
	T[1] += (uint64_t)ctx->final << (127 - 64);
	T[1] += (uint64_t)ctx->first << (126 - 64);
	T[1] += (uint64_t)ctx->type << (120 - 64);
	T[1] += (uint64_t)ctx->bitPad << (119 - 64);
	T[1] += (uint64_t)ctx->buf_offset >> 64;
	T[0] += (uint64_t)ctx->buf_offset & 0xffffffffffffffff;
	unsigned char* to_bytes = &T;
	
	if (ctx->buf_offset <= 32) 
	{
		threefish(ctx->finalize_buf, message, chaining_vals, to_bytes);
		for (int i = 0; i < 32; i++)
		{
			ctx->finalize_buf[i] = ctx->finalize_buf[i] ^ message[i];
		}
	}
	else if(lenght != 0)
	{
		threefish(ctx->finalize_buf, message, ctx->buffer, to_bytes);
		for (int i = 0; i < 32; i++)
		{
			ctx->finalize_buf[i] = ctx->finalize_buf[i] ^ message[i];
		}
	}
	else
	{
		threefish(ctx->finalize_buf, message, ctx->finalize_buf, to_bytes);
		for (int i = 0; i < 32; i++)
		{
			ctx->finalize_buf[i] = ctx->finalize_buf[i] ^ message[i];
		}
	}

	ctx->first = true;
	ctx->type = OUTPUT; // 120–125 Type of the field(config, message = 48, output = 63, etc.)

	T[1] = 0;
	T[0] = 0;

	T[1] += (uint64_t)ctx->final << (127 - 64);
	T[1] += (uint64_t)ctx->first << (126 - 64);
	T[1] += (uint64_t)ctx->type << (120 - 64);
	T[1] += (uint64_t)ctx->bitPad << (119 - 64);
	T[1] += (uint64_t)0;
	T[0] += (uint64_t)8 & 0xffffffffffffffff;

	to_bytes = &T;
	memset(message, 0, sizeof(unsigned char) * 32);
	threefish(ctx->finalize_buf, message, ctx->finalize_buf, to_bytes);

	for (int i = 0; i < 32; i++)
	{
		a[i] = ctx->finalize_buf[i] ^ message[i];
	}
}

