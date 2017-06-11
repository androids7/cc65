#
# Makefile for cc65 samples (io2)
#
# This Makefile requires GNU make
#

.PHONY:	all
all: \
	charset.jb \
	ciao.jb \
	fill1.jb \
	fill2.jb \
	keypad.jb \
	loop1.jb \
	loop2.jb \
	loop3.jb \
	random.jb

include ../Samples.mk

%.jb: %.s
	$(CL) -Wa -DJBFMT_DEVID=3 -t io2 -o $@ header.s $<
