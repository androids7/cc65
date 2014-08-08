#
# Makefile for cc65 samples (primo)
#
# This Makefile requires GNU make
#

CL=../../bin/cl65
HDR=../../libsrc/primo/header

%.jb: %.c
	$(CL) -t primo -O2 -o $@ $< sys.c

%.jb: %.s
	$(CL) -t primo -o $@ $(HDR).s $<

.PHONY:	all
all: \
	cblink.jb

.PHONY:	clean
clean:
	$(RM) *~ $(HDR).o *.o *.jb
