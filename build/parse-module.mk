###############################################################################
# Simple Object Kernel project Makefile                                       #
# Copyright 2013 - Damien Dejean <dam.dejean@gmail.com>                       #
#                                                                             #
# Process module configuration.                                               #
###############################################################################

#
# Module description
PRIVATE_MODULE := $(strip $(LOCAL_MODULE))
PRIVATE_PATH := $(strip $(LOCAL_PATH))
PRIVATE_CLASS := $(strip $(LOCAL_MODULE_CLASS))

ifeq (,$(PRIVATE_MODULE))
    $(error LOCAL_MODULE must be set.)
endif
ifeq (,$(PRIVATE_PATH))
    $(error LOCAL_PATH must be set.)
endif
ifeq (,$(PRIVATE_CLASS))
    $(error LOCAL_MODULE_CLASS must be set.)
endif


#
# Build configuration
PRIVATE_INCLUDES := $(PRIVATE_PATH)/ $(LOCAL_INCLUDES)
PRIVATE_CFLAGS   := $(DEFAULT_CFLAGS) $(LOCAL_CFLAGS)
PRIVATE_CPPFLAGS := $(DEFAULT_CPPFLAGS) $(LOCAL_CXXFLAGS)
PRIVATE_ASFLAGS  := $(DEFAULT_ASFLAGS) $(LOCAL_ASFLAGS)
PRIVATE_LDFLAGS  := $(DEFAULT_LDFLAGS) $(LOCAL_LDFLAGS)
PRIVATE_ARFLAGS  := $(DEFAULT_ARFLAGS) $(LOCAL_ARFLAGS)

ifeq ($(PRIVATE_CLASS),KERNEL)
    PRIVATE_INCLUDES += $(KERNEL_INCLUDES)
    PRIVATE_CFLAGS   += $(KERNEL_CFLAGS)
    PRIVATE_CPPFLAGS += $(KERNEL_CPPFLAGS)
    PRIVATE_ASFLAGS  += $(KERNEL_ASFLAGS)
    PRIVATE_LDFLAGS  += $(KERNEL_LDFLAGS)
    PRIVATE_ARFLAGS  += $(KERNEL_ARFLAGS)
endif


#
# Dependencies management
PRIVATE_DEPENDENCIES := $(strip $(LOCAL_DEPENDENCIES))
PRIVATE_STATIC_LIBRARIES := $(strip $(LOCAL_STATIC_LIBRARY))

$(foreach static_library,$(PRIVATE_STATIC_LIBRARIES), \
    $(eval $(static_library)_PRODUCT := $(call get-static-library-product,$(static_library))) \
    $(eval PRIVATE_DEPENDENCIES += $($(static_library)_PRODUCT)) \
)


#
# Build destination and files
PRIVATE_OUT_DIR := $(OUT_DIR)/$(PRIVATE_PATH)

PRIVATE_C_FILES := $(addprefix $(PRIVATE_PATH)/,$(filter %.c,$(LOCAL_SRC_FILES)))
PRIVATE_CPP_FILES := $(addprefix $(PRIVATE_PATH)/,$(filter %.cpp,$(LOCAL_SRC_FILES)))
PRIVATE_ASM_FILES := $(addprefix $(PRIVATE_PATH)/,$(filter %.S,$(LOCAL_SRC_FILES)))

PRIVATE_OBJS := $(addprefix $(OUT_DIR)/,\
    $(PRIVATE_C_FILES:.c=.o) \
    $(PRIVATE_CPP_FILES:.cpp=.o) \
    $(PRIVATE_ASM_FILES:.S=.o) \
)

#
# Define a target for the current module
PRIVATE_TARGET := $(strip $(PRIVATE_MODULE))


#
# Tests
ifneq (,$(LOCAL_TESTS_FILES))

PRIVATE_TESTS_TARGET:=test$(PRIVATE_MODULE)
PRIVATE_TESTS_BINARY:=$(addprefix $(PRIVATE_OUT_DIR)/tests/,$(PRIVATE_TESTS_TARGET))
PRIVATE_TEST_MAIN_SRC := $(PRIVATE_TESTS_BINARY).cpp
PRIVATE_TEST_MAIN_OBJ := $(PRIVATE_TESTS_BINARY).o

PRIVATE_TESTS_H_FILES := $(addprefix $(PRIVATE_PATH)/,$(filter %.h,$(LOCAL_TESTS_FILES)))
PRIVATE_TESTS_C_FILES := $(addprefix $(PRIVATE_PATH)/,$(filter %.c,$(LOCAL_TESTS_FILES)))
PRIVATE_TESTS_CPP_FILES := $(addprefix $(PRIVATE_PATH)/,$(filter %.cpp,$(LOCAL_TESTS_FILES)))
PRIVATE_TESTS_ASM_FILES := $(addprefix $(PRIVATE_PATH)/,$(filter %.S,$(LOCAL_TESTS_FILES)))

PRIVATE_TESTS_OBJS := $(addprefix $(OUT_DIR)/,\
    $(PRIVATE_TESTS_C_FILES:.c=.o) \
    $(PRIVATE_TESTS_CPP_FILES:.cpp=.o) \
    $(PRIVATE_TESTS_ASM_FILES:.S=.o) \
)

# Tests won't generate if there's no header files ...
ifeq (,$(PRIVATE_TESTS_H_FILES))
$(error $(PRIVATE_MODULE): missing test header files in LOCAL_TESTS_FILES)
endif

else

PRIVATE_TESTS_TARGET:=
PRIVATE_TESTS_BINARY:=
PRIVATE_TEST_MAIN_SRC:=
PRIVATE_TEST_MAIN_OBJ:=
PRIVATE_TESTS_H_FILES:=
PRIVATE_TESTS_C_FILES:=
PRIVATE_TESTS_CPP_FILES:=
PRIVATE_TESTS_ASM_FILES:=
PRIVATE_TESTS_OBJS :=

endif

