/*

  gperf.c

  Stress test the Game API.
  Performance on MicroEmulator is misleading; a real phone
  is very unlikely to be able to keep up.

  Features: sprite multi-instantiation, sprite transformations,
  animated sprites/tiles and priority reordering.

*/

#include <stdlib.h>
#include <conio.h>
#include <jbit.h>

#define N_OF_SPRITES 64

#define IMAGE_ID 1

#define TEMPLATE_ID 0
#define BACKGROUND_ID N_OF_SPRITES
#define SCORE_ID BACKGROUND_ID + 1

#define SCORE_COLS 10

static void setup()
{
	// set max layer id (limit is 255 => 256 tiled layers/sprites)
	req_put(REQ_LDIM);
	req_put(SCORE_ID);
	req_end();

	// background is visible through cells set to 0
	req_put(REQ_SETBGCOL);
	req_put(COLOR_LIGHTGREEN);
	req_end();

	// disable console, enable layer manager
	IO[ENABLE] = ENABLE_BGCOL | ENABLE_LAYERS;

	// init random number generator
	_randomize();
}

static void set_ref_pixel(unsigned char id)
{
	// set reference pixel
	req_put(REQ_LSPREFPX);
	req_put(id);
	req_put(DATATYPE_U8);
	req_put(8);
	req_put(8);
	req_end();
}

static void set_priority(unsigned char id, unsigned short pri)
{
	// lower is nearer to the user
	req_put(REQ_LSETPRI);
	req_put(id);
	req_put(DATATYPE_U16);
	req_put(pri & 0xFF);
	req_put(pri >> 8);
	req_end();
}

static void set_anim_tile(unsigned char tile)
{
	// lower is nearer to the user
	req_put(REQ_LTLANIM);
	req_put(BACKGROUND_ID);
	req_put(255);
	req_put(tile);
	req_end();
}

static void create_background()
{
	unsigned char i, x, y;

	// create image
	req_put(REQ_IDUMMY);
	req_put(IMAGE_ID);
	req_put(IDUMMY_TILES);
	req_put(8); // tile width
	req_put(8); // tile height
	req_put(16); // cols
	req_put(16); // rows
	req_put(COLOR_GREEN); // background
	req_put(COLOR_BLACK); // foreground
	req_end();

	// create tiled layer
	req_put(REQ_LTILED);
	req_put(BACKGROUND_ID);
	req_put(IMAGE_ID);
	req_put(8); // tile width
	req_put(8); // tile height
	req_put(1); // # of animated tiles
	req_put(DATATYPE_U8);
	req_put(50); // cols
	req_put(50); // rows
	req_end();

	set_priority(BACKGROUND_ID, 0xFFFF);

	// set pos
	req_put(REQ_LSETPOS);
	req_put(BACKGROUND_ID);
	req_put(DATATYPE_I8);
	req_put(-100);
	req_put(-100);
	req_end();

	IO[LID] = BACKGROUND_ID;
	i = 0;
	for (y = 0; y < 50; y++) {
		IO[TROWLO] = y;
		for (x = 0; x < 50; x++) {
			IO[TCOLLO] = x;
			if ((y & 1) == 1)
				IO[TCELL] = -1; // animated tile
			else
				IO[TCELL] = i;
			i++;
		}
	}
	IO[LCTL] = LCTL_ENABLE;
}

static void create_score()
{
	// create image '1'..'9'
	req_put(REQ_IDUMMY);
	req_put(IMAGE_ID);
	req_put(IDUMMY_TILES);
	req_put(8); // tile width
	req_put(8); // tile height
	req_put(9); // cols
	req_put(1); // rows
	req_put(COLOR_YELLOW); // background
	req_put(COLOR_BLACK); // foreground
	req_end();

	// create tiled layer
	req_put(REQ_LTILED);
	req_put(SCORE_ID);
	req_put(IMAGE_ID);
	req_put(8); // tile width
	req_put(8); // tile height
	req_put(0); // # of animated tiles
	req_put(DATATYPE_U8);
	req_put(SCORE_COLS); // cols
	req_put(1); // rows
	req_end();

	// priority can be negative
	req_put(REQ_LSETPRI);
	req_put(SCORE_ID);
	req_put(DATATYPE_I8);
	req_put(-1);
	req_end();

	// fill layer with '1'
	req_put(REQ_LTLFILL);
	req_put(SCORE_ID);
	req_put(1);
	req_end();

	// enable
	IO[LID] = SCORE_ID;
	IO[LCTL] = LCTL_ENABLE;
}

static void create_template()
{
	// create image
	req_put(REQ_IDUMMY);
	req_put(IMAGE_ID);
	req_put(IDUMMY_SPRITE);
	req_put(16); // width
	req_put(16); // height
	req_put(4); // # of frames
	req_put(COLOR_LIGHTBLUE); // background
	req_put(COLOR_BLACK); // foreground
	req_put('A');
	req_end();

	// create sprite (width and height are used to compute # of frames)
	req_put(REQ_LSPRITE);
	req_put(TEMPLATE_ID);
	req_put(IMAGE_ID);
	req_put(16); // width
	req_put(16); // height
	req_end();

	set_ref_pixel(TEMPLATE_ID);

	// enable
	IO[LID] = TEMPLATE_ID;
	IO[LCTL] = LCTL_ENABLE;
}

static void destroy_image()
{
	req_put(REQ_IDESTROY);
	req_put(IMAGE_ID);
	req_end();
}

static void create_instances()
{
	int id;

	for (id = 1; id < N_OF_SPRITES; id++) {

		// create from template (should share image data)
		req_put(REQ_LSPCOPY);
		req_put(id);
		req_put(TEMPLATE_ID);
		req_end();

		set_ref_pixel(id);

		// enable and move
		IO[LID] = id;
		IO[LCTL] = LCTL_ENABLE;
		IO[LX] = abs(rand()) % 80;
		IO[LY] = id << 1;

	}
}

static void main_loop()
{
	static unsigned char i, t = 0, id = 0;
	static unsigned short j = 0;

	while (!kbhit()) {

		// move every sprite
		for (i = 0; i < N_OF_SPRITES; i++) {
			IO[LID] = i;
			if (j & 0x20)
				IO[LX]--;
			else
				IO[LX]++;
		}

		// transform & animate one sprite
		IO[LID] = id;
		IO[SFRAME] = t & 3;
		IO[STRANSFM] = t & 7;

		// change its priority
		// (first N_OF_SPRITES times should just confirm priority)
		set_priority(id, j);

		// move background
		IO[LID] = BACKGROUND_ID;
		if (j & 0x20)
			IO[LY]--;
		else
			IO[LY]++;

		// change animated tile
		set_anim_tile(j & 15);

		// update score
		IO[LID] = SCORE_ID;
		IO[TCOLLO] = SCORE_COLS - 1;
		IO[TROWLO] = 0;
		for (i = 0; i < SCORE_COLS; i++) {
			if (IO[TCELL] != 9) {
				IO[TCELL]++;
				break;
			}
			IO[TCELL] = 1;
			IO[TCOLLO]--;
		}

		t++;
		if (t == N_OF_SPRITES - 1)
			t = 0;
		id++;
		if (id == N_OF_SPRITES)
			id = 0;
		j++;
		vsync();

	}
}

int main(void)
{
	setup();
	create_background();
	create_score();
	create_template();
	destroy_image();
	create_instances();
	main_loop();
	return 0;
}
