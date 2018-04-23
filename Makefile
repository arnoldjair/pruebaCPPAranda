CPP = clang++ -std=c++11
NAME = programa
OBJS = log.o main.o zlib.o
LIBS = lib
STATIC = lib/libZipper-static.a lib/libz.a lib/libboost_filesystem.a lib/libboost_system.a
FLAGS = -std=c++11 

all: programa

programa: ${OBJS}
	${CPP} -I ${LIBS} -L ${LIBS} ${OBJS} -o programa ${STATIC}


main.o: main.cpp
	${CPP} -I ${LIBS} -c main.cpp

log.o: log.cpp
	${CPP} -c log.cpp

zlib.o: zlib.cpp
	${CPP}	-c zlib.cpp

clean:
	rm *o programa



