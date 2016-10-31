#------------------------------------------------------------------------------
# File: 
# Author:
# Date:
# Purpose:
#		Compile matmult program used to benchmark matrix multiplication 
#		operation implemented with different algorithms
#------------------------------------------------------------------------------
HEADERS=matrix.h error.h time_macro.h
OBJ=alloc.o debug.o mult.o test.o error.o main.o
CFLAGS=-g -Wall
DEFINES=-DUSE_BLAS
LIBS=-lblas
TARGET=matmult
#DEBUG=-v

all: build

build: $(TARGET)

install:

clean:
	rm *.o
	rm $(TARGET)

$(TARGET): $(OBJ)
	gcc $(DEBUG) -o $@ $^ $(LIBS)

%.o: %.c
	gcc $(DEBUG) $(CFLAGS) $(DEFINES) -c $<
