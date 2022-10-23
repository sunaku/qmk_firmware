# NOTE: Don't name the QMK Configurator JSON keymap file as "keymap.json"
# because `qmk compile` directly translates it into C and compiles it too,
# thereby completely bypassing this Makefile and our keymap header/footer!

TOPLEVEL=`git rev-parse --show-toplevel`
KEYBOARD=handwired/dactyl_manuform/5x6_5
KEYMAP=sunaku

all: flash

flash: build
	qmk flash -kb $(KEYBOARD) -km $(KEYMAP)

build: keymap.c config.h rules.mk
	test ! -e keymap.json # see comment at the top of this Makefile
	qmk compile -kb $(KEYBOARD) -km $(KEYMAP)

keymap.c: keymap_config.json keymap_header.c keymap_footer.c config.h
	qmk json2c -o $@ $<
	spot=$$( awk '/THIS FILE WAS GENERATED/ { print NR-1 }' $@ ) && \
	sed -e "$$spot r keymap_header.c" -e "$$ r keymap_footer.c" -i $@

clean:
	qmk clean

clobber: clean
	rm -fv keymap.c
	rm -fv $(TOPLEVEL)/$$( echo $(KEYBOARD) | tr / _ )_$(KEYMAP).hex

.PHONY: clean clobber build flash
