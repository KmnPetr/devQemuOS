#!/bin/sh
set -e

# Rebuild the kernel and this tree's init.
make -C /home/petr/k-dev -j14
make -C /home/petr/k-dev/devQemuOS

# Plain QEMU on the existing k-dev bzImage, no -device edu.
exec qemu-system-x86_64 \
	-kernel /home/petr/k-dev/arch/x86/boot/bzImage \
	-initrd /home/petr/k-dev/devQemuOS/out/initramfs.cpio \
	-append "console=ttyS0 rdinit=/init" \
	-m 512 \
	-nographic \
	-no-reboot
