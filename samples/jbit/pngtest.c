/*

  pngtest.c

  Test every valid combination of Color type and Depth.
  A device with color display and support for transparency is assumed.

  A naive implementation is fine since we don't care about
  performance here.

 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <jbit.h>

#define MAX_SIZE 64
#define IMAGE_ID 1

static char buf[16];
unsigned char size;
unsigned char concols, conrows;
unsigned char lastconrow;

unsigned char *row;
unsigned short rowsize;
unsigned char pixelsize;

static unsigned char color_types[] = {
	IPNGGEN_CT_GRAYSCALE,
	IPNGGEN_CT_TRUECOLOR,
	IPNGGEN_CT_INDEXED_COLOR,
	IPNGGEN_CT_GRAYSCALE_ALPHA,
	IPNGGEN_CT_TRUECOLOR_ALPHA
};

static const char *color_type_to_tag(unsigned char color_type)
{
	switch (color_type)
	{
	case IPNGGEN_CT_GRAYSCALE:
		return "GRAY";
	case IPNGGEN_CT_TRUECOLOR:
		return "RGB";
	case IPNGGEN_CT_INDEXED_COLOR:
		return "PAL";
	case IPNGGEN_CT_GRAYSCALE_ALPHA:
		return "GRAY+A";
	case IPNGGEN_CT_TRUECOLOR_ALPHA:
		return "RGB+A";
	default:
		return "?";
	}
}

static const unsigned char *color_type_to_depths(unsigned char color_type)
{
	switch (color_type)
	{
	case IPNGGEN_CT_GRAYSCALE:
		return "\x01\x02\x04\x08\x10";
	case IPNGGEN_CT_TRUECOLOR:
		return "\x08\x10";
	case IPNGGEN_CT_INDEXED_COLOR:
		return "\x01\x02\x04\x08";
	case IPNGGEN_CT_GRAYSCALE_ALPHA:
		return "\x08\x10";
	case IPNGGEN_CT_TRUECOLOR_ALPHA:
		return "\x08\x10";
	default:
		return "";
	}
}

static void resize(unsigned char cols, unsigned char rows)
{
    IO[CONCOLS] = cols;
    IO[CONROWS] = rows;
}

static void reset_image()
{
	req_put(REQ_IDESTROY);
	req_put(IMAGE_ID);
	req_end();
	req_put(REQ_SETBGIMG);
	req_put(IMAGE_ID);
	req_end();
}

static void setup_overlay()
{
	unsigned char x, y;

	bordercolor(COLOR_LIGHTBLUE);
	resize(0, 0);
	screensize(&concols, &conrows);
	lastconrow = conrows - 1;
	clrscr();
	for (y = 1; y < conrows - 1; y++)
		for (x = 0; x < concols; x++)
			cputcxy(x, y, 0);
	IO[ENABLE] |= ENABLE_BGIMG;
}

static void clear_overlay(unsigned char y)
{
	unsigned char x;

	for (x = 0; x < concols; x++)
		cputcxy(x, y, ' ');
}

static unsigned char yval;
static unsigned char *r;
static unsigned char bval;
static unsigned char bpos;
static unsigned char bits[] = {
	0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01
};

static void compute_sizes(unsigned char color_type, unsigned char depth)
{
	switch (color_type) {
	case IPNGGEN_CT_GRAYSCALE:
	case IPNGGEN_CT_INDEXED_COLOR:
		pixelsize = depth;
		break;
	case IPNGGEN_CT_GRAYSCALE_ALPHA:
		pixelsize = depth * 2;
		break;
	case IPNGGEN_CT_TRUECOLOR:
		pixelsize = depth * 3;
		break;
	case IPNGGEN_CT_TRUECOLOR_ALPHA:
		pixelsize = depth * 4;
		break;
	}
	rowsize = ((size * pixelsize) + 7) >> 3;
}

#define append_byte(value) (*r++ = (value))
#define append_word(value) (*r++ = (value), *r++ = 0)

static void append_bit1(unsigned char value)
{
	if (value)
		bval |= bits[bpos];
	bpos++;
	if (bpos == 8) {
		append_byte(bval);
		bval = 0;
		bpos = 0;
	}
}

static void append_bit2(unsigned char value)
{
	append_bit1(value & 0x02);
	append_bit1(value & 0x01);
}

static void append_bit4(unsigned char value)
{
	append_bit1(value & 0x08);
	append_bit1(value & 0x04);
	append_bit1(value & 0x02);
	append_bit1(value & 0x01);
}

static unsigned char xval[MAX_SIZE];

static void prepare_xval()
{
	unsigned short i, inc, xval2;

	inc = 0xFFFF / size;
	xval2 = 0;
	for (i = 0; i < size; i++) {
		xval[i] = xval2 >> 8;
		xval2 += inc;
	}
}

static void fill_row(unsigned char color_type, unsigned char depth)
{
	unsigned char x;

	r = row;
	bval = 0;
	bpos = 0;
	for (x = 0; x < size; x++) {
		switch (color_type) {
		case IPNGGEN_CT_GRAYSCALE:
			switch (depth) {
			case 1:
				append_bit1(yval);
				break;
			case 2:
				append_bit2(yval);
				break;
			case 4:
				append_bit4(yval);
				break;
			case 8:
				append_byte(yval);
				break;
			case 16:
				append_word(yval);
				break;
			}
			break;
		case IPNGGEN_CT_INDEXED_COLOR:
			switch (depth) {
			case 1:
				append_bit1(yval);
				break;
			case 2:
				append_bit2(yval);
				break;
			case 4:
				append_bit4(yval);
				break;
			case 8:
				append_byte(yval);
				break;
			}
			break;
		case IPNGGEN_CT_TRUECOLOR:
			switch (depth) {
			case 8:
				append_byte(255);
				append_byte(yval);
				append_byte(0);
				break;
			case 16:
				append_word(255);
				append_word(yval);
				append_word(0);
				break;
			}
			break;
		case IPNGGEN_CT_GRAYSCALE_ALPHA:
			switch (depth) {
			case 8:
				append_byte(yval);
				append_byte(xval[x]);
				break;
			case 16:
				append_word(yval);
				append_word(xval[x]);
				break;
			}
			break;
		case IPNGGEN_CT_TRUECOLOR_ALPHA:
			switch (depth) {
			case 8:
				append_byte(255);
				append_byte(yval);
				append_byte(0);
				append_byte(xval[x]);
				break;
			case 16:
				append_word(255);
				append_word(yval);
				append_word(0);
				append_word(xval[x]);
				break;
			}
			break;
		}
	}
}

static void make_palette(unsigned char depth)
{
	unsigned short i, n = (1 << depth) - 1;
	req_put(n);
	for (i = 0; i <= n; i++) {
		req_put(rand());
		req_put(rand());
		req_put(rand());
	}
}

static unsigned char make_image(unsigned char color_type, unsigned char depth)
{
	unsigned char y;
	unsigned short i, inc, yval2;

	req_put(REQ_IPNGGEN);
	req_put(IMAGE_ID);
	req_put(size); // Width (u16)
	req_put(0);
	req_put(size); // Height (u16)
	req_put(0);
	req_put(depth);
	req_put(color_type);
	if (color_type == IPNGGEN_CT_INDEXED_COLOR) {
		req_put(IPNGGEN_FLAGS_IDX0TRANSP); // Flags
		make_palette(depth);
	} else {
		req_put(0); // Flags
	}
	compute_sizes(color_type, depth);
	if (depth >= 8)
		inc = 0xFFFF / size;
	else
		inc = (1 << (depth + 8)) / size;
	yval2 = 0;
	memset(row, 0, rowsize);
	prepare_xval();
	for (y = 0; y < size; y++) {
		yval = yval2 >> 8;
		fill_row(color_type, depth);
		for (i = 0; i < rowsize; i++)
			req_put(row[i]);
		yval2 += inc;
	}
	req_end();
	if (IO[REQRES] != 0)
		return 0;
	req_put(REQ_SETBGIMG);
	req_put(IMAGE_ID);
	req_end();
	return 1;
}

static void test_images()
{
	unsigned char i, color_type, j;
	const char *tag;
	const unsigned char *depths;
	clock_t t;
	unsigned long sec;
	unsigned sec10;

	setup_overlay();
	for (i = 0; i < sizeof(color_types); i++) {
		color_type = color_types[i];
		tag = color_type_to_tag(color_type);
		depths = color_type_to_depths(color_type);
		for (j = 0; depths[j]; j++) {
			clear_overlay(0);
			gotoxy(0, 0);
			cprintf("%s %u", tag, depths[j]);
			clear_overlay(lastconrow);
			cputsxy(0, lastconrow, "Wait...");
			t = clock();
			if (make_image(color_type, depths[j])) { 
				t = clock() - t;
				sec = (t * 10) / CLK_TCK;
				sec10 = sec % 10;
				sec /= 10;
				sprintf(buf, "%lu.%us", sec, sec10);
			} else {
				sprintf(buf, "FAILED");
			}
			clear_overlay(lastconrow);
			cputsxy(0, lastconrow, buf);
			cgetc();
			reset_image();
		}
	}
}

static void setup_main_menu()
{
	IO[ENABLE] &= ~ENABLE_BGIMG;
	bordercolor(COLOR_WHITE);
	resize(10, 4);
	clrscr();
	cputsxy(0, 0, "Sel. size:");
	cputsxy(0, 1, "1=8  2=16");
	cputsxy(0, 2, "3=32 4=64");
	cputsxy(0, 3, "0=Exit");
}

int main(void)
{
	row = malloc(MAX_SIZE * 8);
	setup_main_menu();
	while (1) {
		size = 0;
		switch (cgetc()) {
		case '1':
			size = 8;
			break;
		case '2':
			size = 16;
			break;
		case '3':
			size = 32;
			break;
		case '4':
			size = 64;
			break;
		case '0':
			exit(0);
		}
		if (size) {
			test_images();
			setup_main_menu();
		}
	}
}
