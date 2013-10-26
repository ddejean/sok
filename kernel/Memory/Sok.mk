###############################################################################
# Simple Object Kernel project Makefile                                       #
# Copyright 2013 - Damien Dejean <dam.dejean@gmail.com>                       #
#                                                                             #
# Memory management library build.                                            #
###############################################################################

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Memory
LOCAL_MODULE_CLASS := KERNEL
LOCAL_SRC_FILES := $(call cpp-files-under,.)

LOCAL_TESTS_FILES := $(call cpp-files-under,tests) \
    $(call c-files-under,tests) \
    $(call asm-files-under,tests) \
    $(call h-files-under,tests)

include $(BUILD_STATIC_LIBRARY)

