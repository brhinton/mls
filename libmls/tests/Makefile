# $Id: Makefile,v 1.1 2002/05/20 22:22:11 alliz Exp $

# MLStreams
# Copyright (c) 2001-2002, Bryan Hinton
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
