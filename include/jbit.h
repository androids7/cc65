//
// jbit.h
//

#ifndef _JBIT_H_
#define _JBIT_H_

// {{{ p2c io.p !
#define REQPUT 0x01
#define REQEND 0x02
#define REQRES 0x03
#define REQPTRLO 0x04
#define REQPTRHI 0x05
#define ENABLE 0x10
#define FRMFPS 0x11
#define FRMDRAW 0x12
#define GKEY0 0x13
#define GKEY1 0x14
#define RANDOM 0x17
#define KEYBUF 0x18
#define CONCOLS 0x20
#define CONROWS 0x21
#define CONCX 0x22
#define CONCY 0x23
#define CONCCHR 0x24
#define CONCFG 0x25
#define CONCBG 0x26
#define CONVIDEO 0x28
#define CONROW0 0x28
#define CONROW1 0x32
#define CONROW2 0x3C
#define CONROW3 0x46
#define LID 0x50
#define LCTL 0x51
#define LX 0x52
#define LY 0x53
#define SFRAME 0x54
#define STRANSFM 0x55
#define SCWITH 0x56
#define TCOLLO 0x57
#define TCOLHI 0x58
#define TROWLO 0x59
#define TROWHI 0x5A
#define TCELL 0x5B
#define REQDAT 0x60
#define REQ_NOREQ 0x00
#define REQ_TIME 0x02
#define REQ_LOADROM 0x06
#define REQ_DPYINFO 0x10
#define REQ_SETBGCOL 0x11
#define REQ_SETPAL 0x12
#define REQ_SETBGIMG 0x13
#define REQ_IDESTROY 0x14
#define REQ_IDIM 0x15
#define REQ_IINFO 0x16
#define REQ_ILOAD 0x17
#define REQ_IDUMMY 0x18
#define REQ_IPNGGEN 0x19
#define REQ_IEMPTY 0x1A
#define REQ_IMKIMMUT 0x1B
#define REQ_IRAWRGBA 0x1C
#define REQ_LMVIEW 0x20
#define REQ_LMPOS 0x21
#define REQ_LDESTROY 0x22
#define REQ_LDIM 0x23
#define REQ_LTILED 0x24
#define REQ_LSPRITE 0x25
#define REQ_LSETPOS 0x26
#define REQ_LGETPOS 0x27
#define REQ_LMOVE 0x28
#define REQ_LSETPRI 0x29
#define REQ_LGETPRI 0x2A
#define REQ_LTLANIM 0x2B
#define REQ_LTLFILL 0x2C
#define REQ_LTLPUT 0x2D
#define REQ_LTLSCRLL 0x2E
#define REQ_LSPCOPY 0x2F
#define REQ_LSPAPOS 0x30
#define REQ_LSPREFPX 0x31
#define REQ_LSPCLRCT 0x32
#define REQ_FXTONE 0x40
#define REQ_FXVIBRA 0x41
#define REQ_FXFLASH 0x42
#define ENABLE_BGCOL 0x01
#define ENABLE_BGIMG 0x02
#define ENABLE_CONSOLE 0x04
#define ENABLE_LAYERS 0x08
#define TIME_ABS 0x01
#define TIME_RESET 0x02
#define TIME_1 0x01
#define TIME_10 0x02
#define TIME_100 0x03
#define TIME_1000 0x04
#define DPYINFO_WIDTH 0x00
#define DPYINFO_HEIGHT 0x02
#define DPYINFO_COLORDEPTH 0x04
#define DPYINFO_ALPHADEPTH 0x05
#define DPYINFO_FLAGS 0x06
#define DPYINFO_FLAGS_ISCOLOR 0x80
#define DPYINFO_FLAGS_ISMIDP2 0x40
#define DPYINFO_FLAGS_ISTOUCH 0x20
#define SETPAL_STD 0x00
#define SETPAL_RGB 0x01
#define IINFO_WIDTH 0x00
#define IINFO_HEIGHT 0x02
#define IINFO_FLAGS 0x04
#define IINFO_FLAGS_ISMUTABLE 0x80
#define IDUMMY_SIMPLE 0x01
#define IDUMMY_SPRITE 0x02
#define IDUMMY_TILES 0x03
#define IPNGGEN_CT_GRAYSCALE 0x00
#define IPNGGEN_CT_TRUECOLOR 0x02
#define IPNGGEN_CT_INDEXED_COLOR 0x03
#define IPNGGEN_CT_GRAYSCALE_ALPHA 0x04
#define IPNGGEN_CT_TRUECOLOR_ALPHA 0x06
#define IPNGGEN_FLAGS_IDX0TRANSP 0x01
#define IPNGGEN_FLAGS_PALREF 0x02
#define IPNGGEN_FLAGS_ZOOM0 0x04
#define IPNGGEN_FLAGS_ZOOM1 0x08
#define IRAWRGBA_FLAGS_ALPHA 0x01
#define DATATYPE_U8 0x01
#define DATATYPE_I8 0x02
#define DATATYPE_U16 0x03
#define DATATYPE_I16 0x04
#define LCTL_SHIFTX0 0x01
#define LCTL_SHIFTX1 0x02
#define LCTL_SHIFTY0 0x04
#define LCTL_SHIFTY1 0x08
#define LCTL_PXLCOLL 0x40
#define LCTL_ENABLE 0x80
#define LCTL_SHIFTX_MASK 0x03
#define LCTL_SHIFTY_MASK 0x0C
#define LTRANSFM_NONE 0x00
#define LTRANSFM_ROT90 0x05
#define LTRANSFM_ROT180 0x03
#define LTRANSFM_ROT270 0x06
#define LTRANSFM_MIRROR 0x02
#define LTRANSFM_MIRROR_ROT90 0x07
#define LTRANSFM_MIRROR_ROT180 0x01
#define LTRANSFM_MIRROR_ROT270 0x04
#define GKEY0_UP 0x02
#define GKEY0_LEFT 0x04
#define GKEY0_RIGHT 0x20
#define GKEY0_DOWN 0x40
#define GKEY1_FIRE 0x01
#define GKEY1_A 0x02
#define GKEY1_B 0x04
#define GKEY1_C 0x08
#define GKEY1_D 0x10
#define ALINE_TOP 0x01
#define ALINE_LEFT 0x02
#define ALINE_RIGHT 0x04
#define ALINE_BOTTOM 0x08
#define COLOR_BLACK 0x00
#define COLOR_WHITE 0x01
#define COLOR_RED 0x02
#define COLOR_CYAN 0x03
#define COLOR_VIOLET 0x04
#define COLOR_PURPLE 0x04
#define COLOR_GREEN 0x05
#define COLOR_BLUE 0x06
#define COLOR_YELLOW 0x07
#define COLOR_ORANGE 0x08
#define COLOR_BROWN 0x09
#define COLOR_LIGHTRED 0x0A
#define COLOR_GRAY1 0x0B
#define COLOR_GRAY2 0x0C
#define COLOR_LIGHTGREEN 0x0D
#define COLOR_LIGHTBLUE 0x0E
#define COLOR_GRAY3 0x0F
#define CH_ULCORNER 0x8C
#define CH_URCORNER 0x8A
#define CH_LLCORNER 0x85
#define CH_LRCORNER 0x83
#define CH_HLINE 0x86
#define CH_VLINE 0x89
#define CH_TTEE 0x8E
#define CH_RTEE 0x89
#define CH_BTEE 0x8B
#define CH_LTEE 0x8D
#define CH_CROSS 0x8F
// }}}

#define IO		((unsigned char *)0x0200)
#define IODAT		((unsigned char *)(IO + REQDAT))
#define IOVID		((unsigned char *)(IO + CONVIDEO))

#define req_put(x)	(*(unsigned char*)(IO + REQPUT) = (x))
#define req_end()	(*(unsigned char*)(IO + REQEND) = 0)

void vsync (void);

#endif
