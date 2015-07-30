SRC_FILES = ../common/y86.cpp \
						../scanner/scanner.cpp \
						./assembler.cpp

y86_64:
	g++ -std=c++11 $(SRC_FILES) -D y86_64 -D SHOW_ADDRESS -o assembler64

y86_32:
	g++ -std=c++11 $(SRC_FILES) -D y86_32 -D SHOW_ADDRESS -o assembler32
