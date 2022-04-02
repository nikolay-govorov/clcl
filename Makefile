CC = gcc
CFLAGS = -Wall -ansi -pedantic

SRCMODULES = log.c
OBJMODULES = $(SRCMODULES:.c=.o)
EXECUTABLE = calculator

$(EXECUTABLE): $(OBJMODULES) main.c
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clear
clear:
	rm -vf $(EXECUTABLE) *.o *.out

