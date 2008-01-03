/*
 *	draw.c
 *
 *	Routines for drawing text on images
 *
 *	Copyright 2000, Jeroen Vreeken
 *	This program is published under the GNU public license version 2
 *	See also the file 'COPYING'
 *
 */

#include <ctype.h>
#include "motion.h"

/* The number of characters in draw_table. */
#define NUM_CHARS 81

struct draw_char {
	char ascii;
	char pix[8][7];
};

struct big_char {
	char ascii;
	char pix[16][14];
};

struct big_char big_table[NUM_CHARS];

struct draw_char draw_table[NUM_CHARS]= {
	{
		'0',
		{
			{0,0,1,1,1,0,0},
			{0,1,2,2,2,1,0},
			{1,2,1,1,2,2,1},
			{1,2,1,2,1,2,1},
			{1,2,1,2,1,2,1},
			{1,2,2,1,1,2,1},
			{0,1,2,2,2,1,0},
			{0,0,1,1,1,0,0}
		}
	},
	{
		'1',	
		{
			{0,0,0,1,0,0,0},
			{0,0,1,2,1,0,0},
			{0,1,2,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,1,2,2,2,1,0},
			{0,0,1,1,1,0,0}
		}
	},
	{
		'2',
		{
			{0,0,1,1,1,0,0},
			{0,1,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{0,1,1,2,2,1,0},
			{0,1,2,1,1,0,0},
			{1,2,1,1,1,1,0},
			{1,2,2,2,2,2,1},
			{0,1,1,1,1,1,0}
		}
	},
	{
		'3',
		{
			{0,0,1,1,1,0,0},
			{0,1,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{0,1,1,2,2,1,0},
			{0,1,0,1,1,2,1},
			{1,2,1,1,1,2,1},
			{0,1,2,2,2,1,0},
			{0,0,1,1,1,0,0}
		}
	},
	{
		'4',
		{
			{0,0,0,0,1,0,0},
			{0,0,0,1,2,1,0},
			{0,0,1,2,2,1,0},
			{0,1,2,1,2,1,0},
			{1,2,2,2,2,2,1},
			{0,1,1,1,2,1,0},
			{0,0,0,1,2,1,0},
			{0,0,0,0,1,0,0}
		}
	},
	{
		'5',
		{
			{0,1,1,1,1,1,0},
			{1,2,2,2,2,2,1},
			{1,2,1,1,1,1,0},
			{1,2,2,2,2,1,0},
			{0,1,1,1,1,2,0},
			{0,1,1,1,1,2,0},
			{1,2,2,2,2,1,0},
			{0,1,1,1,1,0,0}
		}
	},
	{
		'6',
		{
			{0,0,1,1,1,1,0},
			{0,1,2,2,2,2,1},
			{1,2,1,1,1,1,0},
			{1,2,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{1,2,1,1,1,2,1},
			{0,1,2,2,2,1,0},
			{0,0,1,1,1,0,0}
		}
	},
	{
		'7',
		{
			{0,1,1,1,1,1,0},
			{1,2,2,2,2,2,1},
			{0,1,1,1,1,2,1},
			{0,0,0,1,2,1,0},
			{0,0,1,2,1,0,0},
			{0,1,2,1,0,0,0},
			{0,1,2,1,0,0,0},
			{0,0,1,0,0,0,0}
		}
	},
	{
		'8',
		{
			{0,0,1,1,1,0,0},
			{0,1,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{0,1,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{1,2,1,1,1,2,1},
			{0,1,2,2,2,1,0},
			{0,0,1,1,1,0,0}
		}
	},
	{
		'9',
		{
			{0,0,1,1,1,0,0},
			{0,1,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{0,1,2,2,2,2,1},
			{0,1,1,1,1,2,1},
			{1,2,1,1,1,2,1},
			{0,1,2,2,2,1,0},
			{0,0,1,1,1,0,0}
		}
	},
	{
		'"',
		{
			{0,0,1,0,1,0,0},
			{0,1,2,1,2,1,0},
			{0,1,2,1,2,1,0},
			{0,0,1,0,1,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0}
		}
	},
	{
		'/',
		{
			{0,0,0,0,1,0,0},
			{0,0,0,1,2,1,0},
			{0,0,0,1,2,1,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,1,2,1,0,0,0},
			{0,1,2,1,0,0,0},
			{0,0,1,0,0,0,0}
		}
	},
	{
		'(',
		{
			{0,0,0,1,0,0,0},
			{0,0,1,2,1,0,0},
			{0,1,2,1,0,0,0},
			{0,1,2,1,0,0,0},
			{0,1,2,1,0,0,0},
			{0,1,2,1,0,0,0},
			{0,0,1,2,1,0,0},
			{0,0,0,1,0,0,0}
		}
	},
	{
		')',
		{
			{0,0,0,1,0,0,0},
			{0,0,1,2,1,0,0},
			{0,0,0,1,2,1,0},
			{0,0,0,1,2,1,0},
			{0,0,0,1,2,1,0},
			{0,0,0,1,2,1,0},
			{0,0,1,2,1,0,0},
			{0,0,0,1,0,0,0}
		}
	},
	{
		'@',
		{
			{0,0,1,1,1,0,0},
			{0,1,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{1,2,1,2,2,2,1},
			{1,2,1,2,2,2,1},
			{1,2,1,1,1,1,0},
			{0,1,2,2,2,1,0},
			{0,0,1,1,1,0,0}
		}
	},
	{
		'~',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,1,0,0,0,0},
			{0,1,2,1,0,1,0},
			{1,2,1,2,1,2,1},
			{0,1,0,1,2,1,0},
			{0,0,0,0,1,0,0},
			{0,0,0,0,0,0,0}
		}
	},
	{
		'#',
		{
			{0,0,1,0,1,0,0},
			{0,1,2,1,2,1,0},
			{1,2,2,2,2,2,1},
			{0,1,2,1,2,1,0},
			{0,1,2,1,2,1,0},
			{1,2,2,2,2,2,1},
			{0,1,2,1,2,1,0},
			{0,0,1,0,1,0,0}
		}
	},
	{
		'<',
		{
			{0,0,0,0,0,1,0},
			{0,0,0,1,1,2,1},
			{0,1,1,2,2,1,0},
			{1,2,2,1,1,0,0},
			{0,1,1,2,2,1,0},
			{0,0,0,1,1,2,1},
			{0,0,0,0,0,1,0},
			{0,0,0,0,0,0,0}
		}
	},
	{
		'>',
		{
			{0,1,0,0,0,0,0},
			{1,2,1,1,0,0,0},
			{0,1,2,2,1,1,0},
			{0,0,1,1,2,2,1},
			{0,1,2,2,1,1,0},
			{1,2,1,1,0,0,0},
			{0,1,0,0,0,0,0},
			{0,0,0,0,0,0,0}
		}
	},
	{
		'|',
		{
			{0,0,0,1,0,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,0,1,0,0,0}
		}
	},
	{
		',',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,1,1,0,0,0},
			{0,1,2,2,1,0,0},
			{0,1,2,2,1,0,0},
			{0,1,2,1,0,0,0},
			{0,0,1,0,0,0,0}
		}
	},
	{
		'.',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,1,1,0,0,0},
			{0,1,2,2,1,0,0},
			{0,1,2,2,1,0,0},
			{0,0,1,1,0,0,0},
			{0,0,0,0,0,0,0}
		}
	},
	{
		':',
		{
			{0,0,1,1,0,0,0},
			{0,1,2,2,1,0,0},
			{0,1,2,2,1,0,0},
			{0,0,1,1,0,0,0},
			{0,0,1,1,0,0,0},
			{0,1,2,2,1,0,0},
			{0,1,2,2,1,0,0},
			{0,0,1,1,0,0,0}
		}
	},
	{
		'-',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,1,1,1,0,0},
			{0,1,2,2,2,1,0},
			{0,0,1,1,1,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0}
		}
	},
	{
		'+',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,1,0,0,0},
			{0,0,1,2,1,0,0},
			{0,1,2,2,2,1,0},
			{0,0,1,2,1,0,0},
			{0,0,0,1,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0}
		}
	},
	{
		'_',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,1,1,1,1,1,0},
			{1,2,2,2,2,2,1},
			{0,1,1,1,1,1,0}
		}
	},
	{
		'\'',
		{
			{0,0,0,1,0,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,0,1,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0}
		}
	},
	{
		'a',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,1,1,1,1,0},
			{0,1,2,2,2,2,1},
			{1,2,1,1,1,2,1},
			{1,2,1,1,1,2,1},
			{0,1,2,2,2,2,1},
			{0,0,1,1,1,1,0}
		}
	},
	{
		'b',
		{
			{0,1,0,0,0,0,0},
			{1,2,1,0,0,0,0},
			{1,2,1,1,1,0,0},
			{1,2,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{1,2,1,1,1,2,1},
			{1,2,2,2,2,1,0},
			{0,1,1,1,1,0,0}
		}
	},
	{
		'c',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,1,1,1,1,0},
			{0,1,2,2,2,2,1},
			{1,2,1,1,1,1,0},
			{1,2,1,1,1,1,0},
			{0,1,2,2,2,2,1},
			{0,0,1,1,1,1,0}
		}
	},
	{
		'd',
		{
			{0,0,0,0,0,1,0},
			{0,0,0,0,1,2,1},
			{0,0,1,1,1,2,1},
			{0,1,2,2,2,2,1},
			{1,2,1,1,1,2,1},
			{1,2,1,1,1,2,1},
			{0,1,2,2,2,2,1},
			{0,0,1,1,1,1,0}
		}
	},
	{
		'e',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,1,1,1,0,0},
			{0,1,2,2,2,1,0},
			{1,2,2,1,1,2,1},
			{1,2,1,2,2,1,0},
			{0,1,2,2,2,2,1},
			{0,0,1,1,1,1,0}
		}
	},
	{
		'f',
		{
			{0,0,0,0,1,1,0},
			{0,0,0,1,2,2,1},
			{0,0,1,2,1,1,0},
			{0,1,2,2,2,1,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,0,1,0,0,0}
		}
	},
	{
		'g',
		{
			{0,0,0,0,0,0,0},
			{0,0,1,1,1,1,0},
			{0,1,2,2,2,2,1},
			{1,2,1,1,1,2,1},
			{0,1,2,2,2,2,1},
			{0,1,1,1,1,2,1},
			{1,2,2,2,2,1,0},
			{0,1,1,1,1,0,0}
		}
	},
	{
		'h',
		{
			{0,1,0,0,0,0,0},
			{1,2,1,0,0,0,0},
			{1,2,1,1,1,0,0},
			{1,2,1,2,2,1,0},
			{1,2,2,1,1,2,1},
			{1,2,1,0,1,2,1},
			{1,2,1,0,1,2,1},
			{0,1,0,0,0,1,0}
		}
	},
	{
		'i',
		{
			{0,0,0,1,0,0,0},
			{0,0,1,2,1,0,0},
			{0,0,0,1,0,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,1,2,2,2,1,0},
			{0,0,1,1,1,0,0}
		}
	},
	{
		'j',
		{
			{0,0,0,1,0,0,0},
			{0,0,1,2,1,0,0},
			{0,0,0,1,0,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,1,1,2,1,0,0},
			{1,2,2,1,0,0,0},
			{0,1,1,0,0,0,0}
		}
	},
	{
		'k',
		{
			{0,1,0,0,0,0,0},
			{1,2,1,0,0,0,0},
			{1,2,1,0,1,0,0},
			{1,2,1,1,2,1,0},
			{1,2,1,2,1,0,0},
			{1,2,2,1,2,1,0},
			{1,2,1,0,1,2,1},
			{0,1,0,0,0,1,0}
		}
	},
	{
		'l',
		{
			{0,0,1,1,0,0,0},
			{0,1,2,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,0,1,2,1,0},
			{0,0,0,0,1,0,0}
		}
	},
	{
		'm',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,1,1,0,1,0,0},
			{1,2,2,1,2,1,0},
			{1,2,1,2,1,2,1},
			{1,2,1,2,1,2,1},
			{1,2,1,2,1,2,1},
			{0,1,0,1,0,1,0}
		}
	},
	{
		'n',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,1,0,1,1,0,0},
			{1,2,1,2,2,1,0},
			{1,2,2,1,1,2,1},
			{1,2,1,0,1,2,1},
			{1,2,1,0,1,2,1},
			{0,1,0,0,0,1,0}
		}
	},
	{
		'o',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,1,1,1,0,0},
			{0,1,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{1,2,1,1,1,2,1},
			{0,1,2,2,2,1,0},
			{0,0,1,1,1,0,0}
		}
	},
	{
		'p',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,1,1,1,1,0,0},
			{1,2,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{1,2,2,2,2,1,0},
			{1,2,1,1,1,0,0},
			{1,2,1,0,0,0,0},
		}
	},
	{
		'q',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,1,1,1,1,0},
			{0,1,2,2,2,2,1},
			{1,2,1,1,1,2,1},
			{0,1,2,2,2,2,1},
			{0,0,1,1,1,2,1},
			{0,0,0,0,1,2,1}
		}
	},
	{
		'r',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,1,0,1,1,0,0},
			{1,2,1,2,2,1,0},
			{1,2,2,1,1,2,1},
			{1,2,1,0,0,1,0},
			{1,2,1,0,0,0,0},
			{0,1,0,0,0,0,0}
		}
	},
	{
		's',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,1,1,1,1,0},
			{0,1,2,2,2,2,1},
			{1,2,2,2,1,1,0},
			{0,1,1,2,2,2,1},
			{1,2,2,2,2,1,0},
			{0,1,1,1,1,0,0}
		}
	},
	{
		't',
		{
			{0,0,0,1,0,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,1,2,2,2,1,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,0,1,2,1,0},
			{0,0,0,0,1,0,0}
		}
	},
	{
		'u',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,1,0,0,0,1,0},
			{1,2,1,0,1,2,1},
			{1,2,1,0,1,2,1},
			{1,2,1,1,2,2,1},
			{0,1,2,2,1,2,1},
			{0,0,1,1,0,1,0}
		}
	},
	{
		'v',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,1,0,0,0,1,0},
			{1,2,1,0,1,2,1},
			{1,2,1,0,1,2,1},
			{0,1,2,1,2,1,0},
			{0,0,1,2,1,0,0},
			{0,0,0,1,0,0,0}
		}
	},
	{
		'w',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,1,0,0,0,1,0},
			{1,2,1,0,1,2,1},
			{1,2,1,1,1,2,1},
			{1,2,1,2,1,2,1},
			{0,1,2,1,2,1,0},
			{0,0,1,0,1,0,0}
		}
	},
	{
		'x',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,1,0,0,1,0,0},
			{1,2,1,1,2,1,0},
			{0,1,2,2,1,0,0},
			{0,1,2,2,1,0,0},
			{1,2,1,1,2,1,0},
			{0,1,0,0,1,0,0}
		}
	},
	{
		'y',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,1,0,0,0,1,0},
			{1,2,1,0,1,2,1},
			{0,1,2,1,2,1,0},
			{0,0,1,2,1,0,0},
			{0,1,2,1,0,0,0},
			{1,2,1,0,0,0,0}
		}
	},
	{
		'z',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,1,1,1,1,0,0},
			{1,2,2,2,2,1,0},
			{0,1,1,2,1,0,0},
			{0,1,2,1,1,0,0},
			{1,2,2,2,2,1,0},
			{0,1,1,1,1,0,0}
		}
	},
	{
		'A',
		{
			{0,0,1,1,1,0,0},
			{0,1,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{1,2,1,1,1,2,1},
			{1,2,2,2,2,2,1},
			{1,2,1,1,1,2,1},
			{1,2,1,0,1,2,1},
			{0,1,0,0,0,1,0}
		}
	},
	{
		'B',
		{
			{0,1,1,1,1,0,0},
			{1,2,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{1,2,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{1,2,1,1,1,2,1},
			{1,2,2,2,2,1,0},
			{0,1,1,1,1,0,0}
		}
	},
	{
		'C',
		{
			{0,0,1,1,1,0,0},
			{0,1,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{1,2,1,0,0,1,0},
			{1,2,1,0,0,1,0},
			{1,2,1,1,1,2,1},
			{0,1,2,2,2,1,0},
			{0,0,1,1,1,0,0}
		}
	},
	{
		'D',
		{
			{0,1,1,1,1,0,0},
			{1,2,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{1,2,1,0,1,2,1},
			{1,2,1,0,1,2,1},
			{1,2,1,1,1,2,1},
			{1,2,2,2,2,1,0},
			{0,1,1,1,1,0,0}
		}
	},
	{
		'E',
		{
			{0,1,1,1,1,1,0},
			{1,2,2,2,2,2,1},
			{1,2,1,1,1,1,0},
			{1,2,2,2,2,1,0},
			{1,2,1,1,1,0,0},
			{1,2,1,1,1,1,0},
			{1,2,2,2,2,2,1},
			{0,1,1,1,1,1,0}
		}
	},
	{
		'F',
		{
			{0,1,1,1,1,1,0},
			{1,2,2,2,2,2,1},
			{1,2,1,1,1,1,0},
			{1,2,2,2,2,1,0},
			{1,2,1,1,1,0,0},
			{1,2,1,0,0,0,0},
			{1,2,1,0,0,0,0},
			{0,1,0,0,0,0,0}
		}
	},
	{
		'G',
		{
			{0,0,1,1,1,0,0},
			{0,1,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{1,2,1,1,1,1,0},
			{1,2,1,2,2,2,1},
			{1,2,1,1,1,2,1},
			{0,1,2,2,2,1,0},
			{0,0,1,1,1,0,0}
		}
	},
	{
		'H',
		{
			{0,1,0,0,0,1,0},
			{1,2,1,0,1,2,1},
			{1,2,1,1,1,2,1},
			{1,2,2,2,2,2,1},
			{1,2,1,1,1,2,1},
			{1,2,1,0,1,2,1},
			{1,2,1,0,1,2,1},
			{0,1,0,0,0,1,0}
		}
	},
	{
		'I',
		{
			{0,0,1,1,1,0,0},
			{0,1,2,2,2,1,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,1,2,2,2,1,0},
			{0,0,1,1,1,0,0}
		}
	},
	{
		'J',
		{
			{0,0,1,1,1,1,0},
			{0,1,2,2,2,2,1},
			{0,0,1,1,1,2,1},
			{0,0,0,0,1,2,1},
			{0,1,0,0,1,2,1},
			{1,2,1,1,1,2,1},
			{0,1,2,2,2,1,0},
			{0,0,1,1,1,0,0}
		}
	},
	{
		'K',
		{
			{0,1,0,0,0,1,0},
			{1,2,1,0,1,2,1},
			{1,2,1,1,2,1,0},
			{1,2,1,2,1,0,0},
			{1,2,2,2,1,0,0},
			{1,2,1,1,2,1,0},
			{1,2,1,0,1,2,1},
			{0,1,0,0,0,1,0}
		}
	},
	{
		'L',
		{
			{0,1,0,0,0,0,0},
			{1,2,1,0,0,0,0},
			{1,2,1,0,0,0,0},
			{1,2,1,0,0,0,0},
			{1,2,1,0,0,0,0},
			{1,2,1,1,1,0,0},
			{1,2,2,2,2,1,0},
			{0,1,1,1,1,0,0}
		}
	},
	{
		'M',
		{
			{0,1,1,0,1,1,0},
			{1,2,2,1,2,2,1},
			{1,2,1,2,1,2,1},
			{1,2,1,1,1,2,},
			{1,2,1,0,1,2,1},
			{1,2,1,0,1,2,1},
			{1,2,1,0,1,2,1},
			{0,1,0,0,0,1,0}
		}
	},
	{
		'N',
		{
			{0,1,0,0,0,1,0},
			{1,2,1,0,1,2,1},
			{1,2,2,1,1,2,1},
			{1,2,1,2,1,2,1},
			{1,2,1,1,2,2,1},
			{1,2,1,0,1,2,1},
			{1,2,1,0,1,2,1},
			{0,1,0,0,0,1,0}
		}
	},
	{
		'O',
		{
			{0,0,1,1,1,0,0},
			{0,1,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{1,2,1,0,1,2,1},
			{1,2,1,0,1,2,1},
			{1,2,1,1,1,2,1},
			{0,1,2,2,2,1,0},
			{0,0,1,1,1,0,0}
		}
	},
	{
		'P',
		{
			{0,1,1,1,1,0,0},
			{1,2,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{1,2,2,2,2,1,0},
			{1,2,1,1,1,0,0},
			{1,2,1,0,0,0,0},
			{1,2,1,0,0,0,0},
			{0,1,0,0,0,0,0}
		}
	},
	{
		'Q',
		{
			{0,0,1,1,1,0,0},
			{0,1,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{1,2,1,1,1,2,1},
			{1,2,1,2,1,2,1},
			{1,2,1,1,2,1,0},
			{0,1,2,2,1,2,1},
			{0,0,1,1,0,1,0}
		}
	},
	{
		'R',
		{
			{0,1,1,1,1,0,0},
			{1,2,2,2,2,1,0},
			{1,2,1,1,1,2,1},
			{1,2,2,2,2,1,0},
			{1,2,1,2,1,0,0},
			{1,2,1,1,2,1,0},
			{1,2,1,0,1,2,1},
			{0,1,0,0,0,1,0}
		}
	},
	{
		'S',
		{
			{0,0,1,1,1,1,0},
			{0,1,2,2,2,2,1},
			{1,2,1,1,1,1,0},
			{0,1,2,2,2,1,0},
			{0,0,1,1,1,2,1},
			{0,1,1,1,1,2,1},
			{1,2,2,2,2,1,0},
			{0,1,1,1,1,0,0}
		}
	},
	{
		'T',
		{
			{0,1,1,1,1,1,0},
			{1,2,2,2,2,2,1},
			{0,1,1,2,1,1,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,0,1,0,0,0}
		}
	},
	{
		'U',
		{
			{0,1,0,0,0,1,0},
			{1,2,1,0,1,2,1},
			{1,2,1,0,1,2,1},
			{1,2,1,0,1,2,1},
			{1,2,1,0,1,2,1},
			{1,2,1,1,1,2,1},
			{0,1,2,2,2,2,1},
			{0,0,1,1,1,1,0}
		}
	},
	{
		'V',
		{
			{0,1,0,0,0,1,0},
			{1,2,1,0,1,2,1},
			{1,2,1,0,1,2,1},
			{1,2,1,0,1,2,1},
			{1,2,1,0,1,2,1},
			{0,1,2,1,2,1,0},
			{0,0,1,2,1,0,0},
			{0,0,0,1,0,0,0}
		}
	},
	{
		'W',
		{
			{0,1,0,0,0,1,0},
			{1,2,1,0,1,2,1},
			{1,2,1,0,1,2,1},
			{1,2,1,1,1,2,1},
			{1,2,1,2,1,2,1},
			{1,2,1,2,1,2,1},
			{0,1,2,1,2,1,0},
			{0,0,1,0,1,0,0}
		}
	},
	{
		'X',
		{
			{0,1,0,0,0,1,0},
			{1,2,1,0,1,2,1},
			{0,1,2,1,2,1,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,1,2,1,2,1,0},
			{1,2,1,0,1,2,1},
			{0,1,0,0,0,1,0}
		}
	},
	{
		'Y',
		{
			{0,1,0,0,0,1,0},
			{1,2,1,0,1,2,1},
			{0,1,2,1,2,1,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,1,2,1,0,0},
			{0,0,0,1,0,0,0}
		}
	},
	{
		'Z',
		{
			{0,1,1,1,1,1,0},
			{1,2,2,2,2,2,1},
			{0,1,1,1,2,1,0},
			{0,0,1,2,1,0,0},
			{0,1,2,1,0,0,0},
			{1,2,1,1,1,1,0},
			{1,2,2,2,2,2,1},
			{0,1,1,1,1,1,0}
		}
	},
	{
		' ',
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0}
		}
	},
	{
		0,
		{
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0}
		}
	}
};

#define NEWLINE "\\n"

static int draw_textn (unsigned char *image, int startx, int starty, int width, int height, char *text, int len, int factor)
{
	int i, pos, x, y , tempvar;

	if (startx < 0)
		startx = 0;
	if (startx>width/2) {
		startx -= len*(6*(factor+1));
	}
	/* Draw text at normal (small) size. */
	if(!factor) {
		for (pos = 0; pos < len; pos++) {
			if (startx+(pos+1)*6>=width)
				break;
			i=0;
			tempvar=startx+pos*6;
			
			while (draw_table[i].ascii && draw_table[i].ascii!=text[pos]) i++;
			
			for (x=0; x<7; x++) {
				int tempvar_x = tempvar + x;
				for (y=0; y<8; y++) {
					switch(draw_table[i].pix[y][x]) {
						case 1:
							image[tempvar_x+(y+starty)*width]=0;
							break;
						case 2:
							image[tempvar_x+(y+starty)*width]=255;
							break;
						default:
							break;
					}
				}
			}
		}
	}
	/* Draw text at double normal size. */
	else {
		for (pos = 0; pos < len; pos++) {
			if (startx+(pos+1)*12>=width)
				break;
			i=0;
			tempvar=startx+pos*12;
			
			while (big_table[i].ascii && big_table[i].ascii!=text[pos]) i++;
			
			for (x=0; x<14; x++) {
				int tempvar_x = tempvar + x;
				for (y=0; y<16; y++) {
					switch(big_table[i].pix[y][x]) {
						case 1:
							image[tempvar_x+(y+starty)*width]=0;
							break;
						case 2:
							image[tempvar_x+(y+starty)*width]=255;
							break;
						default:
							break;
					}
				}
			}
		}
	}
	return 0;
}

int draw_text (unsigned char *image, int startx, int starty, int width, int height, char *text, int factor)
{
	int num_nl = 0;
	char *end, *begin;
	const int line_space = (factor + 1) * 9;
	
	/* Count the number of newlines in "text" so we scroll it up the image */
	end = text;
	while ((end = strstr(end, NEWLINE))) {
		num_nl++;
		end += sizeof(NEWLINE)-1;
	}
	starty -= line_space * num_nl;
	
	begin = end = text;
	while ((end = strstr(end, NEWLINE))) {
		int len = end-begin;
		draw_textn(image, startx, starty, width, height, begin, len, factor);
		end += sizeof(NEWLINE)-1;
		begin = end;
		starty += line_space;
	}
	draw_textn(image, startx, starty, width, height, begin, strlen(begin), factor);
	return 0;
}

int initialize_chars(void)
{
	int i=0, x, y;
	
	/* Fill the structure 'big_table' with double sized characters. */
	while(draw_table[i].ascii) {
		big_table[i].ascii = draw_table[i].ascii;
		for(x=0; x < 14; x++) {
			for(y=0; y < 16; y++) {
				big_table[i].pix[y][x] = draw_table[i].pix[y/2][x/2];
			}
		}
		i++;
	}
	
	return 0;
}
