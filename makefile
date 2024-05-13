OBJS	= catalog.o run_catalog.o
SOURCE	= catalog.cpp run_catalog.cpp
HEADER	= catalog.h
OUT	= a.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

catalog.o: catalog.cpp
	$(CC) $(FLAGS) catalog.cpp 

run_catalog.o: run_catalog.cpp
	$(CC) $(FLAGS) run_catalog.cpp 


clean:
	rm -f $(OBJS) $(OUT)