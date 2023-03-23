## $Id: Makefile.am,v 1.4 2002/08/21 20:42:38 alliz Exp $
## MLStreams
## Copyright (c) 2001-2002, Bryan Hinton
## All rights reserved.

##----------------------------------------------------

AUTOMAKE_OPTIONS = no-dependencies foreign

INCLUDES = -I$(top_srcdir)/libmt

AM_CXXFLAGS = -D_REENTRANT -frepo

lib_LTLIBRARIES = libmls.la
libmls_la_SOURCES = mlbuf.cpp mlpipebuf.cpp mlshmbuf.cpp mlsockbuf.cpp mlstream.cpp \
			       mlistream.cpp mlostream.cpp Trace.cpp Trace.h cstream.h \
			       Meta.h mlbuf.h mlistream.h mlostream.h mlpipebuf.h \
			       mlpipestreamimpl.h mlshmbuf.h mlshmstreamimpl.h mls_mlistream.h \
			       mls_mlostream.h mls_mlstream.h mlsockbuf.h mlsockstreamimpl.h \
			       mlstream.h mlstreamimpl.h StreamConfig.h mlpipestreamimpl.tcc \
			       mlshmstreamimpl.tcc mls_mlistream.tcc mls_mlostream.tcc \
			       mls_mlstream.tcc mlsockstreamimpl.tcc mlstreamimpl.tcc

libmls_la_LIBADD = $(top_builddir)/libmt/libmt.la -lnsl -lresolv -lsocket
#libmls_la_LIBADD = -lnsl -lresolv -lsocket
