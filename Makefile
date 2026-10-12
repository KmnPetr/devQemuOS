# SPDX-License-Identifier: GPL-2.0-only

.PHONY: all clean

all: out/init out/initramfs.cpio

out/init: init.c bash.c Makefile | out
	gcc -O2 -Wall -o out/init init.c

# libs/ mirrors rootfs paths: libs/lib64/... → out/rootfs/lib64/...
out/initramfs.cpio: out/init $(shell find libs -type f 2>/dev/null)
	mkdir -p out/rootfs
	cp -f out/init out/rootfs/init
	cp -a libs/. out/rootfs/
	cd out/rootfs && find . -print | cpio -o -H newc > ../initramfs.cpio

out:
	mkdir -p out

clean:
	rm -f out/init out/*.o out/initramfs.cpio
	rm -rf out/rootfs
