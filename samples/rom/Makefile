#
# Sample Makefile to generate a ROMable runtime
#
# This Makefile requires GNU make
#

CL=../../bin/cl65

.PHONY:	all
all: \
	prmcrt.rom

prmcrt.rom: symbols.def
	./mkrom.py import symbols.def >import.s
	$(CL) -t primo -C prmcrt.cfg -Ln prmcrt.map -O2 -o prmcrt.rom import.s
	./mkrom.py export symbols.def <prmcrt.map >export.s
	$(CL) -t primo -o prmcrt.o -c export.s

.PHONY:	clean
clean:
	$(RM) *~ *.o *.rom *.map import.s export.s
