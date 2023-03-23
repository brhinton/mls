## $Id: Makefile.am,v 1.4 2002/08/21 20:42:56 alliz Exp $
## MLStreams
## Copyright (c) 2001-2002, Bryan Hinton
## All rights reserved.
## Process this file with automake to produce Makefile.in

##----------------------------------------------------

AUTOMAKE_OPTIONS = no-dependencies foreign

## INCLUDES = -I$(top_srcdir)/libmt

lib_LTLIBRARIES = libmt.la
libmt_la_SOURCES = CV.cpp CondAttr.cpp FastMutex.cpp Mutex.cpp MutexAttr.cpp MTException.cpp \
		   CondAttr.h CV.h FastMutex.h MTException.h MutexAttr.h Mutex.h Posix.h
libmt_la_LIBADD = -lpthread -lrt
