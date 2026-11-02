#!/bin/sh
set -e

cd "$(dirname "$0")"

# Rebuild the kernel and this tree's init.
make -C ../linux -j14
make

# Plain QEMU on the existing kernel bzImage, no -device edu.
exec qemu-system-x86_64 \
	-kernel ../linux/arch/x86/boot/bzImage \
	-initrd out/initramfs.cpio \
	-append "console=ttyS0 rdinit=/init" \
	-m 512 \
	-nographic \
	-no-reboot
