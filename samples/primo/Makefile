#
# Makefile for cc65 samples (primo)
#
# This Makefile requires GNU make
#

CL=../../bin/cl65
HDR=../../libsrc/primo/header

%.jb: %.c
	$(CL) -t primo -O2 -o $@ $<

%.jb: %.s
	$(CL) -t primo -o $@ $(HDR).s $<

%.txt: %.jb
	od -A d -t u1 $<

.PHONY:	all
all: \
	vm.jb \
	cblink.jb \
	prmcrt.rom

prmcrt.rom:
	$(CL) -t primo -C prmcrt.cfg -Ln prmcrt.map -O2 -o prmcrt.rom import.s
	$(CL) -t primo -c export.s
	$(CL) -t primo -O2 -o testcrt.jb cblink.c export.o

.PHONY:	clean
clean:
	$(RM) *~ $(HDR).o *.o *.jb *.rom *.map
