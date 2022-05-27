CC=g++
CC_FLAGS = -w -Wall
SOURCES=$(wildcard *.cc)
OBJECTS = $(SOURCES:.cc=.o)
PROGRAMM=programm

all:$(PROGRAMM)
$(PROGRAMM): $(OBJECTS)
		$(CC) $(OBJECTS) -o $(PROGRAMM)


%.o: %.c
	$(CC)  $(CC_FLAGS) -c $< 


clean:
	rm -f $(PROGRAMM) $(OBJECTS)


