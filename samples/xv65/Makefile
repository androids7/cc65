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
	sys.jb \
	req.jb \
	hello.jb

.PHONY:	clean
clean:
	$(RM) *~ $(HDR).o *.o *.jb
