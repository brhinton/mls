# SPDX-License-Identifier: GPL-2.0-only
#
# MLStreams
# Copyright (c) 2001-2023, Bryan Hinton
# All rights reserved.

include Make.defines

echoserv:
	make -f Makefile.echoserv

all:
	make echoserv

clean:
	make -f Makefile.echoserv clean

again:
	make -f Makefile.echoserv clean
	make echoserv

TAGS:
	ctags *.h *.cpp *.tcc
