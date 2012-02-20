#########################################################
# Simple Object Kernel project Makefile                 #
# by Damien Dejean <djod4556@yahoo.fr>                  #
# Provides functions to simplify main Makefile content. #
#########################################################

# targetize:
# Creates compilation target files from source files
define targetize
$(notdir $(patsubst %.s,%.o,$(patsubst %.cpp,%.o,$(patsubst %.c,%.o,$(1)))))
endef

# first-and-unique:
# Ensure that the provided file is the first one and the unique instance of the list
# Prototype: $(first-and-unique file, file-list)
define first-and-unique
$(strip $(1) $(filter-out $(1), $(2)))
endef

