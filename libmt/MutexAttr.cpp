///////////////////////////////////////////////////////////////
//  SPDX-License-Identifier: GPL-2.0-only
//
//  MLStreams
//  Copyright (c) 2001-2023, Bryan Hinton
//  All rights reserved.
//
//  MutexAttr.cpp
//  Created by Bryan R. Hinton, on Mon Jul 02 2001, 17:36:34 CDT
//
//  File Contents: Implementation of the MutexAttr component.
//  Please see MutexAttr.h for full documentation of this system.
//
///////////////////////////////////////////////////////////////

#include "MutexAttr.h"


namespace MTLib
{

   MutexAttr::MutexAttr()
   {
      int ret = Init();
   }

   MutexAttr::MutexAttr(const MutexAttr &copy)
   {}

   MutexAttr::~MutexAttr()
   {
      Destroy();
   }

   const MutexAttr&
   MutexAttr::operator=(const MutexAttr &rhs)
   {}

   void
   MutexAttr::DumpDiagnostics() const
   {
      //std::cout << std::endl << std::endl <<
      //"MutexAttr Diagnostics dump "<< std::endl << std::endl;
   }

   int
   MutexAttr::Init(void)
   {
      return( pthread_mutexattr_init(&mattr) );
   }

   void
   MutexAttr::Destroy(void)
   {
      pthread_mutexattr_destroy(&mattr);
   }

   int
   MutexAttr::setpShared(int pshared)
   {
      return ( pthread_mutexattr_setpshared(&mattr, pshared) );
   }

   int
   MutexAttr::getpShared(int *pshared)
   {
      return ( pthread_mutexattr_getpshared(&mattr, pshared) );
   }

#ifdef XOPEN_REALTIME
   int
   MutexAttr::setPrioCeiling(int prioceiling)
   {
      return ( pthread_mutexattr_setprioceiling(&mattr, prioceiling) );
   }

   int
   MutexAttr::getPrioCeiling(int *prioceiling)
   {
      return ( pthread_mutexattr_getprioceiling(&mattr, prioceiling) );
   }

   int
   MutexAttr::setProtocol(int protocol)
   {
      return ( pthread_mutexattr_setprotocol(&mattr, protocol) ) ;
   }

   int
   MutexAttr::getProtocol(int *protocol)
   {
      return ( pthread_mutexattr_getprotocol(&mattr, protocol) );
   }

#endif

   pthread_mutexattr_t*
   MutexAttr::operator&(void)
   {
      return (&mattr);
   }


} // End namespace MTLib
