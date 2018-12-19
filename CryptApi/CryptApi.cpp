// This is the main DLL file.
#include "stdafx.h"
#include "CryptApi.h"

//CRYPTO CONFIGURATION PARAMETERS
#define BIT_SHIFT 3
#define XOR_KEY 0x3C
#define ENABLE_XOR_VARIANCE true
////////////////////////////////

int get_rs_mask(int shift)
{
	switch (shift)
	{
	case 0:
		return 0x00;
	case 1:
		return 0x01;
	case 2:
		return 0x03;
	case 3:
		return 0x07;
	case 4:
		return 0x0F;
	case 5:
		return 0x1F;
	case 6:
		return 0x3F;
	case 7:
		return 0x7F;
	default:
		throw "get_rs_mask -> Error, shift argument outside legal range 0-7";
	}
}

void shift_right(char* buf, int msg_len, int shift)
{
	unsigned char tmp = 0x00, tmp2 = 0x00;
	for (int k = 0; k <= msg_len; k++)
	{
		if (k == 0)
		{
			tmp = buf[k];
			buf[k] >>= shift;
		}
		else
		{
			tmp2 = buf[k];
			buf[k] >>= shift;
			buf[k] |= ((tmp & get_rs_mask(shift)) << (8 - shift));

			if (k != msg_len)
				tmp = tmp2;
		}
	}
}

int get_ls_mask(int shift)
{
	switch (shift)
	{
	case 0:
		return 0x00;
	case 1:
		return 0x80;
	case 2:
		return 0xC0;
	case 3:
		return 0xE0;
	case 4:
		return 0xF0;
	case 5:
		return 0xF8;
	case 6:
		return 0xFC;
	case 7:
		return 0xFE;
	default:
		throw "get_ls_mask -> Error, shift argument outside legal range 0-7";
	}
}

void shift_left(char* buf, int msg_len, int shift)
{
	char tmp = 0x00, tmp2 = 0x00;
	for (int k = msg_len; k >= 0; k--)
	{
		if (k == msg_len)
		{
			tmp = buf[k];
			buf[k] <<= shift;
		}
		else
		{
			tmp2 = buf[k];
			buf[k] <<= shift;
			buf[k] |= ((tmp & get_ls_mask(shift)) >> (8 - shift));

			tmp = tmp2;
		}
	}
}

void crypt(char* buf, int msg_len, bool decrypt = false)
{
	if (!decrypt)
	{
		shift_right(buf, msg_len, BIT_SHIFT);
		for (int k = 0; k < msg_len; k++)
		{
			buf[k] = buf[k] ^ XOR_KEY ^ k * (ENABLE_XOR_VARIANCE ? 2 : 0);
		}
		buf[msg_len] = '\0';
	}
	else
	{
		for (int k = 0; k < msg_len; k++)
		{
			buf[k] = buf[k] ^ XOR_KEY ^ k * (ENABLE_XOR_VARIANCE ? 2 : 0);
		}
		shift_left(buf, (msg_len)-1, BIT_SHIFT);
	}
}