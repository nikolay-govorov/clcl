CFLAGS = -Wall -ansi -pedantic
LDFLAGS += -lm

LANG = ru de kz

INSTALL_DIR = /usr/bin
LOCALE_BASE_DIR = /usr/share/locale

CFLAGS += -DLOCALE_BASE_DIR='"$(LOCALE_BASE_DIR)"'

SRCMODULES = $(shell find 'src' -type f -name '*.c')
OBJMODULES = $(SRCMODULES:.c=.o)
TRANSLATES = $(patsubst %.pot,%.mo,$(wildcard */LC_MESSAGES/*.pot))
EXECUTABLE = clcl

all: release

release: CFLAGS += -O2 -Wextra -Werror
release: $(EXECUTABLE) translate

debug: CFLAGS += -DDEBUG -g -O0
debug: $(EXECUTABLE) translate

$(EXECUTABLE): $(OBJMODULES)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -rvf $(EXECUTABLE) $(TRANSLATES) $(OBJMODULES) {**/,}*.out

.PHONY: translate
translate: $(TRANSLATES)

%.mo: %.pot
	msgfmt $< -o $@

.PHONY: install
install: build
	install $(EXECUTABLE) $(INSTALL_DIR)
	for code in $(LANG); do \
		mkdir -p $(LOCALE_BASE_DIR)/$$code/LC_MESSAGES/; \
		cp -r $$code/LC_MESSAGES/*.mo $(LOCALE_BASE_DIR)/$$code/LC_MESSAGES/; \
	done

.PHONY: uninstall
uninstall:
	rm -rvf $(INSTALL_DIR)/$(EXECUTABLE)
	rm -rvf $(LOCALE_BASE_DIR)/*/LC_MESSAGES/$(EXECUTABLE).mo

