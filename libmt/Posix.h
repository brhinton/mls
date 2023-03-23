// $Id: Posix.h,v 1.3 2002/05/18 21:30:16 alliz Exp $
//  MLStreams
//  Copyright (c) 2001-2002, Bryan Hinton
//  All rights reserved.

#ifndef POSIX_H
#define POSIX_H
#include <pthread.h>
#include <unistd.h>

#if defined(_POSIX_THREAD_PRIO_INHERIT) \
 && defined(_POSIX_THREAD_PRIO_PROTECT) \
 && defined(_POSIX_THREAD_PRIORITY_SCHEDULING)
#define XOPEN_REALTIME
#endif

#if defined(_POSIX_THREADS) \
 && defined(_POSIX_THREAD_ATTR_STACKADDR) \
 && defined(_POSIX_THREAD_ATTR_STACKSIZE) \
 && defined(_POSIX_THREAD_PROCESS_SHARED)
#define XSI_CONFORM
#endif

#endif
