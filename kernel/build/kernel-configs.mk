##################################################################
# Simple Object Kernel project Makefile                          #
# by Damien Dejean <djod4556@yahoo.fr>                           #
# Provides definitions of different kernel build configurations. #
##################################################################

# Default kernel configuration, no specific debug options
KERNEL_DEFAULT := kernel-default.bin
$(KERNEL_DEFAULT): KERNEL_CFLAGS += -DVGA_DEBUG
$(KERNEL_DEFAULT): KERNEL_CXXFLAGS += -DVGA_DEBUG
ifeq ($(MAKECMDGOALS),$(KERNEL_DEFAULT))
	OUTPUT := $(OUTPUT_BASE)/default
endif

# Kernel with qemu debug console defined as default output in stage1
KERNEL_QEMU_DEBUG :=  kernel-qemu-debug.bin
$(KERNEL_QEMU_DEBUG): KERNEL_CFLAGS += -DQEMU_DEBUG
$(KERNEL_QEMU_DEBUG): KERNEL_CXXFLAGS += -DQEMU_DEBUG
ifeq ($(MAKECMDGOALS),$(KERNEL_QEMU_DEBUG))
	OUTPUT := $(OUTPUT_BASE)/qemu-debug
endif

# Summary of all kernel configs
KERNEL_CONFIGS := $(KERNEL_DEFAULT) $(KERNEL_QEMU_DEBUG)

