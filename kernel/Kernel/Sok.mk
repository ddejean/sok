###############################################################################
# Simple Object Kernel project Makefile                                       #
# Copyright 2013 - Damien Dejean <dam.dejean@gmail.com>                       #
#                                                                             #
# Kernel build makefile                                                       #
###############################################################################

LOCAL_PATH := $(call my-dir)

# Build the kernel as an executable binary
include $(CLEAR_VARS)

LOCAL_MODULE := Kernel
LOCAL_MODULE_CLASS := KERNEL
LOCAL_SRC_FILES := $(call cpp-files-under,.)
LOCAL_DEPENDENCIES := kernel/Boot/kernel.lds
LOCAL_STATIC_LIBRARY := Boot Arch Memory Runtime CUtils
LOCAL_LDFLAGS := -T kernel/Boot/kernel.lds

# Be the main target of the build !
$(call add-dependency,$(DEFAULT_GOAL),$(LOCAL_MODULE))

include $(BUILD_EXECUTABLE)

