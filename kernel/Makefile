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
MAIN_FILES 	:= $(wildcard *.c) $(wildcard *.cpp) $(wildcard *.s)
MAIN_OBJS 	:= $(addprefix $(OUTPUT)/, $(call objetize-compilables, $(MAIN_FILES)))
MAIN_DEPS	:= $(addprefix $(OUTPUT)/, $(call generate-dependencies, $(MAIN_FILES)))

# Boot files (need special link)
BOOT_FILES 	:= $(call first-and-unique, boot/crt0.s, $(call all-compilables-under, boot))
BOOT_OBJS 	:= $(addprefix $(OUTPUT)/, $(call objetize-compilables, $(BOOT_FILES)))
BOOT_DEPS	:= $(addprefix $(OUTPUT)/, $(call generate-dependencies, $(BOOT_FILES)))

# Library builds
LIBRARY_NAMES 	:= CUtils Memory
LIBRARY_FILES	:= $(call dirs-to-libs, $(LIBRARY_NAMES))
LIBRARIES_OUT 	:= $(addprefix $(OUTPUT)/, $(LIBRARY_FILES))
LDFLAGS			+= -L$(OUTPUT) $(call generate-libs-flags, $(LIBRARY_NAMES))

### Main link ###
$(KERNEL_CONFIGS): boot/kernel.lds $(BOOT_OBJS) $(MAIN_OBJS) $(LIBRARIES_OUT)
	@echo $(MAIN_DEPS) $(BOOT_DEPS)
	$(LD) $(LDFLAGS) -e entry -T $< -o $@ $(filter-out $<, $^)

### Handle source file dependencies to header files ###
$(OUTPUT)/%.d: %.cpp
	@$(MKDIR) -p $(@D)
	@echo -n "$(@D)/" > $@
	$(CC) -MM $< $(INCLUDES) >> $@

$(OUTPUT)/%.d: %.c
	@$(MKDIR) -p $(@D)
	@echo -n "$(@D)/" > $@
	$(CC) -MM $< $(INCLUDES) > $@

$(OUTPUT)/%.d: %.s
	@$(MKDIR) -p $(@D)
	@echo -n "$(@D)/" > $@
	$(CC) -MM $< $(INCLUDES) > $@

ifneq "$(OUTPUT)" ""
-include $(MAIN_DEPS)
-include $(BOOT_DEPS)
endif

### Archive creation ###
include build/library.mk
$(foreach lib, $(LIBRARY_NAMES), $(eval $(call LIBRARY_BUILD,$(lib))))

### Generic compilation rules ###
$(OUTPUT)/%.o: %.s
	@$(MKDIR) -p $(@D)
	$(AS) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OUTPUT)/%.o: %.cpp
	@$(MKDIR) -p $(@D)
	$(CPP) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OUTPUT)/%.o: %.c
	@$(MKDIR) -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(KERNEL_CONFIGS)
	rm -rf out/

