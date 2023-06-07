# This file makes Gattaca.
# Author: R. Coleman
# Created: 4 Feb 2019
CC = nvcc
CFLAGS=-c
LDFLAGS=
DEPS=Card.h GA.h Hand.h Helpers.h Kpax.h Player.h Population.h Strategy.h Utils.h
#CPP=GA.cpp Helpers.cpp Main.cpp Population.cpp Test03.cpp
#CU=Kpax.cu
OBJS=GA.obj Helpers.obj Main.obj Population.obj Test01.obj Test02.obj Test03.obj Test04.obj Test10.obj
CUOBJS=Kpax.obj
EXECUTABLE=Gattaca.exe 

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) $(CUOBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(CUOBJS) -o $@

%.obj: %.cpp $(DEPS)
	$(CC) $(CFLAGS) $< $@

%.obj: %.cu $(DEPS)
	$(CC) $(CFLAGS) $< $@

clean:
	erase *.obj Gattaca.exe
