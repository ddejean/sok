###############################################################################
# Simple Object Kernel project Makefile                                       #
# Copyright 2013 - Damien Dejean <dam.dejean@gmail.com>                       #
#                                                                             #
# C++ runtime build.                                                          #
###############################################################################

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Runtime
LOCAL_MODULE_CLASS := KERNEL
LOCAL_SRC_FILES := $(call all-cpp-files-under,.)

include $(BUILD_STATIC_LIBRARY)

