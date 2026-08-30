RISCV_PREFIX ?= riscv64-unknown-elf-
CC      := $(RISCV_PREFIX)gcc
OBJCOPY := $(RISCV_PREFIX)objcopy
OBJDUMP := $(RISCV_PREFIX)objdump
CFLAGS  := -march=rv32i -mabi=ilp32 -Os -ffreestanding -nostdlib -nostartfiles \
           -Wall -Wextra -Wl,--no-relax -Wl,-T,link.ld
BUILD   := build

.PHONY: all clean
all: $(BUILD)/firmware.hex $(BUILD)/firmware.dump

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)/firmware.elf: start.S main.c link.ld | $(BUILD)
	$(CC) $(CFLAGS) start.S main.c -o $@

$(BUILD)/firmware.bin: $(BUILD)/firmware.elf
	$(OBJCOPY) -O binary $< $@

$(BUILD)/firmware.hex: $(BUILD)/firmware.bin
	python3 ../scripts/bin_to_word_hex.py $< $@

$(BUILD)/firmware.dump: $(BUILD)/firmware.elf
	$(OBJDUMP) -d -S $< > $@

clean:
	rm -rf $(BUILD)
