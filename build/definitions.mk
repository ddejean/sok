###############################################################################
# Simple Object Kernel project Makefile                                       #
# Copyright 2013 - Damien Dejean <dam.dejean@gmail.com>                       #
#                                                                             #
# Global toolchain definitions.                                               #
###############################################################################


###########################################################
## Retrieve the directory of the current makefile
###########################################################

# Figure out where we are.
define my-dir
$(strip \
  $(eval LOCAL_MODULE_MAKEFILE := $$(lastword $$(MAKEFILE_LIST)))        \
    $(if $(filter $(CLEAR_VARS),$(LOCAL_MODULE_MAKEFILE)),               \
         $(error LOCAL_PATH must be set before including $$(CLEAR_VARS)) \
         ,                                                               \
         $(patsubst %/,%,$(dir $(LOCAL_MODULE_MAKEFILE)))                \
     )                                                                   \
)
endef


###########################################################
## Retrieve a list of all makefiles immediately below some directory
###########################################################

define all-makefiles-under
$(wildcard $(1)/*/Sok.mk)
endef


###########################################################
## Look in the named list of directories for makefiles,
## relative to the current directory.
###########################################################

# $(1): List of directories to look for under this directory
define all-named-subdir-makefiles
$(wildcard $(addsuffix /Sok.mk, $(addprefix $(call my-dir)/,$(1))))
endef


###########################################################
## Evaluates to true if the string contains the word true,
## and empty otherwise
## $(1): a var to test
###########################################################

define true-or-empty
$(filter true, $(1))
endef


###########################################################
## Function we can evaluate to introduce a dynamic dependency
###########################################################

define add-dependency
$(1): $(2)
endef


###########################################################
## Returns true if $(1) and $(2) are equal. Returns
## the empty string if they are not equal.
###########################################################

define streq
$(strip $(if $(strip $(1)),                                                                                                  \
             $(if $(strip $(2)),                                                                                             \
                  $(if $(filter-out __,_$(subst $(strip $(1)),,$(strip $(2)))$(subst $(strip $(2)),,$(strip $(1)))_),,true), \
              ),                                                                                                             \
              $(if $(strip $(2)),                                                                                            \
                   ,                                                                                                         \
                   true)                                                                                                     \
         )                                                                                                                   \
)
endef


###########################################################
## Find all of the header files under the named directories.
## Meant to be used like:
## SRC_FILES := $(call all-h-files-under,src tests)
###########################################################

define all-h-files-under
$(patsubst ./%,%, \
    $(shell cd $(LOCAL_PATH) ; \
            find -L $(1) -name "*.h" -and -not -name ".*") \
)
endef

define h-files-under
$(patsubst ./%,%, \
    $(shell cd $(LOCAL_PATH) ; \
            find -L $(1) -maxdepth 1 -name "*.h" -and -not -name ".*") \
)
endef


###########################################################
## Find all of the C++ files under the named directories.
## Meant to be used like:
## SRC_FILES := $(call all-cpp-files-under,src tests)
###########################################################

define all-cpp-files-under
$(patsubst ./%,%, \
    $(shell cd $(LOCAL_PATH) ; \
            find -L $(1) -name "*.cpp" -and -not -name ".*") \
)
endef

define cpp-files-under
$(patsubst ./%,%, \
    $(shell cd $(LOCAL_PATH) ; \
            find -L $(1) -maxdepth 1 -name "*.cpp" -and -not -name ".*") \
)
endef



###########################################################
## Find all of the c files under the named directories.
## Meant to be used like:
## SRC_FILES := $(call all-c-files-under,src tests)
###########################################################

define all-c-files-under
$(patsubst ./%,%, \
    $(shell cd $(LOCAL_PATH) ; \
            find -L $(1) -name "*.c" -and -not -name ".*") \
)
endef

define c-files-under
$(patsubst ./%,%, \
    $(shell cd $(LOCAL_PATH) ; \
            find -L $(1) -maxdepth 1 -name "*.c" -and -not -name ".*") \
)
endef


###########################################################
## Find all of the ASM files under the named directories.
## Meant to be used like:
## SRC_FILES := $(call all-asm-files-under,src tests)
###########################################################

define all-asm-files-under
$(patsubst ./%,%, \
    $(shell cd $(LOCAL_PATH) ; \
            find -L $(1) -name "*.S" -and -not -name ".*") \
)
endef

define asm-files-under
$(patsubst ./%,%, \
    $(shell cd $(LOCAL_PATH) ; \
            find -L $(1) -maxdepth 1 -name "*.S" -and -not -name ".*") \
)
endef


###########################################################
## Commands for munging the dependency files GCC generates
###########################################################
# $(1): the input .d file
# $(2): the output .P file
define transform-d-to-p-args
$(hide) $(CP) $(1) $(2); \
    sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
    -e '/^$$/ d' -e 's/$$/ :/' < $(1) >> $(2); \
    $(RM) -f $(1)
endef

define transform-d-to-p
$(call transform-d-to-p-args,$(@:%.o=%.d),$(@:%.o=%.P))
endef


###########################################################
## Build a C++ file with gcc
###########################################################

define transform-cpp-to-o
@mkdir -p $(dir $@)
@echo "  CPP   $(PRIVATE_MODULE) <= $<"
$(hide) $(CPP) \
    $(addprefix -I , $(PRIVATE_INCLUDES)) \
    -c \
    $(PRIVATE_CPPFLAGS) \
    -MD -MF $(patsubst %.o,%.d,$@) -o $@ $<
$(transform-d-to-p)
endef


###########################################################
## Commands for running gcc to compile a C file
###########################################################

# $(1): extra flags
define transform-c-or-s-to-o-no-deps
@mkdir -p $(dir $@)
$(hide) $(CC) \
    $(addprefix -I , $(PRIVATE_INCLUDES)) \
    -c \
    $(1) \
    -MD -MF $(patsubst %.o,%.d,$@) -o $@ $<
endef

define transform-c-to-o-no-deps
@echo "  CC    $(PRIVATE_MODULE) <= $<"
$(call transform-c-or-s-to-o-no-deps,$(PRIVATE_CFLAGS))
endef

define transform-s-to-o-no-deps
@echo "  AS    $(PRIVATE_MODULE) <= $<"
$(call transform-c-or-s-to-o-no-deps,$(PRIVATE_ASFLAGS))
endef

define transform-c-to-o
$(transform-c-to-o-no-deps)
$(trasform-d-to-p)
endef

define transform-s-to-o
$(transform-s-to-o-no-deps)
$(transform-d-to-p)
endef


###########################################################
## Commands for linking o files to a binary
###########################################################

define link-o-and-a-to-binary
@echo "  LD    $(PRIVATE_MODULE): $(notdir $@)"
@mkdir -p $(dir $@)
$(hide) $(LD) -o $@ $(PRIVATE_LDFLAGS) $(1)
endef


###########################################################
## Commands for linking o files to an archive
###########################################################

define link-o-to-archive
@echo "  AR    $(PRIVATE_MODULE): $(notdir $@)"
@mkdir -p $(dir $@)
$(hide) $(AR) $(PRIVATE_ARFLAGS) $@ $(filter %.o,$^)
endef


###########################################################
## Commands for running tests
###########################################################

define run-tests
@echo "  TEST  $(PRIVATE_MODULE)"
$(hide) $<
endef

