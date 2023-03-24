## SPDX-License-Identifier: GPL-2.0-only
## MLStreams
## Copyright (c) 2001-2023, Bryan Hinton
## All rights reserved.
## Process this file with automake to produce Makefile.in

##----------------------------------------------------

AUTOMAKE_OPTIONS = no-dependencies foreign

## INCLUDES = -I$(top_srcdir)/libmt

lib_LTLIBRARIES = libmt.la
libmt_la_SOURCES = CV.cpp CondAttr.cpp FastMutex.cpp Mutex.cpp MutexAttr.cpp MTException.cpp \
		   CondAttr.h CV.h FastMutex.h MTException.h MutexAttr.h Mutex.h Posix.h
libmt_la_LIBADD = -lpthread -lrt
