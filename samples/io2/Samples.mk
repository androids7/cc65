#
# Common Makefile for cc65 samples (io2)
#
# This Makefile requires GNU make
#

CL=../../../bin/cl65

%.jb: %.c
	$(CL) -t io2 -O2 -o $@ $<

%.jb: %.s
	$(CL) -t io2 -o $@ ../header.s $<

%.prg: %.c
	$(CL) -t c64 -O2 -o $@ $< c64jb.c

.PHONY:	clean
clean:
	$(RM) *~ ../header.o *.o *.jb *.prg
