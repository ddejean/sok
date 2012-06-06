#########################################################
# Simple Object Kernel project Makefile                 #
# by Damien Dejean <djod4556@yahoo.fr>                  #
# Provides functions to simplify main Makefile content. #
#########################################################

# targetize:
# Creates compilation target files from source files
define targetize
$(notdir $(patsubst %.S,%.o,$(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(1)))))
endef

# first-and-unique:
# Ensure that the provided file is the first one and the unique instance of the list
# Prototype: $(first-and-unique file, file-list)
define first-and-unique
$(strip $(1) $(filter-out $(1), $(2)))
endef

# dirs-to-libs:
# Transform directories list to libraries list
define dirs-to-libs
$(addsuffix .a, $(addprefix lib, $(strip $(1))))
endef

# libs-to-paths(libdir, libfile, outputdir)
# Create compilation paths from libs file names and directory names
define libs-to-paths
$(addprefix $(3), $(join $(strip $(1)), $(strip $(2))))
endef

# generate-libs-flags:
# Generate library flags for linker based on lib names
define generate-libs-flags
$(addprefix -l, $(strip $(1)))
endef

# all-compilables-under
# Provide all compilable files (C, C++, ASM) under the directory
define all-compilables-under
$(strip $(wildcard $(1)/*.c) $(wildcard $(1)/*.cpp) $(wildcard $(1)/*.S))
endef

# objetize-compilables
# Change file names from source files to object files
define objetize-compilables
$(strip $(patsubst %.S, %.o, $(patsubst %.cpp, %.o, $(patsubst %.c, %.o, $(1)))))
endef

# generate-dependencies
# Change file names from source files to object files
define generate-dependencies
$(strip $(patsubst %.S, %.d, $(patsubst %.cpp, %.d, $(patsubst %.c, %.d, $(1)))))
endef
