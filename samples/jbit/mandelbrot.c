/*****************************************************************************
 * mandelbrot sample program for cc65.                                       *
 *                                                                           *
 * (w)2002 by groepaz/hitmen, TGI support by Stefan Haubenthal               *
 * JBit port by Emanuele Fornara                                             *
 *****************************************************************************/

/*

  JBit is very slow here.

  The IO chip might get a math (int/float/double) subsystem in the future;
  on one hand it would be easy to implement, on the other hand I don't
  consider it a priority and it would force the split of the MIDP2
  distribution in two versions (CLDC 1.0/1.1).

  This demo allows us to:

  - Have a reference for future CPU/VM optimizations.
  - Test the stability of JBit and the accuracy of the 6502 emulation.
  - Test the PNG generator with multiple deflate blocks.
  - Post a nice screenshot.

*/

#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include <jbit.h>


/* Graphics definitions */
signed short SCREEN_X;
signed short SCREEN_Y;
unsigned char MAXCOL;

/*

  Poor Man's TGI
  ==============

  TGI is not supported in JBit; the gfx model of the MIDP platform is too
  different from the one you can find in most real 8-bit machines.
  In MIDP you create an immutable image and then render it to the display.
  Screens in games are usually drawn by composing parts of immutable images.

  In other words, in JBit there is no framebuffer that can be updated in
  real-time; what we do here is to stream the pixels one by one to the IO chip
  to generate an immutable image. At the end the image is shown.

  JBit will eventually get some drawing primitives (e.g. lines, rectangles,
  arcs, etc...) of its own; that's what IEMPTY and IMKIMMUT are for.

*/

// #define USE_RGBA

#define IMAGE_ID 1

static unsigned char palette[] = {
	0x00, 0x40, 0x80, 0xA0, 0xA8, 0xB0, 0xB8, 0xC0,
	0xC8, 0xD0, 0xD8, 0xE0, 0xE8, 0xF0, 0xF8, 0xFF
};

static unsigned char is_color;

#ifdef USE_RGBA

#define tgi_setcolor(color) ( \
	is_color ? \
	( \
		req_put(0), \
		req_put(0), \
		req_put(palette[color]), \
		req_put(255) \
	) : ( \
		req_put(palette[color]), \
		req_put(palette[color]), \
		req_put(palette[color]), \
		req_put(255) \
	) \
)

#else

#define tgi_setcolor(color) req_put(color)

#endif

#define tgi_setpixel(x, y)

static void tgi_init()
{
	req_put(REQ_DPYINFO);
	req_end();
	SCREEN_X = *(unsigned*)&IODAT[DPYINFO_WIDTH];
	SCREEN_Y = *(unsigned*)&IODAT[DPYINFO_HEIGHT];
	is_color = IODAT[DPYINFO_FLAGS] & DPYINFO_FLAGS_ISCOLOR;
	MAXCOL = 16;
	// SCREEN_X = 24; SCREEN_Y = 24;
}

static void tgi_done()
{
	IO[ENABLE] = ENABLE_BGCOL | ENABLE_CONSOLE;
}

static void png_begin()
{
	unsigned char color;

	req_put(REQ_IPNGGEN); // Create a new image using the PNG generator
	req_put(IMAGE_ID);
	req_put(SCREEN_X & 0xFF); // Width (u16)
	req_put(SCREEN_X >> 8);
	req_put(SCREEN_Y & 0xFF); // Height (u16)
	req_put(SCREEN_Y >> 8);
	req_put(8); // Depth (8 bpp = 256 levels/colors)
#ifdef USE_RGBA
	req_put(IPNGGEN_CT_TRUECOLOR_ALPHA); // Color type
	req_put(0); // Flags
#else
	req_put(IPNGGEN_CT_INDEXED_COLOR); // Color type
	req_put(0); // Flags
	req_put(MAXCOL - 1);
	for (color = 0; color < MAXCOL; color++) {
		req_put(is_color ? 0 : palette[color]); // red
		req_put(is_color ? 0 : palette[color]); // green
		req_put(palette[color]); // blue
	}
#endif
}

static void png_end()
{
	req_end();
	if (IO[REQRES] != 0) {
		unsigned char i, c;
		req_put(REQ_IDUMMY);
		req_put(IMAGE_ID);
		req_put(IDUMMY_SIMPLE);
		req_put(SCREEN_X & 0xFF); // Width (u16)
		req_put(SCREEN_X >> 8);
		req_put(SCREEN_Y & 0xFF); // Height (u16)
		req_put(SCREEN_Y >> 8);
		req_put(COLOR_BLACK); // background
		req_put(COLOR_RED); // foreground
		for (i = 0; c = "PNGGEN Err"[i]; i++)
			req_put(c);
		req_end();
	}
	req_put(REQ_SETBGIMG);
	req_put(IMAGE_ID);
	req_end();
	IO[ENABLE] = ENABLE_BGCOL | ENABLE_BGIMG;
}


#define maxiterations   32
#define fpshift         (10)
#define tofp(_x)        ((_x)<<fpshift)
#define fromfp(_x)      ((_x)>>fpshift)
#define fpabs(_x)       (abs(_x))

#define mulfp(_a,_b)    ((((signed long)_a)*(_b))>>fpshift)
#define divfp(_a,_b)    ((((signed long)_a)<<fpshift)/(_b))

/* Use static local variables for speed */
#pragma static-locals (1);



void mandelbrot (signed short x1, signed short y1, signed short x2,
		 signed short y2)
{
    register unsigned char count;
    register signed short r, r1, i;
    register signed short xs, ys, xx, yy;
    register signed short x, y;

    /* calc stepwidth */
    xs = ((x2 - x1) / (SCREEN_X));
    ys = ((y2 - y1) / (SCREEN_Y));

    yy = y1;
    for (y = 0; y < (SCREEN_Y); y++) {
	gotoxy(0, 0);
        cprintf("%03u", y + 1);
	vsync();
	yy += ys;
	xx = x1;
	for (x = 0; x < (SCREEN_X); x++) {
	    xx += xs;
	    /* do iterations */
	    r = 0;
	    i = 0;
	    for (count = 0; (count < maxiterations) &&
		 (fpabs (r) < tofp (2)) && (fpabs (i) < tofp (2));
		 ++count) {
		r1 = (mulfp (r, r) - mulfp (i, i)) + xx;
		/* i = (mulfp(mulfp(r,i),tofp(2)))+yy; */
		i = (((signed long) r * i) >> (fpshift - 1)) + yy;
		r = r1;
	    }
	    if (count == maxiterations) {
		tgi_setcolor (0);
	    } else {
		if (MAXCOL == 2)
		    tgi_setcolor (1);
		else
		    tgi_setcolor (count % MAXCOL);
	    }
	    /* set pixel */
	    tgi_setpixel (x, y);
	}
    }
}

int main (void)
{
    clock_t t;
    unsigned long sec;
    unsigned sec10;

    /* Initialize graphics */
    tgi_init ();

    IO[CONCOLS] = 7;
    IO[CONROWS] = 1;
    clrscr ();
    cprintf("---/%03u", SCREEN_Y);

    t = clock ();

    /* calc mandelbrot set */
    png_begin();
    mandelbrot (tofp (-2), tofp (-2), tofp (2), tofp (2));
    png_end();

    t = clock () - t;

    /* Fetch the character from the keyboard buffer and discard it */
    (void) cgetc ();

    /* shut down gfx mode and return to textmode */
    tgi_done ();

    /* Calculate stats */
    sec = (t * 10) / CLK_TCK;
    sec10 = sec % 10;
    sec /= 10;

    /* Output stats */
    clrscr ();
    cprintf ("%lu.%us", sec, sec10);

    /* Wait for a key, then end */
    (void) cgetc ();

    /* Done */
    return EXIT_SUCCESS;

}
