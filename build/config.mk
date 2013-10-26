###############################################################################
# Simple Object Kernel project Makefile                                       #
# Copyright 2013 - Damien Dejean <dam.dejean@gmail.com>                       #
#                                                                             #
# Defines configuration for the platform.                                     #
###############################################################################

# Defines a default shell
SHELL := /bin/bash

# Silent output
hide ?= @

# Defines the output build directory
ifeq (,$(BUILD_OUTPUT))
    $(error BUILD_OUTPUT must be set before calling config.mk)
endif
OUT_DIR := $(BUILD_OUTPUT)

# Pathes to build modules
CLEAR_VARS := $(BUILD_ROOT)/clear-vars.mk
BUILD_STATIC_LIBRARY := $(BUILD_ROOT)/build-static-library.mk
BUILD_TEST := $(BUILD_ROOT)/build-tests.mk
BUILD_EXECUTABLE := $(BUILD_ROOT)/build-executable.mk

# Default build flags
DEFAULT_FLAGS := -m32 -Wall -Wextra -Werror -g -gstabs -pipe
DEFAULT_CFLAGS := $(DEFAULT_FLAGS) -std=c99
DEFAULT_CPPFLAGS := $(DEFAULT_FLAGS)
DEFAULT_ASFLAGS := $(DEFAULT_FLAGS)
DEFAULT_LDFLAGS := -melf_i386
DEFAULT_ARFLAGS := rcs

# Kernel build flags
KERNEL_INCLUDES := kernel/ kernel/CUtils/
KERNEL_CFLAGS := -nostdinc -fno-stack-protector
KERNEL_CPPFLAGS := -nostdinc -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -fno-exceptions -fno-rtti -fno-stack-protector
KERNEL_ASFLAGS := -nostdinc
KERNEL_LDFLAGS :=
KERNEL_ARFLAGS :=
