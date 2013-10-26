###############################################################################
# Simple Object Kernel project Makefile                                       #
# Copyright 2013 - Damien Dejean <dam.dejean@gmail.com>                       #
#                                                                             #
# Standard build rules for modules.                                           #
###############################################################################


###########################################################
# C: Compile .c files to .o.
###########################################################

c_sources  := $(strip $(PRIVATE_C_FILES) $(PRIVATE_TESTS_C_FILES))
c_objects  := $(addprefix $(OUT_DIR)/,$(c_sources:.c=.o))
c_out_path := $(PRIVATE_OUT_DIR)

ifneq ($(strip $(c_objects)),)

$(c_objects): PRIVATE_MODULE := $(PRIVATE_MODULE)
$(c_objects): $(c_out_path)/%.o: $(PRIVATE_PATH)/%.c
	$(transform-c-to-o)

-include $(c_objects:%.o=%.P)
endif


###########################################################
# C++: Compile .c++ files to .o.
###########################################################

cpp_sources  := $(strip $(PRIVATE_CPP_FILES) $(PRIVATE_TESTS_CPP_FILES))
cpp_objects  := $(addprefix $(OUT_DIR)/,$(cpp_sources:.cpp=.o))
cpp_out_path := $(PRIVATE_OUT_DIR)

ifneq ($(strip $(cpp_objects)),)

$(cpp_objects): PRIVATE_MODULE := $(PRIVATE_MODULE)
$(cpp_objects): $(cpp_out_path)/%.o: $(PRIVATE_PATH)/%.cpp
	$(transform-cpp-to-o)

-include $(cpp_objects:%.o=%.P)
endif


###########################################################
# ASM: Compile .S files to .o.
###########################################################

asm_sources  := $(strip $(PRIVATE_ASM_FILES) $(PRIVATE_TESTS_ASM_FILES))
asm_objects  := $(addprefix $(OUT_DIR)/,$(asm_sources:.S=.o))
asm_out_path := $(PRIVATE_OUT_DIR)

ifneq ($(strip $(asm_objects)),)
$(asm_objects): PRIVATE_MODULE := $(PRIVATE_MODULE)

$(asm_objects): $(asm_out_path)/%.o: $(PRIVATE_PATH)/%.S
	$(transform-s-to-o)

-include $(asm_objects:%.o=%.P)
endif


###########################################################
# Tests targets
###########################################################

ifneq (,$(LOCAL_TESTS_FILES))

$(PRIVATE_TESTS_TARGET): PRIVATE_MODULE := $(PRIVATE_MODULE)
$(PRIVATE_TESTS_TARGET): $(PRIVATE_TESTS_BINARY)
	$(run-tests)

$(PRIVATE_TEST_MAIN_SRC): $(PRIVATE_TESTS_H_FILES)
	@echo "  GEN   $(PRIVATE_MODULE) <= $(notdir $@)"
	@mkdir -p $(dir $@)
	$(hide) $(TESTGEN) -o $@ --error-printer $^

$(PRIVATE_TEST_MAIN_OBJ): $(PRIVATE_TEST_MAIN_SRC)
	$(transform-cpp-to-o)

$(PRIVATE_TESTS_BINARY): PRIVATE_INCLUDES := ./ kernel/
$(PRIVATE_TESTS_BINARY): PRIVATE_LDFLAGS := -m32
$(PRIVATE_TESTS_BINARY): PRIVATE_CFLAGS := $(DEFAULT_CFLAGS)
$(PRIVATE_TESTS_BINARY): PRIVATE_CPPFLAGS := $(DEFAULT_CPPFLAGS)
$(PRIVATE_TESTS_BINARY): PRIVATE_ASFLAGS := $(DEFAULT_ASFLAGS)
$(PRIVATE_TESTS_BINARY): PRIVATE_TESTS_OBJS := $(PRIVATE_TESTS_OBJS)
$(PRIVATE_TESTS_BINARY): PRIVATE_TESTS_H_FILES := $(PRIVATE_TESTS_H_FILES)
$(PRIVATE_TESTS_BINARY): PRIVATE_PRODUCT := $(PRIVATE_PRODUCT)
$(PRIVATE_TESTS_BINARY): PRIVATE_TEST_MAIN_OBJ := $(PRIVATE_TEST_MAIN_OBJ)
$(PRIVATE_TESTS_BINARY): $(PRIVATE_TEST_MAIN_OBJ) $(PRIVATE_TESTS_OBJS) $(PRIVATE_PRODUCT)
	$(hide) $(CPP) $(PRIVATE_LDFLAGS) -o $@ $(PRIVATE_TEST_MAIN_OBJ) $(PRIVATE_TESTS_OBJS) $(PRIVATE_PRODUCT)
endif
