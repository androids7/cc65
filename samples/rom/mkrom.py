#! /usr/bin/python2

# mkrom.py
# Written by Emanuele Fornara

import sys
import re

include = set()
exclude = set()

def usage():
	sys.exit('usage: mkrom.py import|export symbols.def')

def read_symbols(filename):
	f = open(filename, 'r')
	state = 0
	lineno = 1
	for l in f:
		line = l.strip('\r\n')
		lineno += 1
		if len(line) == 0:
			pass
		elif line.startswith('#'):
			pass
		elif line == 'include:':
			state = 1
		elif line == 'exclude:':
			state = 2
		else:
			m = re.search('^\s*(\w+)\s*$', line)
			if not m:
				sys.exit('invalid format at line ' + str(lineno))
			if state == 1:
				include.add(m.group(1))
			elif state == 2:
				exclude.add(m.group(1))
			else:
				sys.exit('unexpected symbol at line ' + str(lineno))
	f.close()

def dump_import():
	print('\t.export _driver')
	for i in include:
		print('\t.import ' + i)
	print('\t.segment "DRVCODE"')
	print('_driver:')
	for i in include:
		print('\t.word ' + i)

def dump_export():
	for l in sys.stdin:
		line = l.strip('\r\n')
		m = re.search('^al\s*00(\w+)\s*\.(\w+)*$', line)
		if not m:
			continue
		sym = m.group(2)
		addr = m.group(1)
		if sym.endswith('__'):
			continue
		if sym in exclude:
			continue
		if addr.startswith('00'):
			print('\t.exportzp ' + m.group(2) + ' = $' + m.group(1))
		elif addr.startswith('F'):
			print('\t.export ' + m.group(2) + ' = $' + m.group(1))

if (len(sys.argv) != 3):
	usage()
if (sys.argv[1] == 'import'):
	read_symbols(sys.argv[2])
	dump_import()
elif (sys.argv[1] == 'export'):
	read_symbols(sys.argv[2])
	dump_export()
else:
	usage()
