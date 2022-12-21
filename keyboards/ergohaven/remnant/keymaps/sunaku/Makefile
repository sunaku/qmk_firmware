# NOTE: Don't name the QMK Configurator JSON keymap file as "keymap.json"
# because `qmk compile` directly translates it into C and compiles it too,
# thereby completely bypassing this Makefile and our keymap header/footer!

TOPLEVEL=`git rev-parse --show-toplevel`
KEYBOARD=ergohaven/remnant
KEYMAP=sunaku

all: flash

flash: build
	qmk flash -kb $(KEYBOARD) -km $(KEYMAP)

build: keymap.c config.h rules.mk
	test ! -e keymap.json # see comment at the top of this Makefile
	qmk compile -kb $(KEYBOARD) -km $(KEYMAP) -j 0

keymap.c: keymap_config_converted.json keymap_header.c keymap_footer.c config.h
	qmk json2c -o $@ $<
	spot=$$( awk '/THIS FILE WAS GENERATED/ { print NR-1 }' $@ ) && \
	sed -e "$$spot r keymap_header.c" -e "$$ r keymap_footer.c" -i $@

keymap_config_converted.json: keymap_config.json
	sed 's|\("keyboard": *"\)[^"]*|\1$(KEYBOARD)|' $^ > $@

clean:
	qmk clean

clobber: clean
	rm -fv keymap.c keymap_config_converted.json
	rm -fv $(TOPLEVEL)/$$( echo $(KEYBOARD) | tr / _ )_$(KEYMAP).*

.PHONY: clean clobber build flash
