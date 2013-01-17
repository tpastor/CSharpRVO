CC = g++
DEBUG = -g
OMP = -fopenmp
CFLAGS = -Wall -c $(DEBUG) $(OMP) -I../include/
LFLAGS = -Wall $(DEBUG) -L../lib -lRVO -lgomp

all : Sphere

Sphere : Sphere.o
	$(CC) $(LFLAGS) Sphere.o -o Sphere
	rsync Sphere ../bin/
	
Sphere.o : Sphere.cpp
	$(CC) $(CFLAGS) Sphere.cpp

clean:
	rm -f *.o Sphere ../bin/Sphere
