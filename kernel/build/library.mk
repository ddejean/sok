##########################################
# Simple Object Kernel project Makefile  #
# by Damien Dejean <djod4556@yahoo.fr>   #
# Library build mechanism.				 #
##########################################

# Creates a rule to build a library based on its directory name
# and all compilable files under.
define LIBRARY_BUILD = 

# Library object file dependency
$(1)_OBJS := $$(addprefix $$(OUTPUT)/, $$(call objetize-compilables, $$(call all-compilables-under, $(1))))

# Build directory creation
$$(OUTPUT)/$(1): $$(OUTPUT)
	mkdir -p $$@

# Library target
$$(OUTPUT)/lib$(1).a: $$(OUTPUT)/$(1) $$($(1)_OBJS)
	$$(AR) rcs $$@ $$(filter-out $$<, $$^)
endef

