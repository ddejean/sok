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
AR 	  := ar
MKDIR := mkdir

# Include util functions
include build/utils.mk

### Build parameters ###
# Recursively expanded variables to allow flag redefinition by kernel-configs.mk
FLAGS    = -m32 -Wall -Wextra -Werror -g -gstabs -pipe
CFLAGS   = $(FLAGS) -std=c99 -nostdinc -fno-stack-protector
CXXFLAGS = $(FLAGS) -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -fno-exceptions -fno-rtti -fno-stack-protector
LDFLAGS  = -melf_i386

# Output configuration
OUTPUT_BASE := out

# Include all kernel configs:
# defines different targets, flags and output directories
include build/kernel-configs.mk

# Includes
INCLUDES := -I. -ICUtils/

# Main kernel files
MAIN_FILES 	:= $(call all-compilables-under, .)
MAIN_OBJS 	:= $(addprefix $(OUTPUT)/, $(call objetize-compilables, $(MAIN_FILES)))

# Boot files (need special link)
BOOT_FILES 	:= $(call first-and-unique, boot/crt0.s, $(call all-compilables-under, boot))
BOOT_OBJS 	:= $(addprefix $(OUTPUT)/, $(call objetize-compilables, $(BOOT_FILES)))

# Library builds
LIBRARY_NAMES 	:= CUtils Memory
LIBRARY_FILES	:= $(call dirs-to-libs, $(LIBRARY_NAMES))
LIBRARIES_OUT 	:= $(addprefix $(OUTPUT)/, $(LIBRARY_FILES))
LDFLAGS			+= -L$(OUTPUT) $(call generate-libs-flags, $(LIBRARY_NAMES))

### Build rules ###
$(KERNEL_CONFIGS): boot/kernel.lds $(BOOT_OBJS) $(MAIN_OBJS) $(LIBRARIES_OUT)
	$(LD) $(LDFLAGS) -e entry -T $< -o $@ $(filter-out $<, $^)

# Archive creation
include build/library.mk
$(foreach lib, $(LIBRARY_NAMES), $(eval $(call LIBRARY_BUILD,$(lib))))

# Compilation rules
$(OUTPUT)/%.o: %.s $(OUTPUT)
	$(AS) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OUTPUT)/%.o: %.cpp $(OUTPUT)
	$(CPP) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OUTPUT)/%.o: %.c $(OUTPUT)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OUTPUT):
	mkdir -p $@

# Boot build
$(BOOT_OBJS): $(OUTPUT)/boot
$(OUTPUT)/boot:
	mkdir -p $@
	
.PHONY: clean
clean:
	rm -f $(KERNEL_CONFIGS)
	rm -rf out/

