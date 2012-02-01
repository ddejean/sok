#########################################
# Simple Object Kernel project Makefile #
# by Damien Dejean <djod4556@yahoo.fr>  #
#########################################

all: kernel.bin disk
	echo "### This target will require root access to mont disk image ! ###"
	sudo losetup -o 1048576 /dev/loop0 disk.img
	sudo mount -t ext2 /dev/loop0 disk/
	sudo cp kernel.bin disk/
	sudo umount disk/
	sudo losetup -d /dev/loop0
	rm -f kernel.bin

disk:
	mkdir disk/

kernel.bin: kernel/kernel.bin
	cp kernel/kernel.bin .

kernel/kernel.bin:
	make -C kernel/ kernel.bin

