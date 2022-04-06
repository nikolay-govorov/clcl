CC = gcc
CFLAGS = -Wall -ansi -pedantic

SRCMODULES = log.c calc.c locale.c
OBJMODULES = $(SRCMODULES:.c=.o)
EXECUTABLE = calculator

build: $(EXECUTABLE) translate

$(EXECUTABLE): $(OBJMODULES) main.c
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clear
clear:
	rm -rvf $(EXECUTABLE) ru/ *.o *.out

.PHONY: translate
translate:
	mkdir -p ru/LC_MESSAGES/
	msgfmt translate/ru.pot -o ru/LC_MESSAGES/$(EXECUTABLE).mo

