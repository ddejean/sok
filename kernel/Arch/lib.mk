# The library must be linked with the kernel
KERNEL_LDFLAGS += -lArch

$(OUTPUT)/Arch/$(ARCH)/rmcode.o: $(OUTPUT)/Arch/$(ARCH)/empty.o $(OUTPUT)/Arch/$(ARCH)/rmcode.bin
	$(QOBJCOPY) $< --add-section=.rmcode=$(filter-out $<, $^) \
		       --set-section-flags=.rmcode=contents,alloc,load,data \
			   $@

$(OUTPUT)/Arch/$(ARCH)/rmcode.bin: $(OUTPUT)/Arch/$(ARCH)/relocable-rmcode.o
	$(QLD) $(LDFLAGS) -e do_bios_call_rm -Ttext 0x2000 $< --oformat binary -o $@

$(OUTPUT)/Arch/$(ARCH)/relocable-rmcode.o: Arch/$(ARCH)/rmcode.S
	$(SMART_MKDIR)
	$(QAS) $(FLAGS) $(INCLUDES) -c $< -o $@
