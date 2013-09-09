#
# Makefile for cc65 samples (jbit)
#
# This Makefile requires GNU make
#

%.jb: %.c
	../../bin/cl65 -O2 -o $@ $< ../../lib/jbit.lib

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
	time.jb

.PHONY:	clean
clean:
	$(RM) -f *~ *.o *.jb
