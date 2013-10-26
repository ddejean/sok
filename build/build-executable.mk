###############################################################################
# Simple Object Kernel project Makefile                                       #
# Copyright 2013 - Damien Dejean <dam.dejean@gmail.com>                       #
#                                                                             #
# Build an executable from module description.                                #
###############################################################################

# Parse module configuration
include build/parse-module.mk

PRIVATE_PRODUCT:=$(addprefix $(PRIVATE_OUT_DIR)/,$(addsuffix .bin,$(PRIVATE_MODULE)))

# Target module
.PHONY: $(PRIVATE_TARGET)
$(PRIVATE_TARGET): $(PRIVATE_PRODUCT)

# Link executable
$(PRIVATE_PRODUCT): PRIVATE_CFLAGS := $(PRIVATE_CFLAGS)
$(PRIVATE_PRODUCT): PRIVATE_CPPFLAGS := $(PRIVATE_CPPFLAGS)
$(PRIVATE_PRODUCT): PRIVATE_ASFLAGS := $(PRIVATE_ASFLAGS)
$(PRIVATE_PRODUCT): PRIVATE_LDFLAGS := $(PRIVATE_LDFLAGS)
$(PRIVATE_PRODUCT): PRIVATE_MODULE := $(PRIVATE_MODULE)
$(PRIVATE_PRODUCT): $(PRIVATE_OBJS) $(PRIVATE_STATIC_LIBRARIES)
	$(call link-o-and-a-to-binary, $(PRIVATE_OBJS) $(PRIVATE_DEPENDENCIES))

# Import build rules for object files
include build/rules.mk

