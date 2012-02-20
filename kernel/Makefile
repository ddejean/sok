########################################
# Simple Object Kernel build chain     #
# by Damien Dejean <djod4556@yahoo.fr> #
########################################

# Tools
SHELL := /bin/bash
CC    := gcc
CPP   := g++
AS    := gcc
LD    := ld

# Include util functions
include build/utils.mk

### Build parameters ###
# Recursively expanded variables to allow flag redefinition by kernel-configs.mk
FLAGS    = -m32 -Wall -Wextra -Werror -g -gstabs -pipe
CFLAGS   = $(FLAGS) -std=c99 -nostdinc -fno-stack-protector
CXXFLAGS = $(FLAGS) -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -fno-exceptions -fno-rtti -fno-stack-protector
LDFLAGS  = -melf_i386

# Build sources
DIRS      := . boot lib
C_FILES   := $(wildcard $(addsuffix /*.c, $(DIRS)))
CPP_FILES := $(wildcard $(addsuffix /*.cpp, $(DIRS)))
ASM_FILES := $(wildcard $(addsuffix /*.s, $(DIRS)))
FILES     := $(C_FILES) $(CPP_FILES) $(ASM_FILES)

# Includes
INCLUDES_DIR := . lib/
INCLUDES     := $(addprefix -I, $(INCLUDES_DIR))

# Make automatically search source files
vpath %.h $(DIRS)
vpath %.c $(DIRS)
vpath %.cpp $(DIRS)
vpath %.s $(DIRS)

# Output configuration
OUTPUT_BASE := out

# Include all kernel configs:
# defines different targets, flags and output directories
include build/kernel-configs.mk

### Create list of output files ###
# We want a list of obj files
OBJS := $(call targetize, $(FILES))
# The bootstrap file must be linked first
OBJS := $(call first-and-unique, crt0.o, $(OBJS))
# Set the output directory
OBJS := $(addprefix $(OUTPUT)/, $(OBJS))

### Build rules ###
$(KERNEL_CONFIGS): kernel.lds $(OBJS) 
	$(LD) $(LDFLAGS) -e entry -T $< -o $@ $(filter-out kernel.lds, $^)

$(OUTPUT)/%.o: %.s $(OUTPUT)
	$(AS) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OUTPUT)/%.o: %.cpp $(OUTPUT)
	$(CPP) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OUTPUT)/%.o: %.c $(OUTPUT)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OUTPUT):
	mkdir -p $(OUTPUT)

.PHONY: clean
clean:
	rm -f $(KERNEL_CONFIGS)
	rm -rf out/

