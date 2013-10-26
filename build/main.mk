###############################################################################
# Simple Object Kernel project Makefile                                       #
# Copyright 2013 - Damien Dejean <dam.dejean@gmail.com>                       #
#                                                                             #
# Main of the toolchain.                                                      #
###############################################################################


# this turns off the RCS / SCCS implicit rules of GNU Make
% : RCS/%,v
% : RCS/%
% : %,v
% : s.%
% : SCCS/s.%

# If a rule fails, delete $@.
.DELETE_ON_ERROR:

# Build toolchain root directory, mandatory before including main.mk
ifeq ($(BUILD_ROOT),)
    $(error BUILD_ROOT must be set before calling main.)
endif

# Default target to build the kernel. Must be defined first.
.PHONY: kernel
DEFAULT_GOAL := kernel
$(DEFAUT_GOAL):

# Absolute path of the present working direcotry.
# This overrides the shell variable $PWD, which does not necessarily points to
# the top of the source tree, for example when "make -C" is used in m/mm/mmm.
PWD := $(shell pwd)

# Standard tools
include $(BUILD_ROOT)/tools.mk

# Toolchain configuration
include $(BUILD_ROOT)/config.mk

# Toolchain functions definitions
include $(BUILD_ROOT)/definitions.mk

# Module management
include $(BUILD_ROOT)/module-database.mk

.PHONY: clean
clean:
	@echo "  RM    $(OUT_DIR)"
	$(hide) $(RM) -rf $(OUT_DIR)
