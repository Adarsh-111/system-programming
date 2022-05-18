BIN=bin/
OBJ=obj/
SRC=source/
INC=include/
CFLAG=-o
OBJFLAG=-c

all:    clean program 

program: functions
	g++ ${CFLAG} ${BIN}server ${SRC}server.cpp ${OBJ}func.o 
	g++ ${CFLAG} ${BIN}client ${SRC}client.cpp
	
functions:
	g++ ${OBJFLAG} ${CFLAG} ${OBJ}func.o ${SRC}func.cpp

clean:
	rm ${OBJ}func.o
	rm ${BIN}client
	rm ${BIN}server


