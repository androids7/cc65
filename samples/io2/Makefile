#
# Makefile for cc65 samples (io2)
#
# This Makefile requires GNU make
#

CL=../../bin/cl65
HDR=../../libsrc/io2/header

%.jb: %.c
	$(CL) -t io2 -O2 -o $@ $<

%.jb: %.s
	$(CL) -t io2 -o $@ $(HDR).s $<

%.prg: %.c
	$(CL) -t c64 -O2 -o $@ $< c64jb.c

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
