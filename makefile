CC = gcc
CPP = g++
MAIN_SRC = main.cpp
SRC = motor.cpp
INC = motor.h
EXE = rovdrive
CFLAGS = -I/usr/include/ctsocket -lctsocket

build: $(SRC) $(MAIN_SRC)
	$(CPP) -o $(EXE) $(SRC) $(INC) $(MAIN_SRC) $(CFLAGS)
	
clean:
	rm -f *.o *.h.gch $(EXE)
	
rebuild: clean build

