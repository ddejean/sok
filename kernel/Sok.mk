###############################################################################
# Simple Object Kernel project Makefile                                       #
# Copyright 2013 - Damien Dejean <dam.dejean@gmail.com>                       #
#                                                                             #
# Build Kernel library modules.                                               #
###############################################################################

# Cannot be called LOCAL_PATH as overrided by submakefiles
MY_DIR := $(call my-dir)

include $(MY_DIR)/CUtils/Sok.mk
include $(MY_DIR)/Arch/Sok.mk
include $(MY_DIR)/Boot/Sok.mk
include $(MY_DIR)/Utils/Sok.mk
include $(MY_DIR)/Runtime/Sok.mk
include $(MY_DIR)/Memory/Sok.mk
include $(MY_DIR)/Kernel/Sok.mk
