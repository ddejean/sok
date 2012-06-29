# The library must be linked with the kernel
# --whole-archive because code like realmode code need to be included even if
# LD is not able to see we use it
KERNEL_LDFLAGS += --whole-archive -lArch --no-whole-archive

$(OUTPUT)/Arch/$(ARCH)/realmodecode.o: $(OUTPUT)/Arch/$(ARCH)/empty.o $(OUTPUT)/Arch/$(ARCH)/realmodecode.bin
	$(QOBJCOPY) $< --add-section=.realmodecode=$(OUTPUT)/Arch/$(ARCH)/realmodecode.bin \
		       --set-section-flags=.realmodecode=contents,alloc,load,data \
			   $@

$(OUTPUT)/Arch/$(ARCH)/realmodecode.bin: $(OUTPUT)/Arch/$(ARCH)/relocable-code.o
	$(QLD) $(LDFLAGS) -e do_bios_call_rm -Ttext 0x2000 $< --oformat binary -o $@

$(OUTPUT)/Arch/$(ARCH)/relocable-code.o: Arch/$(ARCH)/realmodecode.S
	$(SMART_MKDIR)
	$(QAS) $(FLAGS) $(INCLUDES) -c $< -o $@
