########################################
# Simple Object Kernel build chain     #
# by Damien Dejean <djod4556@yahoo.fr> #
########################################

# Tools
SHELL := /bin/bash
CC := gcc -m32
AS := gcc -m32
LD := ld -melf_i386

# Build parameters
CFLAGS := -Wall -Wextra -Werror -g -gstabs -pipe -std=c99 -nostdinc -fno-stack-protector
LDFLAGS := 

# Build sources
DIRS      := . boot
C_FILES   := $(wildcard $(addsuffix /*.c, $(DIRS)))
CPP_FILES := $(wildcard $(addsuffix /*.cpp, $(DIRS)))
ASM_FILES := $(wildcard $(addsuffix /*.s, $(DIRS)))
FILES     := $(C_FILES) $(CPP_FILES) $(ASM_FILES)

# Make automatically search source files
vpath %.h $(DIRS)
vpath %.c $(DIRS)
vpath %.cpp $(DIRS)
vpath %.s $(DIRS)

# Build products
OUTPUT := build
OBJS   := $(strip crt0.o $(filter-out crt0.o,$(notdir $(patsubst %.s,%.o,$(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(FILES)))))))
OBJS   := $(addprefix $(OUTPUT)/, $(OBJS))

# Build rules
kernel.bin: kernel.lds $(OBJS)
	$(LD) -e entry -T $< -o $@ $(filter-out kernel.lds, $^)

$(OUTPUT)/%.o: %.s $(OUTPUT)
	$(AS) -c $< -o $@

$(OUTPUT):
	mkdir -p $(OUTPUT)

.PHONY: clean
clean:
	rm -f kernel.bin
	rm -rf build/

