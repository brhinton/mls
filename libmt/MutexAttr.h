///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  MutexAttr.h
//  Created by Bryan R. Hinton, on Mon Jul 02 2001, 17:36:34 CDT
//
//  File Contents: Interface and documentation of the MutexAttr component.
//
///////////////////////////////////////////////////////////////

#ifndef MTLIBMUTEXATTR_H
#define MTLIBMUTEXATTR_H



// linkage specifications: functions listed here will not be name encoded.
extern "C"
{
   //#include <pthread.h>
#include "Posix.h"
}

namespace MTLib
{

   /** Purpose: TODO: Describe the purpose of the class.
    *  (Everything that you write here will show up in the
    *  doc++ generated documentation.)
    */
   class MutexAttr
   {

      public:
         /// Constructor.
         MutexAttr();

         // Copy Constructor.
         MutexAttr(const MutexAttr&);

         // Destructor.
         virtual ~MutexAttr();

         // Overloaded Assignment Operator.
         const MutexAttr& operator=(const MutexAttr&);

         /// DumpDiagnostics() dumps the object's state to standard output.
         void DumpDiagnostics() const;

         // set / get process shared attribute of mutexattr object
         int
         setpShared(int);

         int
         getpShared(int *);

#ifdef XOPEN_REALTIME

         // set / get priority ceiling value of mutex attribute object
         // value must be within range of priorities defined by SCHED_FIFO
         int
         setPrioCeiling(int);

         int
         getPrioCeiling(int*);

         // set / get protocol attribute of mutex attribute object
         // PTHREAD_PRIO_INHERIT
         // PTHREAD_PRIO_NONE
         // PTHREAD_PRIO_PROTECT
         int
         setProtocol(int);

         int
         getProtocol(int*);

#endif

         // return address of mutexattr object
         pthread_mutexattr_t* operator&(void);

      protected:

      private:
         int Init(void);
         void Destroy(void);
         pthread_mutexattr_t mattr;


   }
   ; // End class MutexAttr

} // End namespace MTLib

#endif

// NOTES
//NOTES:
//	LINUX: PTHREAD_MUTEX_FAST_NP - default
//		   PTHREAD_MUTEX_RECURSIVE_NP
//		   PTHREAD_MUTEX_ERRORCHECK_NP
//			pthread_mutexattr_setkind_np
//			pthread_mutexattr_getkind_np

//  SOLARIS


//**************************************************************************
//On XSI-conformant systems, _POSIX_THREADS, _POSIX_THREAD_ATTR_STACKADDR,
//_POSIX_THREAD_ATTR_STACKSIZE and _POSIX_THREAD_PROCESS_SHARED are always defined.
//Therefore, the following threads interfaces are always supported:
//**************************************************************************


//--------------------------POSIX-------------------------------------------
//init a mutexattr object with default value for implementation.
//ENOMEM - insufficient memory
//--int pthread_mutexattr_init(pthread_mutexattr_t *attr);

//destroy a mutex attributes object
//EINVAL - value specified by attr is invalid
//--int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
//--------------------------------------------------------------------------

//--------------------------POSIX-------------------------------------------
//get process shared attribute from attributes object
//EINVAL - invalid attr value
//--int pthread_mutexattr_getpshared(const pthread_mutexattr_t *attr, int *pshared);

//set process shared attribute in attributes object
//pshared can be set to PTHREAD_PROCESS_SHARED, PTHREAD_PROCESS_PRIVATE
//EINVAL - new value for pshared is outside legal range of values
//EINVAL - invalid attr value
//--int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int pshared);
//--------------------------------------------------------------------------

//--------------------------X/Open------------------------------------------
//get or set the mutex type attribute.
//PTHREAD_MUTEX_DEFAULT. can be mapped to one of the following types.
//PTHREAD_MUTEX_NORMAL - no deadlock detection.
//PTHREAD_MUTEX_ERRORCHECK - lock / unlock / deadlock detection
//PTHREAD_MUTEX_RECURSIVE - no deadlock. recursive locking and unlocking

//EINVAL - the value type is invalid
//EINVAL - the value specified by attr is invalid
//--int pthread_mutexattr_gettype(const pthread_mutexattr_t *attr, int *type);
//--int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);
//--------------------------------------------------------------------------



//**************************************************************************
//Real-Time. Only supported on XSI-conformant systems.
//_XOPEN_REALTIME_THREADS != -1 if implementation is supported.
//if _XOPEN_REALTIME_THREADS != -1 then
//_POSIX_THREAD_PRIORITY_SCHEDULING
//_POSIX_THREAD_PRIO_PROTECT
//_POSIX_THREAD_PRIO_INHERIT will be defined in <unistd.h>
//**************************************************************************

//-----------------------------RealTime Threads-----------------------------------
//get and set priority ceiling attribute of a mutex attributes object
//prioceiling is the priority that a thread will run at when it locks a mutex.
//prioceiling must be greater than or equal to the highest priority of all the
//threads that will lock the mutex, otherwise priority inversions will not be
//prevented.  The value of prioceiling will be within
//the maximum range of priorities defined by SCHED_FIFO.
//ENOSYS - _POSIX_THREAD_PRIO_PROTECT is not defined and the implementation does not support the function.
//EINVAL - The value specified by attr or prioceiling is invalid.
//EPERM  - The caller does not have the privilege to perform the operation.
//--int pthread_mutexattr_setprioceiling(pthread_mutexattr_t *attr, int prioceiling);
//--int pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *attr, int *prioceiling);
//--------------------------------------------------------------------------------

//-----------------------------RealTime Threads-----------------------------------
//get and set protocol attribute of a mutex attributes object
//protocol value may be set to PTHREAD_PRIO_NONE, PTHREAD_PRIO_INHERIT or PTHREAD_PRIO_PROTECT
//which are defined in <pthread.h>
//PTHREAD_PRIO_NONE     - when a thread grabs the mutex it's priority and scheduling
//						  are not affected by it's mutex ownership
//PTHREAD_PRIO_INHERIT  - When a thread is blocking higher priority threads because of owning one
//						  or more mutexes with the PTHREAD_PRIO_INHERIT protocol attribute,
//						  it executes at the higher of its priority or the priority of the highest
//						  priority thread waiting on any of the mutexes owned by this thread
//						  and initialised with this protocol.
//PTHREAD_PRIO_PROTECT  -

//ENOSYS  - Neither one of the options _POSIX_THREAD_PRIO_PROTECT and
//          _POSIX_THREAD_PRIO_INHERIT is defined and the implementation does not
//			support the function.
//ENOTSUP - The value specified by protocol is an unsupported value.
//EINVAL  - The value specified by attr ro protocol is invalid.
//EPERM   - The caller does not have the privilege to perform the operation.

//--int pthread_mutexattr_setprotocol(pthread_mutexattr_t *attr, int protocol);
//--int pthread_mutexattr_getprotocol(const pthread_mutexattr_t *attr, int *protocol);
//--------------------------------------------------------------------------------
