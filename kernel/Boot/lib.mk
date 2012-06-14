# The library must be linked with the kernel
# --whole-archive because code like realmode code need to be included even if
# LD is not able to see we use it
KERNEL_LDFLAGS += --whole-archive -lBoot --no-whole-archive
