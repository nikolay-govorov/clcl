CC = gcc
CFLAGS = -Wall -ansi -pedantic -lm

LANG = ru de kz

INSTALL_DIR = /usr/bin
LOCALE_BASE_DIR = /usr/share/locale

CFLAGS += -DLOCALE_BASE_DIR=$(LOCALE_BASE_DIR)

# all .c files (by headers) except main.c
SRCMODULES = $(patsubst %.h,%.c,$(wildcard *.h **/*.h))
OBJMODULES = $(SRCMODULES:.c=.o)
EXECUTABLE = clcl

build: $(EXECUTABLE) translate

$(EXECUTABLE): $(OBJMODULES) main.c
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rvf $(EXECUTABLE) */LC_MESSAGES/$(EXECUTABLE).mo **/*.o **/*.out

.PHONY: translate
translate:
	for dir in $(LANG); do msgfmt $$dir/LC_MESSAGES/$(EXECUTABLE).pot -o $$dir/LC_MESSAGES/$(EXECUTABLE).mo; done

.PHONY: install
install:
	install $(EXECUTABLE) /usr/bin
	for code in $(LANG); do \
		mkdir -p $(LOCALE_BASE_DIR)/$$code/LC_MESSAGES/; \
		cp -r $$code/LC_MESSAGES/*.mo $(LOCALE_BASE_DIR)/$$code/LC_MESSAGES/; \
	done

