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
$$(OUTPUT)/lib$(1).a: KERNEL_CFLAGS += $$(LOCAL_CFLAGS)
$$(OUTPUT)/lib$(1).a: KERNEL_CXXFLAGS += $$(LOCAL_CXXFLAGS)
$$(OUTPUT)/lib$(1).a: $$($(1)_OBJS)
	$$(QAR) rcs $$@ $$^

### General library target ###
ifeq ("$(wildcard $(1)/tests)", "$(1)/tests")

# There're tests to compile and run !
lib$(1).a: $$(OUTPUT)/$(1)/test$(1)
	@echo -e "\tTEST\t  $$@"; $$(OUTPUT)/$(1)/test$(1)

$(1)_TEST_FILES 	:= $$(call all-compilables-under, $(1)/tests)
$(1)_TEST_OBJS  	:= $$(addprefix $$(OUTPUT)/, $$(call objetize-compilables, $$($(1)_TEST_FILES)))
$(1)_TEST_DEPS  	:= $$(addprefix $$(OUTPUT)/, $$(call generate-dependencies, $$($(1)_TEST_FILES)))

ifneq "$$(OUTPUT)" ""
-include $$($(1)_TEST_DEPS)
endif

# Test binary link
$$(OUTPUT)/$(1)/test$(1): INCLUDES += -I$(1)/tests/
$$(OUTPUT)/$(1)/test$(1): $$(OUTPUT)/$(1)/tests/test$(1).o $$(OUTPUT)/lib$(1).a $$($(1)_TEST_OBJS)
	$$(QCPP) -m32 -o $$@ $$^ -L$$(OUTPUT) -l$(1)

# Test binary generation and compilation
$$(OUTPUT)/$(1)/tests/test$(1).o: $$(OUTPUT)/$(1)/tests/test$(1).cpp
	$$(QCPP) $$(CXXFLAGS) -I. -c $$< -o $$@

$$(OUTPUT)/$(1)/tests/test$(1).cpp: $$($(1)_TEST_FILES)
	$$(QTESTGEN) -o $$@ --error-printer $(1)/tests/*.h

$$(OUTPUT)/$(1)/tests/%.o: $(1)/tests/%.cpp
	$$(QCPP) $$(CXXFLAGS) $$(INCLUDES) -c $$< -o $$@

else

# No tests, that's bad, but ignore it ...
lib$(1).a: $$(OUTPUT)/lib$(1).a
	@echo -e "\tTEST\t  $$@: no tests for $$@, skipping."

endif

endef

