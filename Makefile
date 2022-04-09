CC = gcc
CFLAGS = -Wall -ansi -pedantic -lm

LANG = ru de kz

# all .c files (by headers) except main.c
SRCMODULES = $(patsubst %.h,%.c,$(wildcard *.h **/*.h))
OBJMODULES = $(SRCMODULES:.c=.o)
EXECUTABLE = calculator

build: $(EXECUTABLE) translate

$(EXECUTABLE): $(OBJMODULES) main.c
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rvf $(EXECUTABLE) */LC_MESSAGES/$(EXECUTABLE).mo *.o *.out

.PHONY: translate
translate:
	for dir in $(LANG); do msgfmt $$dir/LC_MESSAGES/$(EXECUTABLE).pot -o $$dir/LC_MESSAGES/$(EXECUTABLE).mo; done

