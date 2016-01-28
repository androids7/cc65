#
# Makefile for cc65 samples (xv65)
#
# This Makefile requires GNU make
#

CL=../../bin/cl65

%.jb: %.c
	$(CL) -t xv65 -O2 -o $@ $<

%.jb: %.s
	$(CL) -t xv65 -o $@ header.s $<

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
		../../asminc/io2.inc \
		../../include/_xv65.h \
		../../include/xv65.h \
		../../include/_io2.h \
		../../include/io2.h \
		../../cfg/xv65.cfg \
		../../cfg/io2.cfg \
		../../lib/xv65.lib \
		../../lib/io2.lib \
		../../libsrc/io2/header.s

.PHONY:	clean
clean:
	$(RM) *~ *.o *.jb cc65-jbit.zip
