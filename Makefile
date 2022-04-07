CC = gcc
CFLAGS = -Wall -ansi -pedantic

LANG = ru de kz
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
	rm -rvf $(EXECUTABLE) */LC_MESSAGES/$(EXECUTABLE).mo *.o *.out

.PHONY: translate
translate:
	for dir in $(LANG); do msgfmt $$dir/LC_MESSAGES/$(EXECUTABLE).pot -o $$dir/LC_MESSAGES/$(EXECUTABLE).mo; done

