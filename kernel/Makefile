########################################
# Simple Object Kernel build chain     #
# by Damien Dejean <djod4556@yahoo.fr> #
########################################

SHELL  := /bin/bash

# Raw tools
CC     		:= gcc
CPP    		:= g++
AS     		:= gcc
LD     		:= ld
AR	   		:= ar
MKDIR  		:= mkdir
RM	   		:= rm
TESTGEN 	:= CxxTest/cxxtestgen.pl

# Displayed tools
QCC    		= @echo -e "\tCC\t " $@; $(CC)
QCPP   		= @echo -e "\tCPP\t " $@; $(CPP)
QDEPS  		= @echo -e "\tDEPS\t " $@; $(CC) -MM
QAS    		= @echo -e "\tAS\t " $@; $(AS)
QLD    		= @echo -e "\tLD\t " $@; $(LD)
QAR 	  	= @echo -e "\tAR\t " $@; $(AR)
QTESTGEN 	= @echo -e "\tTESTGEN\t " $@; $(TESTGEN)
SMART_MKDIR = @test -d $(@D) || { echo -e "\tMKDIR\t " $(@D); $(MKDIR) -p $(@D); }

# Include util functions
include build/utils.mk

### Build parameters ###
# Recursively expanded variables to allow flag redefinition by kernel-configs.mk
FLAGS    := -m32 -Wall -Wextra -Werror -g -gstabs -pipe
CFLAGS   := $(FLAGS) -std=c99
CXXFLAGS := $(FLAGS)
LDFLAGS  := -melf_i386

# Kernel compilation and link flags
KERNEL_CFLAGS = $(CFLAGS) -nostdinc -fno-stack-protector
KERNEL_CXXFLAGS = $(CXXFLAGS) -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -fno-exceptions -fno-rtti -fno-stack-protector
KERNEL_LDFLAGS = $(LDFLAGS)

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
KERNEL_LDFLAGS	+= -L$(OUTPUT) $(call generate-libs-flags, $(LIBRARY_NAMES))

### Main link ###
$(KERNEL_CONFIGS): boot/kernel.lds $(BOOT_OBJS) $(MAIN_OBJS) $(LIBRARY_FILES)
	$(QLD) $(KERNEL_LDFLAGS) -e entry -T $< -o $@ $(BOOT_OBJS) $(MAIN_OBJS) $(LIBRARIES_OUT)

### Handle source file dependencies to header files ###
$(OUTPUT)/%.d: %.cpp
	$(SMART_MKDIR)
	@echo -n "$(@D)/" > $@
	$(QDEPS) $< $(INCLUDES) >> $@

$(OUTPUT)/%.d: %.c
	$(SMART_MKDIR)
	@echo -n "$(@D)/" > $@
	$(QDEPS) $< $(INCLUDES) > $@

$(OUTPUT)/%.d: %.s
	$(SMART_MKDIR)
	@echo -n "$(@D)/" > $@
	$(QDEPS) $< $(INCLUDES) > $@

ifneq "$(OUTPUT)" ""
-include $(MAIN_DEPS)
-include $(BOOT_DEPS)
endif

### Archive creation ###
include build/library.mk
$(foreach lib, $(LIBRARY_NAMES), $(eval $(call LIBRARY_BUILD,$(lib))))

### Generic compilation rules ###
$(OUTPUT)/%.o: %.s
	$(SMART_MKDIR)
	$(QAS) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OUTPUT)/%.o: %.cpp
	$(SMART_MKDIR)
	$(QCPP) $(KERNEL_CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OUTPUT)/%.o: %.c
	$(SMART_MKDIR)
	$(QCC) $(KERNEL_CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY: clean
clean:
	@echo -e "\tRM\t $(KERNEL_CONFIGS)"; $(RM) -f $(KERNEL_CONFIGS)
	@echo -e "\tRM\t out/"; $(RM) -rf out/

