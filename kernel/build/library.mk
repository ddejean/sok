##########################################
# Simple Object Kernel project Makefile  #
# by Damien Dejean <djod4556@yahoo.fr>   #
# Library build mechanism.				 #
##########################################

# Creates a rule to build a library based on its directory name
# and all compilable files under.
define LIBRARY_BUILD =

# Clear local libray definitions
LOCAL_INCLUDES :=
LOCAL_CFLAGS :=
LOCAL_CXXFLAGS :=

# Import local library stuff
-include $(1)/lib.mk

# Library dependencies
$(1)_FILES := $$(call all-compilables-under, $(1))
$(1)_OBJS  := $$(addprefix $$(OUTPUT)/, $$(call objetize-compilables, $$($(1)_FILES)))
$(1)_DEPS  := $$(addprefix $$(OUTPUT)/, $$(call generate-dependencies, $$($(1)_FILES)))

# Include dependency targets
ifneq "$$(OUTPUT)" ""
-include $$($(1)_DEPS)
endif

# Library target
$$(OUTPUT)/lib$(1).a: INCLUDES += $$(LOCAL_INCLUDES)
$$(OUTPUT)/lib$(1).a: CFLAGS += $$(LOCAL_CFLAGS)
$$(OUTPUT)/lib$(1).a: CXXFLAGS += $$(LOCAL_CXXFLAGS)
$$(OUTPUT)/lib$(1).a: $$($(1)_OBJS)
	$$(AR) rcs $$@ $$^

endef

