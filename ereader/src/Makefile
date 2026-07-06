SHELL :=/bin/bash
E_READER_DEV = /home/matt/dev/e-reader-dev
E_READER_DEV_BIN = $(E_READER_DEV)/bin
LIB = ./clib
# PATH = /bin:$(DEVKITARM)/bin:$(E_READER_DEV_BIN):/opt/devkitpro/tools/bin

PATH_LIB_GCC = $DEVKITARM/arm-none-eabi/lib/thumb

EREADER_MGBA_SAVESTATE=~/roms/gba/ereaderUSA_savestate
# the ereader rom
EREADER_MGBA_ROM=~/roms/gba/ereaderUSA.gba
EREADER_MGBA_ROM_JPN=~/roms/gba/ereaderJPN.zip
EREADER_MGBA_ROM_SAV=~/roms/gba/ereaderUSA.sav
EREADER_MGBA_ROM_SAV_JPN=~/roms/gba/ereaderJPN.sav
MGBA=/usr/bin/mgba-qt

OPTIMIZATION=-Os

# name of application
NAME = "Eridin ER"
TARGET = main

SRC_FILES := $(wildcard *.c)
OBJ_FILES := $(patsubst %.c,build/%.o,$(SRC_FILES))

# assemble and link
PREFIX  := arm-none-eabi-
GCC      = $(PREFIX)gcc
AS       = $(PREFIX)as
LD       = $(PREFIX)ld
OBJCOPY  = $(PREFIX)objcopy

# If running on Linux (and presumably MacOS), this is used to run the E-Reader tools through wine
# wine.sh is just a simple script that will take an installed wine command and allow it to run against
# exe's in the bin directory
WINE=../scripts/wine.sh
BIN=../bin
RAW2BMP=$(BIN)/raw2bmp
NEDCMAKE=$(WINE) nedcmake.exe
NEFLMAKE=$(BIN)/neflmake
NEVPK=$(WINE) nevpk.exe

REGION = 1
TARGET = main

loader: $(TARGET).loader
sav : $(TARGET).sav
vpk: build/$(TARGET).vpk

# E-Reader Dot Code Strip

raws : build/$(TARGET).vpk
	$(NEDCMAKE) -i $< -o build/$(TARGET) -type 2 -raw -fill 0 -save 1 -music 1 -region $(REGION) -name $(NAME)

$(TARGET).sav : build/$(TARGET).vpk
	$(NEFLMAKE) -i $< -o "$@" -type 2 -name $(NAME)

$(TARGET).loader: $(TARGET).sav
	@echo "Generating $(TARGET).loader from $(TARGET).sav..."
	@size_hex=$$(dd if=$(TARGET).sav bs=1 skip=$$((0x1002C)) count=4 2>/dev/null | od -An -tx1 | tr -s ' ') && \
	set -- $$size_hex && \
	size=$$(( 0x$$1 + (0x$$2 << 8) + (0x$$3 << 16) + (0x$$4 << 24) )); \
	header_extra=$$((0x002C + 4 + 32)) ; \
	length=$$(( header_extra + size )); \
	total=$$(( (length + 31) & ~31 )); \
	dd if=$(TARGET).sav bs=1 skip=$$((0x10000)) count=$$total of=$(TARGET).loader 2>/dev/null

# E-Reader Save Data

build/$(TARGET).vpk : build/$(TARGET).bin 
	$(NEVPK) -i "$<" -o "$@" -c -level 2

# GBA Binary

build/$(TARGET).bin : build/$(TARGET).elf
	$(OBJCOPY) -O binary "$<" "$@"

build/$(TARGET).elf : build/crt0.o $(OBJ_FILES) $(LIB)/ereader.ld
	$(LD) build/crt0.o $(OBJ_FILES) -L $(PATH_LIB_GCC) -T $(LIB)/ereader.ld $(OPTIMIZATION) -o "$@"

build/%.o : %.c
	$(GCC) -I $(LIB) $(CFLAGS) -mthumb -c $(OPTIMIZATION) -o "$@" "$<"

build/crt0.o : $(LIB)/crt0.s
	$(AS) -o "$@" "$<"

list :
	echo $(OBJ_FILES)

clean :
	rm -f build/*.o
	rm -f build/*.bin
	rm -f build/*.elf
	rm -f build/*.raw
	rm -f build/*.vpk
	rm -f *.bmp *.sav *.loader

.PHONY: setup-target
setup-target:
	@: #do nothing, just ensure TARGET is setup before sav/bmp are built

runsav: $(TARGET).sav
	rm -f $(EREADER_MGBA_ROM_SAV);
	cp $(TARGET).sav $(EREADER_MGBA_ROM_SAV);
	$(MGBA) $(EREADER_MGBA_ROM)
