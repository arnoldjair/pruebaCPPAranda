CPP = clang++ -std=c++11
CC = clang
NAME = programa
OBJS = log.o main.o zlib.o sqlite3.o db.o
LIBS = lib
STATIC = lib/libZipper-static.a lib/libz.a lib/libboost_filesystem.a lib/libboost_system.a
FLAGS = -std=c++11 

all: programa

programa: ${OBJS}
	${CPP} -I ${LIBS} -L ${LIBS} ${OBJS} -lpthread -ldl -o programa ${STATIC}


main.o: main.cpp
	${CPP} -I ${LIBS} -c main.cpp

log.o: log.cpp
	${CPP} -c log.cpp

zlib.o: zlib.cpp
	${CPP}	-c zlib.cpp

sqlite3.o: sqlite3.c
	${CC} -c sqlite3.c

db.o: db.cpp
	${CPP} -c db.cpp

clean:
	rm *o programa



