SHELL = /bin/bash

CXX = /usr/bin/g++

ALL_CPPFLAGS = -O3

LIBS =

OBJS1 = testSort.o 

EXEC1 = testSort

OBJS1 = draw.o 

EXEC1 = draw


all: $(EXEC1)

$(EXE1):
	$CXX -c $(OBJS1) 
	$CXX -O3 $(OBJS1) -o $(EXEC1) $(LIBS)
$(EXE2):
	$CXX -c $(OBJS2) 
	$CXX -O3 $(OBJS2) -o $(EXEC2) $(LIBS)

clean:      
	rm -f $(OBJS1) $(EXEC1)
	rm -f $(OBJS2) $(EXEC2)
#	rm -f .data*