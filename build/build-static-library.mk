###############################################################################
# Simple Object Kernel project Makefile                                       #
# Copyright 2013 - Damien Dejean <dam.dejean@gmail.com>                       #
#                                                                             #
# Build a static library from module description.                             #
###############################################################################

# Parse module configuration
include build/parse-module.mk

PRIVATE_PRODUCT:=$(addprefix $(PRIVATE_OUT_DIR)/,$(addprefix lib,$(addsuffix .a,$(PRIVATE_MODULE))))

PRIVATE_ARFLAGS := $(DEFAULT_ARFLAGS)

# Register the static library
$(call register-static-library,$(PRIVATE_MODULE),$(PRIVATE_PRODUCT))

# Target module
.PHONY: $(PRIVATE_TARGET)
$(PRIVATE_TARGET): $(PRIVATE_PRODUCT) $(PRIVATE_TESTS_TARGET)

$(PRIVATE_PRODUCT): PRIVATE_MODULE := $(PRIVATE_MODULE)
$(PRIVATE_PRODUCT): PRIVATE_CFLAGS := $(PRIVATE_CFLAGS)
$(PRIVATE_PRODUCT): PRIVATE_CPPFLAGS := $(PRIVATE_CPPFLAGS)
$(PRIVATE_PRODUCT): PRIVATE_ASFLAGS := $(PRIVATE_ASFLAGS)
$(PRIVATE_PRODUCT): PRIVATE_ARFLAGS := $(PRIVATE_ARFLAGS)
$(PRIVATE_PRODUCT): $(PRIVATE_OBJS)
	$(call link-o-to-archive)

# Import build rules for object files
include build/rules.mk

