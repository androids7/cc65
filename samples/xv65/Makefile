#
# Makefile for cc65 samples (jbit)
#
# This Makefile requires GNU make
#

CL=../../bin/cl65
HDR=../../libsrc/xv65/header

%.jb: %.c
	$(CL) -t xv65 -O2 -o $@ $<

%.jb: %.s
	$(CL) -t xv65 -o $@ $(HDR).s $<

.PHONY:	all
all: \
	testsys.jb \
	req.jb \
	console.jb \
	xtermpal.jb \
	hello.jb

testsys.jb: testsys.c
	$(CL) -t xv65 -O2 -o $@ $< sys.c

PACK=cc65-jbit.zip

.PHONY:	pack
pack:
	zip -j $(PACK) \
		../../asminc/xv65.inc \
		../../asminc/jbit.inc \
		../../include/_xv65.h \
		../../include/xv65.h \
		../../include/jbit.h \
		../../cfg/xv65.cfg \
		../../cfg/jbit.cfg \
		../../lib/xv65.lib \
		../../lib/jbit.lib \
		../../libsrc/jbit/header.s

.PHONY:	clean
clean:
	$(RM) *~ $(HDR).o *.o *.jb cc65-jbit.zip
