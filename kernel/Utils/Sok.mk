###############################################################################
# Simple Object Kernel project Makefile                                       #
# Copyright 2013 - Damien Dejean <dam.dejean@gmail.com>                       #
#                                                                             #
# A C++ standard library build.                                               #
###############################################################################

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Utils
LOCAL_MODULE_CLASS := KERNEL
LOCAL_TESTS_FILES := $(call h-files-under,tests) \
    $(call cpp-files-under,tests)

include $(BUILD_STATIC_LIBRARY)
