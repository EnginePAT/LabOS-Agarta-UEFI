#
# Tools
#
CC=x86_64-elf-gcc
LD=x86_64-elf-ld
ASM=nasm

#
# Compiler Flags
#
CFLAGS = -ffreestanding -fno-stack-protector -fno-builtin -nostdlib -Wall -Wextra -O2 -mcmodel=kernel -ILimine/limine-protocol/include/ -Iinclude/
LDFLAGS = -T src/linker.ld

#
# Directories
#
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

#
# Files
#
KERNEL = $(BUILD_DIR)/kernel.elf
SRCFILES := $(shell find $(SRC_DIR) -name "*.c")
ASMFILES := $(shell find $(SRC_DIR) -name "*.asm")
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCFILES))
OBJS += $(patsubst $(SRC_DIR)/%.asm, $(OBJ_DIR)/%.asm.o, $(ASMFILES))

all: $(KERNEL) install

#
# Compile each .c file individually
#
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.asm.o: $(SRC_DIR)/%.asm
	@mkdir -p $(dir $@)
	$(ASM) -f elf64 $< -o $@

#
# Link
#
$(KERNEL): $(OBJS)
	@mkdir -p $(dir $@)
	$(LD) $(LDFLAGS) $(OBJS) -o $(KERNEL)

#
# clangd
#
compile_commands.json: clean
	bear -- make

#
# Clean
#
clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)

#
# Install
#
install: $(KERNEL)
	./scripts/mount-disk.sh
	cp $(KERNEL) /Volumes/NO\ NAME/boot/kernel.elf
	cp scripts/LabOS/limine.conf /Volumes/NO\ NAME/boot/limine/
	hdiutil detach /Volumes/NO\ NAME

#
# Run
#
run:
	./scripts/run.sh
