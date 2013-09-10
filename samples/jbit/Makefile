#
# Makefile for cc65 samples (jbit)
#
# This Makefile requires GNU make
#

CL=../../bin/cl65
HDR=../../libsrc/jbit/header

%.jb: %.c
	$(CL) -t jbit -O2 -o $@ $<

%.jb: %.s
	$(CL) -t jbit -o $@ $(HDR).s $<

%.prg: %.c
	$(CL) -O2 -o $@ $< c64jb.c

.PHONY:	all
all: \
	bounce.jb \
	cciao.jb \
	clock.jb \
	cpubm.jb \
	dpyinfo.jb \
	fps.jb \
	gperf.jb \
	hello.jb \
	mandelbrot.jb \
	newline.jb \
	pngtest.jb \
	rand.jb \
	time.jb \
	smile.jb \
	bounce.prg \
	cpubm.prg

.PHONY:	clean
clean:
	$(RM) *~ $(HDR).o *.o *.jb *.prg
