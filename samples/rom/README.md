The relevant files of the runtime are:

* [crt0.s](../../libsrc/primo/crt0.s)
* [crt1.s](../../libsrc/primo/crt1.s)

The code of the linked startup (crt0) is just a JMP to the real startup
(startup1 in crt1, ideally stored in a known location in ROM). The
values that might change from program to program (e.g. the constructor
table) are stored in a struct in RODATA and passed to startup1 using AX.

To generate the ROM, I use a custom configuration (prmcrt.cfg), a list
of symbols to include/exclude (symbols.def), and a "typical" program
(sample.c).

The result is a pair of files: a ROM to load (prmcrt.rom) and an object
file (prmcrt.o) to link programs with.

See Makefile and mkrom.py for details of how the ROM is generated and
the [primo](../primo) sample directory for a few sample programs linking
with prmcrt.o.

## TODO

* Check for .o/.rom version mismatch.
* Check for data spillover from ROM.
* Partial JMP table.
* Are all the dependent symbols exported?
