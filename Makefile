CC = gcc
CFLAG = -ggdb
LIBS = -pthread
SRCDIR = ./src/

exibitstream: clean
	${CC} ${CFLAG} ${LIBS} -o $@ ${SRCDIR}ExibitStream.c
clean:
	rm -f ./exibitstream
