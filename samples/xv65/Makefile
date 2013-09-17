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
	scratch.jb \
	hello.jb

testsys.jb: testsys.c
	$(CL) -t xv65 -O2 -o $@ $< sys.c

.PHONY:	clean
clean:
	$(RM) *~ $(HDR).o *.o *.jb
