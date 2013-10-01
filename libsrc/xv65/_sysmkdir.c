// _sysmkdir.c
// Written by Emanuele Fornara

#include <xv65.h>

int _sysmkdir(const char* name, ...) {
	return xv65_mkdir(name);
}
