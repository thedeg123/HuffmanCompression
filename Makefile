all: encode decode code.o
encode: encode.c encode.h code.o
	gcc encode.c code.o -o encode -lm
decode: decode.c decode.h code.o
	gcc decode.c code.o -o decode -lm
code.o: code.c code.h
	gcc code.c code.h -c
clean:
	rm encode decode code.h.gch code.o
