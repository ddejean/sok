###############################################################################
# Simple Object Kernel project Makefile                                       #
# Copyright 2013 - Damien Dejean <dam.dejean@gmail.com>                       #
#                                                                             #
# Mostly inspirated from Android Build System.                                #
###############################################################################

# Define toolchain location
BUILD_ROOT:=build

# Define toolchain output
BUILD_OUTPUT:=out

# Import the toolchain
include $(BUILD_ROOT)/main.mk

# Import submakefile chain
include kernel/Sok.mk

