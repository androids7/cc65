#
# Makefile for cc65 samples (primo)
#
# This Makefile requires GNU make
#

CL=../../bin/cl65
HDR=../../libsrc/primo/header
ROM=

# comment out to avoid using rom
ROM += ../rom/prmcrt.o

%.jb: %.c
	$(CL) -t primo -O2 -o $@ $< $(ROM)

%.jb: %.s
	$(CL) -t primo -o $@ $(HDR).s $<

%.txt: %.jb
	od -A d -t u1 $<

.PHONY:	all
all: \
	vm.jb \
	cblink.jb

.PHONY:	clean
clean:
	$(RM) *~ $(HDR).o *.o *.jb
