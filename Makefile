# SPDX-License-Identifier: GPL-2.0-only

.PHONY: all clean

all: out/init

out/init: init.c | out
	gcc -O2 -Wall -static -o out/init init.c

out:
	mkdir -p out

clean:
	rm -f out/init out/*.o
