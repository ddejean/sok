###############################################################################
# Simple Object Kernel project Makefile                                       #
# Copyright 2013 - Damien Dejean <dam.dejean@gmail.com>                       #
#                                                                             #
# Module database implementation. Aims to centralize a module list by class   #
# to allow easy reuse between module declaration.slobal toolchain definitions.#
###############################################################################

#
# Static library database
STATIC_LIBRARIES_DB :=

###########################################################
## Register a static library
###########################################################

# $(1): library module name
# $(2): library linkable file
define register-static-library
$(eval STATIC_LIBRARIES_DB += $(1):$(2))
endef

# $(1): library module name
define get-static-library-product
$(strip $(patsubst $(1):%,%,$(filter $(1):%,$(STATIC_LIBRARIES_DB))))
endef

